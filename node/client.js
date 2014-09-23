var net = require('net');
var client = net.connect({
    host: 'localhost',
    port: 3000
}, function() {
    client.destroy();
});

