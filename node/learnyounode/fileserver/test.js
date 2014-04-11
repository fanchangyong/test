
var http = require('http');
var fs = require('fs');

var argv = process.argv;
var port = argv[2];
var filename = argv[3];

var server = http.createServer(function(req,res){
	var filestream = fs.createReadStream(filename);
	res.on('pipe',function(src){
		//console.log("pipe event:",src);
	});
	filestream.on('open',function(){
		filestream.pipe(res,{end:false});
	});
	filestream.on('end',function(){
		res.end();
	});

	//res.write("hello,client!");
	//res.end();
});
server.listen(Number(port));
