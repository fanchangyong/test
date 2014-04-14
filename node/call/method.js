// function as an object's attributes is a method
var obj = {
	value:0,
	incr:function(){
		this.value += 1;
	}
}

obj.incr();
console.log(obj.value);
