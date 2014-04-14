var Quo = function(str){
	this.status = str;
}

Quo.prototype.get_status = function(){
	return this.status;
}

var myQuo = new Quo("confused");
var st = myQuo.get_status();
console.log(st);
