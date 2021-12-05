const express = require('express');
const router = express.Router();
const Functions = require('../scripts/Functions')

router.post('/', function(req, res, next){
    // 신청한 task 이름
    // 제출자 id

    var id = req.body.userID;
    var taskname = req.body.taskName;
    Functions.user_apply_task(id, taskname)
    .then((stat)=>{
        res.json({stat:stat});
    })
});

module.exports = router;