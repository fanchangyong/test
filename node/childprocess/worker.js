process.on('uncaughtException',function(){
	console.log('exception,my pid:',process.pid);
	process.exit(1);
});

setTimeout(function(){
	throw new Error('myerror');
},1000);
