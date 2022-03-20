const express = require('express');
const router = express.Router();
const Functions = require('../scripts/Functions')

router.post('/', function(req, res, next){
    var id = req.user.id;
    var password = req.body.password;
    var phone_number = req.body.phone_number;
    var address = req.body.address;

    Functions.user_edit(id, password, phone_number,address)
        .then((stat)=>{
            res.json({STAT: stat});
        });
});

module.exports = router;