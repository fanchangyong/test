
var child_process = require('child_process');
var child = child_process.fork('worker.js');

function regChild(child){
	child.on('disconnect',function(){
		regChild(child_process.fork('worker.js'));
	});
}

regChild(child);
