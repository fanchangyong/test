var express = require('express');
var router = express.Router();

/* GET home page. */
router.get('/', function(req, res) {
  res.render('index', { title: 'Express' });
});

router.get('/test',function(req,res){
	res.send('test in index.js');
});

router.post('/',function(req,res){
	console.log('req:',req.body);
	res.send(req.body);
});

//router.get('/users',function(req,res){
	//res.send('users in index.js');
//});

module.exports = router;
