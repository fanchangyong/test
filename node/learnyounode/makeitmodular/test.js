var rddir = require('./rddir.js');
//console.log("process argv :",process.argv);
if(process.argv.length<4){
	console.log("Usage: node <program> <dirname> <extfilter>");
	return;
}
var dirname = process.argv[2];
var ext = process.argv[3];
rddir(dirname,ext,function(err,data){
	if(err){
		console.log("error occur:",err);
	}else{
		for(var i=0;i<data.length;i++){
			console.log(data[i]);
		}
	}
});
