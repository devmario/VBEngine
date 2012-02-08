mongoose.connect('mongodb://localhost/mania');

var Schema = mongoose.Schema;
var ObjectId = Schema.ObjectId;

var FriendSchma = new Schema({
                             is_friend  : {type:Boolean, default:false},
                             req_id     : {type:ObjectId},
                             res_id     : {type:ObjectId}
                             });

var FriendModel = mongoose.model('friends', FriendSchma);

var UserSchema = new Schema({
                            //페이스북
                            facebookID          : {type:String, default:null},
                            
                            //트위터
                            twitterID           : {type:String, default:null},
                            
                            //게임센터
                            gameCenterID        : {type:String, default:null},
                            gameCenterAlias     : {type:String, default:null},
                            
                            //모바게
                            mobageID            : {type:String, default:null},
                            
                            //돈
                            money               : {type:Number, default:0, min:0}
                            });

var UserModel = mongoose.model('users', UserSchema);

var result = new Object();
var action = url.parse(req.url, true).pathname;
var query = url.parse(req.url, true).query;

function queryToMongoDBq(_q) {
    var _o = {};
    if(_q.money != undefined) {
        if(_o.$inc == undefined)
            _o.$inc = {};
        _o.$inc.money = _q.money;
    }
    if(_q.num_play_count != undefined) {
        if(_o.$inc == undefined)
            _o.$inc = {};
        _o.$inc.num_play_count = _q.num_play_count;
    }
    _o.$set = {};
    _o.$set.date_last = new Date();
    if(_q.facebookID != undefined)
        _o.$set.facebookID = _q.facebookID;
    if(_q.twitterID != undefined)
        _o.$set.twitterID = _q.twitterID;
    if(_q.gameCenterID != undefined)
        _o.$set.gameCenterID = _q.gameCenterID;
    if(_q.gameCenterAlias != undefined)
        _o.$set.gameCenterAlias = _q.gameCenterAlias;
    if(_q.mobageID != undefined)
        _o.$set.mobageID = _q.mobageID;
    return _o;
}

function queryToModel(_q) {
    var _o = new UserModel();
    if(_q.money != undefined)
        _o.money = _q.money;
    if(_q.num_play_count != undefined)
        _o.num_play_count = _q.num_play_count;
    _o.date_first = new Date();
    _o.date_last = new Date();
    if(_q.facebookID != undefined)
        _o.facebookID = _q.facebookID;
    if(_q.twitterID != undefined)
        _o.twitterID = _q.twitterID;
    if(_q.gameCenterID != undefined)
        _o.gameCenterID = _q.gameCenterID;
    if(_q.gameCenterAlias != undefined)
        _o.gameCenterAlias = _q.gameCenterAlias;
    if(_q.mobageID != undefined)
        _o.mobageID = _q.mobageID;
    return _o;
}

function getUserCallback(error, docs) {
    if(error == null) {
        result["success"] = 1;
        result["users"] = docs;
    } else {
        result["success"] = 0;
        result["error"] = error;
    }
    res.write(JSON.stringify(result) + "\n");
    res.end();
}

function getUserOneCallback(error, doc) {
    if(error == null) {
        result["success"] = 1;
        result["user"] = doc;
    } else {
        result["success"] = 0;
        result["error"] = error;
    }
    res.write(JSON.stringify(result) + "\n");
    res.end();
}

function setUserCallback(error) {
    if(error == null) {
        result["success"] = 1;
    } else {
        result["success"] = 0;
        result["error"] = error;
    }
    res.write(JSON.stringify(result) + "\n");
    res.end();
}

function updateUserCallback(error) {
    if(error == null) {
        UserModel.findOne({_id: query._id}, getUserOneCallback);
    } else {
        result["success"] = 0;
        result["error"] = error;
        res.write(JSON.stringify(result) + "\n");
        res.end();
    }
}

function saveFriendReqCallback(error) {
    if(error == null) {
        //친구요청 노티피케이션 날려야함
        result["success"] = 1;
    } else {
        result["success"] = 0;
        result["error"] = error;
    }
    res.write(JSON.stringify(result) + "\n");
    res.end();
}

function getAlreadyFriendListCallback(error, docs) {
    if(error == null) {
        if(docs.length < 1) {
            //없으면필드에 저장
            var friendObj = new FriendModel();
            friendObj.is_friend = false;
            friendObj.req_id = query.req_id;
            friendObj.res_id = query.res_id;
            result["friend"] = friendObj;
            friendObj.save(saveFriendReqCallback);
        } else {
            //이미 있으면 에러
            result["success"] = 0;
            result["error"] = error;
            res.write(JSON.stringify(result) + "\n");
            res.end();
        }
    } else {
        result["success"] = 0;
        result["error"] = error;
        res.write(JSON.stringify(result) + "\n");
        res.end();
    }
}

