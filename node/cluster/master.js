var cluster = require('cluster');
var http = require('http');
var numCPUs = require('os').cpus().length;
var conns = [];

function msgHandler(msg){
	conns.push(msg.conn);
	if(conns.length==numCPUs){
		var sum = 0;
		for(var j=0;j<conns.length;j++){
			sum+=conns[j];
		}
		console.log('msg conn:',msg.conn);
		conns=[];
	}
}

if (cluster.isMaster) {
  // Fork workers.
  for (var i = 0; i < numCPUs; i++) {
    var worker = cluster.fork();
		worker.on('message',msgHandler);
  }

  cluster.on('exit', function(worker, code, signal) {
    console.log('worker ' + worker.process.pid + ' died');
  });

} else {
  // Workers can share any TCP connection
  // In this case its a HTTP server
	
	var conn = 0;
  http.createServer(function(req, res) {
    res.writeHead(200);
    res.end("hello world\n");
		conn++;
  }).listen(8000);

	setInterval(function(){
		process.send({conn:conn});
		conn = 0;
	},1000);
}
