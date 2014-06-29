var mongoose = require('mongoose');

mongoose.connect('mongodb://localhost/test');
var db = mongoose.connection;
db.on('error', console.error.bind(console, 'connection error:'));
db.once('open', function callback () {
	console.log("opened");
});

var kittySchema = mongoose.Schema({
	name:String
});

kittySchema.methods.speak = function(){
	var greeting = this.name
		? "Meow name is " + this.name
		: "I don't have a name";
	console.log(greeting);
}

var Kitten = mongoose.model('kitten',kittySchema);

var silence = new Kitten({name:"Silence"});

silence.save(function(err,kit){
	if(err) return console.error(err);
	kit.speak();
});

Kitten.findOne(function(err,kittens){
	if(err) return console.log(err);
	console.log("kittens is:",kittens);
}).select('name name name name').exec();
