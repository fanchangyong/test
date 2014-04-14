// called as a normal function

var obj = {value:1};
obj.double = function(){
	// that指向的是obj,为的是使helper函数可以访问到外部函数的"this"
	// 参见JavaScript语言精粹第4章
	var that = this;    
	
	var helper = function(){
		that.value = that.value+that.value;
	};

	helper();
};

obj.double();
console.log(obj.value);
