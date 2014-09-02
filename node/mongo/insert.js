var MongoClient = require('mongodb').MongoClient

MongoClient.connect('mongodb://127.0.0.1:27017/tmpdb',function(err,db){
	if(err){
		return console.log('connnect err:',err);
	}

	var collection = db.collection('test_insert');
	for(var i=0;i<100000000000;i++){
		collection.insert({i:i},function(err,docs){
			if(err){
				return console.log('insert err:',err);
			}
			console.log('docs:',docs);
		});
	}

	collection.count(function(err,count){
		console.log('count:',count);
		db.close();
	});
})
