const express = require('express');
const router = express.Router();
const Functions = require('../scripts/Functions')

router.post('/', function(req, res, next){
    // 이름, 설명, 최소업로드 주기, 데이터 테이블 이름, 데이터 테이블 스키마, 원본 데이터 타입
    // 자신의 테스크 목록 불러오기

    var id = req.user.id;

    var ret = {};
    Functions.get_user_tasks_and_score(id)
    .then((result)=>{
        ret.items = result.items;
        ret.score = result.score[0].score;
        res.json(ret)
    });
});

router.post('/:taskName', function(req, res, next){
    var name = req.params.taskName;
    /*
    var ret = {
        type: [
            {typeName: 'type1-1'},
            {typeName: 'type1-2'}
        ],
    };*/

    var ret = {};
    Functions.get_task_source_data_types(name)
    .then((results)=>{
        ret.type = results.type;
        res.json(ret);
    });
});

router.post('/:taskName/:typeName', function(req, res, next){
    // 원본 데이터 타입에 따른 제출한 파일 목록, 회차, pass 여부
    // submitFiles 의 데이터는 subNum(회차) 순으로 정렬
    // 테스크에 체출한 총 파일 수, pass한 총 튜플 수(모든 원본 데이터 타입에 제출된 총 수)
    var name = req.params.typeName;
    var ret = {};
    Functions.get_source_data_type_info(req.user.id, name)
    .then((results)=>{
        console.log(ret);
        ret.submitFiles = results.submitFiles;
        ret.subFileNum = results.subFileNum[0]['count(*)'];
        ret.tupleNum = results.tupleNum[0]['count(*)'];
        res.json(ret);
    })
});

module.exports = router;