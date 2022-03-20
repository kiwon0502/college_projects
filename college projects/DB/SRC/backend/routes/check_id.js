const express = require('express');
const router = express.Router();
const Functions = require('../scripts/Functions')

router.post('/', function(req, res, next){
    var id = req.body.id;
    Functions.check_id(id)
        .then((stat)=>{
            res.json({STAT: stat});
        });
});

module.exports = router;