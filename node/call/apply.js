function add(a,b){
	return a+b;
}
var array = [3,4];
var sum = add.apply(null,array);

console.log("sum:",sum);

var Quo = function(str){
	this.stat = str;
}

Quo.prototype.get_stat=function(){
	return this.stat;
}

var statusObj={
	stat:"A-OK"
};
var st = Quo.prototype.get_stat.apply(statusObj);
console.log("st:",st);
