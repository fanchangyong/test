var fs = require('fs');
var path = require('path');
module.exports = function(dirname,ext,callback){
  fs.readdir(dirname,function(err,data){
		if(err){
			return callback(err);
		}

		var arr = new Array();

		for (var i=0;i<data.length;i++){
			if(path.extname(data[i])=="."+ext) {
				arr.push(data[i]);
			}
		}
		callback(null,arr);
	})
}

