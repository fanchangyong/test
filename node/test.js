var connect = require('connect');

connect.createServer(
		connect.logger('tiny')
		,function(req,res){
			res.writeHead(200);
			res.end('Hello world');
		}).listen(3100);
