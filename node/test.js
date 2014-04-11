var x = 0;
function test(){
	console.log("this x is:",this.x);
}

var o = {};
o.x = 1;
o.m = test;

o.m.apply(o);

console.log("this in global:",this);