function getFriendRequestListCallback(error, docs) {
    if(error == null) {
        result["success"] = 1;
        result["friends"] = docs;
    } else {
        result["success"] = 0;
        result["error"] = error;
    }
    res.write(JSON.stringify(result) + "\n");
    res.end();
}

function acceptFriendCallback(error) {
    if(error == null) {
        //친구됬다고 요청자에게 노티피케이션
        result["success"] = 1;
    } else {
        result["success"] = 0;
        result["error"] = error;
    }
    res.write(JSON.stringify(result) + "\n");
    res.end();
}

function disacceptFriendCallback(error) {
    if(error == null) {
        //친구 거절됬다고 요청자에게 노티피케이션
        result["success"] = 1;
    } else {
        result["success"] = 0;
        result["error"] = error;
    }
    res.write(JSON.stringify(result) + "\n");
    res.end();
}

if(action == "/newUser") {
    if(query.gameCenterID != undefined || query.facebookID != undefined || query.twitterID != undefined || query.mobageID != undefined) {
        var obj = queryToModel(query);
        result["user"] = obj;
        obj.save(setUserCallback);
    } else {
        result["success"] = 0;
        result["error"] = "id empty";
        res.write(JSON.stringify(result) + "\n");
        res.end();
    }
} else if(action == "/getUser") {
    if(query._id != undefined || query.gameCenterID != undefined || query.facebookID != undefined || query.twitterID != undefined || query.mobageID != undefined) {
        var _q = {};
        if(query._id != undefined)
            _q._id = query._id;
        if(query.gameCenterID != undefined)
            _q.gameCenterID = query.gameCenterID;
        if(query.twitterID != undefined)
            _q.twitterID = query.twitterID;
        if(query.facebookID != undefined)
            _q.facebookID = query.facebookID;
        if(query.mobageID != undefined)
            _q.mobageID = query.mobageID;
        UserModel.find(_q, getUserCallback);
    } else {
        result["success"] = 0;
        result["error"] = "_id empty";
        res.write(JSON.stringify(result) + "\n");
        res.end();
    }
} else if(action == "/updateUser") {
    if(query._id != undefined) {
        UserModel.update({_id:query._id}, queryToMongoDBq(query), {multi:false}, updateUserCallback);
    } else {
        result["success"] = 0;
        result["error"] = "_id empty";
        res.write(JSON.stringify(result) + "\n");
        res.end();
    }
} else if(action == "/addFriend") {
    if(query.res_id != undefined && query.req_id != undefined) {
        FriendModel.find({$or:[{res_id:query.res_id}, {req_id :query.req_id}]}, getAlreadyFriendListCallback);
    } else {
        result["success"] = 0;
        result["error"] = "_id empty";
        res.write(JSON.stringify(result) + "\n");
        res.end();
    }
} else if(action == "/acceptFriend") {
    if(query._id != undefined) {
        var q_f = FriendModel.where('is_friend').ne(true);
        if(q_f.length > 0)
            q_f.update({_id:query._id}, {$set:{is_friend:true}}, {multi:false}, acceptFriendCallback);
        else {
            result["success"] = 0;
            res.write(JSON.stringify(result) + "\n");
            res.end();
        }
    } else {
        result["success"] = 0;
        result["error"] = "_id empty";
        res.write(JSON.stringify(result) + "\n");
        res.end();
    }
} else if(action == "/disacceptFriend") {
    if(query._id != undefined) {
        var q_f = FriendModel.where('is_friend').ne(true);
        if(q_f.length > 0)
            q_f.remove({_id:query._id}, disacceptFriendCallback);
        else {
            result["success"] = 0;
            res.write(JSON.stringify(result) + "\n");
            res.end();
        }
    } else {
        result["success"] = 0;
        result["error"] = "_id empty";
        res.write(JSON.stringify(result) + "\n");
        res.end();
    }
} else if(action == "/showFriendList") {
    if(query._id != undefined) {
        FriendModel.where('is_friend').find({$or:[{res_id:query._id}, {req_id :query._id}]}, function(error,docs) {
                                            res.write(JSON.stringify(docs) + "\n");
                                            res.end();
                                            });
    } else {
        result["success"] = 0;
        result["error"] = "_id empty";
        res.write(JSON.stringify(result) + "\n");
        res.end();
    }
} else if(action == "/getFriendRequestList") {
    if(query._id != undefined) {
        FriendModel.where('is_friend').ne(true).find({res_id:query._id}, getFriendRequestListCallback);
    } else {
        result["success"] = 0;
        result["error"] = "_id empty";
        res.write(JSON.stringify(result) + "\n");
        res.end();
    }
}
