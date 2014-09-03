// import module
var Benchtable = require('benchtable');

// create benchtable suite
var suite = new Benchtable();

// add functions
suite.addFunction('RegExp#test', function(s) { /o/.test(s) })
.addFunction('String#indexOf', function(s) {s.indexOf('o') > -1;})

// add inputs
.addInput('Short string', ['Hello world!'])
.addInput('Long string', ['This is a very big string, isnt it? It is. Really. So, hello world!'])
.addInput('Very long string', ['This is a ' + new Array(200).join("very ") + 'big string, isnt it? It is. Really. So, hello world!'])
.addInput('Extremely long string', ['This is a ' + new Array(20000).join("very ") + 'big string, isnt it? It is. Really. So, hello world!'])

// add listeners
.on('cycle', function(event) {
  console.log(String(event.target));
})
.on('complete', function() {
  console.log('Fastest is ' + this.filter('fastest').pluck('name'));
  console.log(this.table.toString());
})

// run async
.run({ 'async': false });
