var express = require('express');
var router = express.Router();

router.get('/', function(req, res) {
	var username = req.query['username'];
	var pwd = req.query['password'];
	if(!username || !pwd){
		res.render('login',{title:'Login As'});
	}else{
		res.render('logged');
	}
});

router.get('/user',function(){
	console.log('login usr');
});

module.exports = router;
