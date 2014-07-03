
exports.authUser = function(uname,pass,cb){
	User.findOne({username:uname},function(err,user){
		if(user){
			if(user.password===pass){
				return cb(null,user);
			}else{
				return cb('invalid password!');
			}
		}else{
			console.log('uname:',uname);
			return cb('no user!');
		}
	});
}

exports.registUser = function(uname,pass,cb){
	console.log('regist user:',uname,',pass:',pass);
	var user = new User({username:uname,password:pass});

	user.save(function(err,newUser){
		if(err){
			return cb(err);
		}
		return cb(null,newUser);
	});
}
