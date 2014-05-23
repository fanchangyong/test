var http = require('http');


var options = {
	host: '117.121.25.155',
	path: '/', 
	method: 'POST',
	port: 8346,
	headers: {
		'Content-Type': 'application/json'
	}
};

var objs = [
{
	method: 'init',
	params: {
		nickname: 'zc000',
		device_hash: 'IOS-tengxun2'
	}
},
{
	'funfun':'login',
	params: {
		device_hash: 'IOS-tengxun2'
	}
},

{
	method:'missionStart',
		params:{
			device_hash:'IOS-tengxun2',
			missionId:6100101
		}
},
{
	method: 'missionEnd',
	params: {
		device_hash:'IOS-tengxun2',
		missionId:6100101,
		baseScore:1000,
		baseGold:2000,
		killedIndex:10000,
		randomItems:[{typeID:40002,amount:2}]
	}
},
{
	method:'battleStart',
	params:{
		device_hash:'IOS-tengxun2',
		items:[41022]
	}
},

{
	method:'battleEnd',
	params:{
		device_hash:'IOS-tengxun2',
		baseScore:100000,
		baseGold:5000,
		randomItems:[{typeID:41022,amount:1},{typeID:41021,amount:1}],
		killedIndex:5
	}
},

{
	method:'playerRank',
	params:{
		device_hash:'IOS-tengxun2'
	}
},
	

{
	method: 'huntGeneral',
	params: {
		device_hash: 'IOS-tengxun',
		type: 3
	}
},

{
	method: 'recoverItems',
	params: {
		device_hash: 'IOS-tengxun'
	}
},

{
	method: 'armGeneral',
	params: {
		device_hash: 'IOS-tengxun',
		generalTypeID: 1001001,
		index: 0
	}
},

{
	method: 'upgradeGeneral',
	params: {
		device_hash: 'wjvzqjeqfs',
		generalID: '53605ec12ee81a2a353e0a17',
		itemTypeIDs: [41005, 41005]
	}
},

{
	method:'testDeductGold',
	params:{
		device_hash:'IOS-tengxun2',
		reduce:50
	}
},

{
	method:'client_log',
	params:{
		device_hash:'IOS-tengxun',
		strlog:'xxxxxxxxxxxxxxxxxxxxx log',

	}
},

];

function getObj(method){
	for(var i=0;i<objs.length;i++){
		var obj = objs[i];
		if(obj.funfun===method){
			return obj;
		}
	}
}

function send(obj,cb){
	var body = JSON.stringify(obj);
	console.log('body:',body);
	options.headers['Content-Length'] = Buffer.byteLength(body);
	var req = http.request(options, function(res) { 
		var ret = '';
		res.setEncoding('utf8');
		res.on('data', function (data) {
			ret += data;
		});
		res.on('end', function () {
			JSON.parse(ret);
			console.log('ret === ', ret,',obj:',body);
			if(cb){
				cb(null,body);
			}
		});
	});
	req.write(body);
	req.end();
	setTimeout(function(){
		send(obj,cb);
	},10);
}

function mySend(obj){
	var body = JSON.stringify(obj);
	options.headers['Content-Length'] = Buffer.byteLength(body);
	
}

function test(method){
	if(typeof method === 'string'){
		var obj = getObj(method);
		send(obj);
	}else{
		Sync(function(){
			for(var i=0;i<method.length;i++){
				var obj = getObj(method[i]);
				send.sync(null,obj);
			}
		});
	}
}

function testStartMission(){
	test(['init','missionStart']);
}

function testEndMission(){
	test(['init','missionStart','missionEnd']);
}

function testBattle(){
	clearDB();
	test(['init','battleStart','battleEnd']);
}

function testAll(){
	var methods = [];
	for(var i=0;i<objs.length;i++){
		methods.push(objs[i].method);
	}
	test(methods);
}

test('login');

//send({"method":"battleEnd","params":{"device_hash":"mooqaxigil","killedIndex":11,"baseScore":208184,"baseGold":151,"randomItems":[{"typeID":41029,"amount":1}]}});

//testAll();

//for(var i=0;i<objs.length;i++){
	//send(objs[i]);
//}
//testAll();
