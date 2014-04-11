var net = require('net');

var argv = process.argv;

var port = argv[2];
var server = net.createServer(function(socket){
	var now = new Date();
	var year = now.getFullYear();
	var month = now.getMonth()+1;
	var strmonth;
	if(month<10){
		strmonth = "0"+month;
	}else{
		strmonth = "" + month;
	}

	var day = now.getDate();
	var strday;
	if(day<10){
		strday = "0"+day;
	}else{
		strday = ""+day;
	}

	var hour = now.getHours();
	var strhour;
	if(hour<10){
		strhour = "0"+hour;
	}else{
		strhour = ""+hour;
	}

	var minute = now.getMinutes();
	var strmin;
	if(minute<10){
		strmin = "0"+minute;
	}else{
		strmin = "" + minute;
	}
	var str = "" + year + "-" + strmonth + "-" + strday + " " + strhour + ":" + strmin + "\n";
	socket.write(str);
	socket.end();
});

server.listen(port);
