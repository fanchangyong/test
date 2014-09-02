
console.log('require==requirejs:',require==requirejs);
require.config({
	baseUrl:'lib'
});

require(['app/app.js']);
