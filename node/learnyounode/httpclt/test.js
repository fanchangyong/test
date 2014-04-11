var http = require('http');
var argv = process.argv;

if(argv.length<3){
	console.log("Usage: node program <url>");
	return;
}
var url = argv[2];
var strings = new String();
http.get(url,function(res){
	res.setEncoding('utf8');
	res.on('data',function(data){
		strings = strings + data;
	});
	
	res.on('end',function(){
		console.log(strings.length);
		console.log(strings);
	});

	res.on('error',function(err){
		console.log(err);
	});
});
