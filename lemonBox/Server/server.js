var Datastore = require('nedb')
  , db = new Datastore({ filename: 'data/main', autoload: true });
// You can issue commands right away
db.users = new Datastore({ filename: 'data/users', autoload: true });
db.devices = new Datastore({ filename: 'data/devices', autoload: true });

var express = require('express')
  , net = require('net')
  , http = require('http')
  , path = require('path')
  , fs = require('fs')

var compress = require('compression')();

var app = express();
var clients = [];

GLOBAL.app = app;



app.set('port', process.env.PORT || 1337);


app.use(express.static("SPA"));
app.use(compress);


var server = http.createServer(app).listen(app.get('port'), function(){
  console.log('Starting Lemon Seed ' + app.get('port'));
});

app.get('/api/devices/add/:id', function (req, res) {
	getDevice("",{id:req.param("id")}, function(results){

		console.log(results);
		if (results.length > 0){
			
			return;
		}else{
			addDevice("",{id:req.param("id"), name:"lampie",user:"Zaku"});
			res.end("ok")
		}
	});

});
app.get('/*', function (req, res) {
  fs.readFile('SPA/index.html', 'utf8', function(err, text){
        res.send(text);
    });

});










function addDevice(token, device){
	db.devices.insert(device, function (err, newDoc) {   // Callback is optional
	  // newDoc is the newly inserted document, including its _id
	  // newDoc has no key called notToBeSaved since its value was undefined
	  console.log(err);
	});

}

function addUser(token, user){
	db.devices.insert(user, function (err, newDoc) {   // Callback is optional
	  // newDoc is the newly inserted document, including its _id
	  // newDoc has no key called notToBeSaved since its value was undefined
	  console.log(err);
	});

}

function getUser(token, user){


	db.find({ user: 'Zaku' }, function (err, docs) {
	  // docs is an array containing documents Mars, Earth, Jupiter
	  // If no document is found, docs is equal to []
	  console.log(docs);
	});
}

function getDevice(token, device, cb){

	db.devices.find({ id: device.id }, function (err, docs) {
	  // docs is an array containing documents Mars, Earth, Jupiter
	  // If no document is found, docs is equal to []
	  console.log(docs);
	  cb(docs);
	});
}