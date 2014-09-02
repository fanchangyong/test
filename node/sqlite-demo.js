var sqlite3 = require('sqlite3').verbose();
go();

function go()
{
    var db = new sqlite3.Database(':memory:');
	db.serialize(function () {
		db.run("CREATE TABLE lorem (info TEXT)");
		var stmt = db.prepare("INSERT INTO lorem VALUES (?)");
		for (var i = 0; i < 10; i++) {
			stmt.run("Ipsum " + i);
		}
		stmt.finalize();
		db.exec("SELECT rowid AS id, info FROM lorem", function () {
			db.close();
			go();
		});
	});
}