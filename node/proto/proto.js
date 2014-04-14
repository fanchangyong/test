
function Foo(){

}

var proto={
	str:"hello",
	fun:function(){
		console.log("calling proto.fun");
	}
}

Foo.prototype = proto

var f = new Foo;
f.fun();
console.log("f str:",f.str);

proto.str = "world";
proto.fun=function(){
	console.log("**** calling new proto function ***");
}
console.log("f str:",f.str);
f.fun();
