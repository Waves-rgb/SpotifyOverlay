const net = require('net');
const cfg = require('./cfg.json');
const axios = require('axios');

net.createServer(function(socket) {
    console.log(`CONNECTION: ${socket.remoteAddress}:${socket.remotePort}`);
    if (socket.remoteAddress !== '127.0.0.1') {
        socket.write('Access denied');
        return socket.end();
    }

    socket.on('data', function(data) {
        switch (data.toString()) {
            case 'getVersion':
                socket.write(cfg.version);
                break;
            case 'getLatest':

                break;
        }

        socket.end();

    })

    socket.on('end', function() {
        console.log(`END: ${socket.remoteAddress}:${socket.remotePort}`);
    });
}).listen(cfg.port, () => {
    console.log(`Server listening on port ${cfg.port}`);
});
