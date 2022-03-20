const express = require('express');
const router = express.Router();
const Functions = require('../scripts/Functions');

router.get('/:userID/todo', function (req, res, next) {
    // 평가자의 ID
    var id = req.params.userID;

    var ret = {};
    Functions.get_not_evaluated(id)
    .then((results)=>{
        ret.todo_list = results.todo_list;
        res.json(ret);
    });

});

router.get('/:userID/evaluated', function (req, res, next) {
    var id = req.params.userID;

    /*
    var ret = {
        // evaluated_list
        // 이 평가자에게 배당되었고, 이미 평가한 파싱 데이터 시퀀스 파일들을 리스트로 받아옴
        // (파일 ID, 파일 타입, 테스크 이름, 회차, 기간, 평가품질 점수, P/NP) 정보가 필요함
        evaluated_list: [
            { id: 1, task: 'android', type: 'type', number: 1, p_np: true},
            { id: 3, task: 'ios', type: 'type', number: 1, p_np: false},
            { id: 7, task: 'windows10', type: 'type', number: 1, p_np: true},
        ]
    };
    res.json(ret);*/

    var ret = {};
    Functions.get_evaluated(id)
    .then((results)=>{
        ret.evaluated_list = results.evaluated_list;
        res.json(ret);
    });
});

router.get('/:userID/todo/:fileID', function (req, res, next) {
    var userID = req.params.userID;
    var fileID = req.params.fileID;

    /*
    res.json({
        // file
        // fileID를 id로 갖는 파싱 데이터 시퀀스 파일에 대한 다음 정보들이 필요함
        // (파일 ID, 파일 타입, 테스크 이름, 회차, 기간, 전체 튜플 수, 중복 튜플 수, Column별 Null 속성 비율, 파일 다운로드 링크)
        file: {
            id: 5,
            type: 'csv',
            task: 'tmp',
            number: 1,
            start_period: '2020-11-22',
            end_period: '2020-11-23',
            all_tuple_number: 30,
            duplicated_tuple_number: 0,
            null_col_rate: {
                colA: 0,
                colB: 0,
                colC: 0,
                colD: 0
            },
            download_link: 'http://blahblah....'
        }
        // file: {}
    })*/
    ret = {};
    Functions.get_parsing_data_info(fileID)
    .then((results)=>{
        ret.file = results[0];
        table_name = results[0].table_name;
        var columns = [];
        Functions.get_columns(table_name)
        .then((results)=>{
            for(i = 0; i < results.columns.length; i ++){
                columns.push(results.columns[i].column_name);
            }
            Functions.get_null_values(fileID, table_name, columns)
            .then((results)=>{
                ret.file.null_col_rate = results;
                res.json(ret);
            })
        });
    });
});

router.post('/:userID/todo/:fileID', function (req, res, next) {
    // string 타입
    var fileID = req.params.fileID;
    // number 타입
    var score = req.body.score;
    // Pass이면 "Pass", Non pass이면 "Non-Pass"라는 string으로 옴
    var p_np = req.body.p_np;

    // fileID를 ID로 갖는 파싱 데이터 시퀀스 파일에 평가 점수와 P/NP 정보를 저장함.

    if(p_np == 'pass'){
        Functions.update_user_score(fileID, score)
        .then((results)=>{
            Functions.evaluate(fileID, score, p_np);
            Functions.get_mapping_schema(fileID)
            .then((results)=>{
                schema_info = JSON.parse(results[0].schema_info);
                table_name = results[0].table_name;
                task_name = results[0].task_name;
                task_table_name = results[0].task_table_name;
                var columns = [];
                Functions.get_columns(table_name)
                .then((results)=>{
                    for(i = 0; i < results.columns.length; i ++){
                        columns.push(results.columns[i].column_name);
                    }
                    Functions.get_file(fileID, table_name)
                    .then((results)=>{
                        var tuples = results;
                        Functions.put_into_task_table(task_table_name, tuples, columns, schema_info)
                        .then((stat)=>{
                            console.log(stat);
                            res.json({stat:stat});
                        })
                    });
                });
            })
        });
    } else {
        Functions.update_user_score(fileID, score)
        .then((results)=>{
            Functions.evaluate(fileID, score, p_np)
            .then((stat)=>{
                res.json({stat:0});
            });
        });
    }

    // 저장 성공 여부 전송
    // 성공이면 true, 실패면 false
})

module.exports = router;
