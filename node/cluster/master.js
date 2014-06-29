var cluster = require('cluster');
var http = require('http');
var numCPUs = require('os').cpus().length;


if (cluster.isMaster) {
	//Fork workers.
		for (var i = 0; i < numCPUs; i++) {
			var worker=cluster.fork();
			worker.on('error',function(){
				console.log('worker error');
			});
		}

	cluster.on('exit', function(worker, code, signal) {
		console.log('worker ' + worker.process.pid + ' died');
	});
} else {
	// Workers can share any TCP connection
	// In this case its a HTTP server
	
	process.on('uncaughtException',function(err){
		console.log('error:',err);
		console.log('stack:',err.stack);
		process.exit(1);
	});
	http.createServer(function(req, res) {
		res.writeHead(200);
		res.end("Hello from worker ["+cluster.worker.id+"]");
		throw new Error('MyError');
	}).listen(8000);
}
