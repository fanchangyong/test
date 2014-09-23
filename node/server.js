var net = require('net');
var content = new Buffer(1 * 1024 * 1024);
content.fill('#');
net.createServer(function(socket) {
    socket.write(content);
}).listen(3000);
