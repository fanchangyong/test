var express = require('express');
var router = express.Router();

router.get('/', function(req, res) {
	res.render('login',{title:'Login As'});
});

router.post('/',function(req,res){
	console.log('body:',req.body);
	res.send('ok!');
})

module.exports = router;
