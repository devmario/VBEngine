mongoose.connect('mongodb://localhost/GelatoDB');

var Schema = mongoose.Schema;
var ObjectId = Schema.ObjectId;

var Comments = new Schema({
                          title : {type:String},
                          body  : {type:String},
                          date  : {type:Date, default: Date.now}
                          });

var MyModel = mongoose.model('Comments', Comments);
//var instance = new MyModel();
//instance.title = 'hello';
//instance.body = 'body';
//instance.save(function (err) {
//              });

MyModel.find({}, 
             function (err, docs) {
                docs.forEach(
                function(elem, index, array) {
                    res.write(JSON.stringify(elem) + "\n"); 
                });
                res.end();
             });