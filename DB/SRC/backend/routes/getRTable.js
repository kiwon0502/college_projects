const express = require('express');
const router = express.Router();
const Functions = require('../scripts/Functions')

router.post('/', function(req, res, next){
    // Task 정보
    var id = req.user.id;
        // rTask : 제출자가 신청할 수 있는 테스크 정보
        // wTask : 신청 대기 중에 있는 테스크 정보 

    var ret = {};
    Functions.get_appliable_tasks(id)
    .then((results)=>{
        ret.rTask = results.rTask;
        ret.wTask = results.wTask;
        res.json(ret);
    })
});

module.exports = router;