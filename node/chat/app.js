var express = require('express');
var app = express();
var http = require('http').Server(app);
var io = require('socket.io')(http);
var session = require('express-session');
var db = require('./db');
var bodyParser = require('body-parser');
var session = require('express-session');
var cookieParser = require('cookie-parser');
var auth = require('./auth.js');
var randomColor = require('randomcolor');

app.set('views',__dirname);
app.set('view engine','ejs');

app.use(bodyParser.urlencoded({extended:true}));
app.use(bodyParser.json());
app.use(cookieParser());
app.use(session({secret:'ChatRoom'}));

app.get('/',function(req,res){
	if(req.session.user){
		res.render('chat',{username:req.session.user.username});
	}else{
		res.sendfile('index.html');
	}
});

app.get('/login',function(req,res){
	res.sendfile('login.html');
});

app.post('/login',function(req,res){
	console.log('post login,body:',req.body);
	auth.authUser(req.body.username,req.body.password,function(err,user){
		if(err){
			var obj={result:'fail',value:err};
			res.end(JSON.stringify(obj));
		}else{
			req.session.user = user;
			var obj={result:'ok'};
			res.end(JSON.stringify(obj));
		}
	});
});

app.get('/regist',function(req,res){
	res.sendfile('regist.html');
});

app.post('/regist',function(req,res){
	auth.registUser(req.body.username,req.body.password,function(err,user){
		if(err){
			return send(err);
		}
		req.session.user = user;
		res.redirect('/');
	});
});

app.post('/logout',function(req,res){
	req.session.destroy();
	var str=JSON.stringify({result:'ok'});
	res.end(str);
});

app.use(express.static(__dirname));

var userAndColors = {};

io.on('connection', function(socket){
	socket.on('tellname',function(username){
		var color = randomColor();
		console.log('assign %s to %s ',color,username);
		userAndColors[username]=color;
		socket.emit('color',color);
	});

	socket.on('chat message',function(obj){
		var username = obj.username;
		obj.color = userAndColors[username];
		console.log('using %s for %s',obj.color,username);
		io.emit('chat message',obj);
	});

	socket.on('disconnect',function(){
		io.emit('user disconnect');
	});
});

var port = 4000;
http.listen(port, function(){
  console.log('listening on *:'+port);
});
