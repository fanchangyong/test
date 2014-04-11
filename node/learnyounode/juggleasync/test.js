var argv = process.argv;
if(argv.length<5){
	console.log("Usage: node program <url1> <url2> <url3>");
	return;
}

var printlist = new Array();

for(var i=2;i<5;i++){
	var strings1 = new String();
	http.get(url1,function(res){
		res.setEncoding('utf8');
		res.on('data',function(data){
			strings1 = strings1 + data;
		});
		
		res.on('end',function(){
			console.log(strings1);
		});
	});
}
