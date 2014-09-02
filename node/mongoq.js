
var mongodb = require('mongo-q')();
mongodb.MongoClient.connectQ('mongodb://127.0.0.1:27017/test')
	.then(function(db){
		return db.collectionQ('test')
	})
	.then(function(coll){
		coll.insertQ({testing_data:1111});
		return coll;
	})
	.then(function(coll){
		return coll.findQ();
	})
	.then(function(cursor){
		throw new Error('intentional error');
		return cursor.toArrayQ();
	})
	.then(function(result){
		return console.log('result is:',result);
	})
	.fail(function(err){
		console.log('err:',err);
		throw new Error('Error in fail Again!');
	})
.done(function(){
	console.log('done');
},function(){
	console.log('done err:',arguments);
});
