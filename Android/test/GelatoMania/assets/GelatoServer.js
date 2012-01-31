var http = require('http');
var url = require('url');
var mongoose = require('mongoose');

var req, res;

function EvalServer(_req, _res) {
    req = _req;
    res = _res;
    try {
        res.writeHead(200, "OK", {'Content-Type': 'text/html'});
        if (req.method == 'POST') {
            var fullBody = '';
            
            req.on('data', 
            function (chunk) {
                   fullBody += chunk.toString();
            });
            
            req.on('end',
            function() {
                   
                   try {
                   eval(fullBody);
                   } catch (e) {
                   res.write("Error:" + e);
                   res.end();
                   }
            });
        }
    } catch (err) {
        res.write("Error:" + err);
        res.end();
    }
}

http.createServer(EvalServer).listen(80);