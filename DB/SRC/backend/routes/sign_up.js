const express = require('express');
const router = express.Router();
const Functions = require('../scripts/Functions')

router.post('/', function(req, res, next){
    var id = req.body.id;
    var password = req.body.password;
    var name = req.body.name;
    var phone_number = req.body.phone_number;
    var address = req.body.address;
    var birthday = req.body.birthday;
    var type = req.body.type;

    Functions.user_sign_up(id, password, name, phone_number, address, birthday, type)
        .then((stat)=>{
            res.json({STAT: stat});
        });
});

module.exports = router;