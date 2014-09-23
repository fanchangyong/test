var http = require('http');
var num = 0;
http.createServer(function (req, res) {
  res.writeHead(200, {'Content-Type': 'text/plain'});
  res.end('Hello World\n');
	num=num+1;
}).listen(1337);
setInterval(function(){
	console.log('current connections:',num);
	num = 0;
},1000);
console.log('Server running at http://127.0.0.1:1337/');
