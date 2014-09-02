var cluster = require('cluster');
var http = require('http');
var numCPUs = require('os').cpus().length;

function fork(){
	var worker = cluster.fork();
	worker.on('message',function(msg){
		if(msg=='crash'){
			fork();
		}
	});
}

if (cluster.isMaster) {
	for (var i = 0; i < numCPUs; i++) {
		fork();
	}
} else {
	setInterval(function(){
		console.log('child crash...');
		cluster.worker.send('crash');
		process.exit(0);
	},2000);
}
