const express = require('express');
const router = express.Router();
const Functions = require('../scripts/Functions')

router.post('/', function(req, res, next){
    var id = req.user.id;
    Functions.withdraw(id)
        .then((stat)=>{
            res.json({STAT: stat});
        });
});

module.exports = router;