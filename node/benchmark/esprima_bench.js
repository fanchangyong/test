var esprima = require('esprima');

function foo(arg1,arg2,arg3,arg4,arg5,arg6){

}

var times = 10000000;

var t1 = new Date();

for(var i=0;i<times;i++){
	var names = foo.toString().match(/\((.*?)\)/)[1].match(/[\w]+/g);
}

var t2 = new Date();
console.log('time consume1:',t2-t1);

t1 = new Date();
for(var i=0;i<times;i++){
	var obj = esprima.parse(foo.toString()).body[0].params;
}

t2 = new Date();
console.log('time consume 2:',t2-t1);
