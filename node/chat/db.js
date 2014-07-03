var mongoose = require('mongoose');

mongoose.connect('mongodb://localhost/chatapp');


var UserSchema = new mongoose.Schema({
	username: String,
	password: String
});

var User = mongoose.model('Users',UserSchema);

GLOBAL.UserSchema = UserSchema;
GLOBAL.User = User;
