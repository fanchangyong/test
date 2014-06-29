var MongoClient = require('mongodb').MongoClient
	, format = require('util').format
	, fs = require('fs');

var roleId = process.argv[2];
if(!roleId){
	console.log('请输入角色名称!');
	process.exit(1);
}
console.log('roleid:',roleId);

var url = 'mongodb://e.blingstorm.com.cn:27017/testlogdb';

MongoClient.connect(url,function(err,db){
	if(err) throw err;

	var collection = db.collection('logs');

	collection.find({'eventName':'battleLog','roleID':roleId},{'battleLog':1}).toArray(function(err,entries){
		if(err){
			throw err;
		}
		console.log('length:',entries.length);
		for(var i=0;i<entries.length;i++){
			fs.appendFileSync('battleLogs_'+roleId,JSON.stringify(entries[i])+'\r\n');
		}
		process.exit(0);
	});

})
