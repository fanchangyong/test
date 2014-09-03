var Benchtable = require('benchtable');

/*
 * Sync
 */
var suite = new Benchtable()

suite.addFunction('f1',function(defered){
	setTimeout(function(){
		return defered.resolve();
	},100);
})
.addFunction('f2',function(deferred){
	return 2+2;
})
.addInput('nothing',[])
.on('cycle',function(event) {
	console.log(String(event.target));
})
.on('complete',function(){
	console.log(this.table.toString());
})
.run({async:false});

/*
 * Async
 */
//new Benchtable()
//.add({
	//fn:function(deferred){
		//setTimeout(function(){
			//deferred.resolve();
		//},1000);
	//},
	//defer:true,
	//async:true,
	//maxTime:5,
	//onComplete:function(){
		//console.log('times 3:',this.times);
	//}
//})
//.add({
	//fn:function(deferred){
		//setTimeout(function(){
			//deferred.resolve();
		//},500);
	//},
	//defer:true,
	//async:true,
	//maxTime:5,
	//onComplete:function(){
		//console.log('times 3:',this.times);
	//}
//})

