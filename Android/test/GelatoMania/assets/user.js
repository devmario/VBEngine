mongoose.connect('mongodb://localhost/GelatoDB');

var Schema = mongoose.Schema;
var ObjectId = Schema.ObjectId;

var UISchema = new Schema({
                          
});

var StageSchma = new Schema({
                            id_pack     : {type:ObjectId, index:true},
                            id_stage    : {type:ObjectId, index:true},
                            is_lock     : {type:Boolean},
                            per_clear   : {type:Number, min:0, max:100}
                            });

var UserSchema = new Schema({
                            id_user         : {type:ObjectId, index:true},
                            id_facebook     : {type:String},
                            id_mobage       : {type:String},
                            stages          : [StageSchma],
                            friends         : [ObjectId],
                            date_first      : {type:Date},
                            date_last       : {type:Date, default: Date.now},
                            num_play_count  : {type:Number, default:0, min:0},
                            ui              : {
                                
                            }
                            });

var UserModel = mongoose.model('UserSchema', UserSchema);

var obj = new UserModel();
obj.id_facebook = 'jang won hee';
obj.body = 'body';
obj.save(function (err) {
         });

UserModel.find({}, 
               function (err, docs) {
               docs.forEach(
                            function(element, index, array) {
                            res.write(JSON.stringify(element) + "\n"); 
                            });
               res.end();
               });