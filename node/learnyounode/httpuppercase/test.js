
var http = require('http');
var server = http.createServer(function(req,res){
	console.log("req:",req);
	if(req.method=='POST'){

	}
});

server.listen(8888);
