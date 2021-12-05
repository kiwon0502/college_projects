const express = require('express');
const router = express.Router();
const Functions = require('../scripts/Functions')

router.get('/', function(req, res, next){
  // 회원 정보
  /*
    var ret = {
      member_list: [                                            // 참여자 리스트
          {id: '2015147531', name: '서기원', role: 'evaluator', gender: 'm', taskList:['1','2']},
          {id: '2015147533', name: '유현석', role: 'user', gender: 'm', taskList:['6','7']},
          {id: '2015147562', name: '이의동', role: 'user', gender: 'm', taskList:['9','8']},
          {id: '2015147563', name: '류동철', role: 'user', gender: 'm', taskList:['4','3']},
        ]
    };*/
    
    var ret = {};
    Functions.get_members()
    .then((results=>{
      ret.member_list = results;
      res.json(ret);
    }));
});

router.get('/:userID', function(req, res, next){
  var user_id = req.params.userID;
  // 회원 상세 정보
  // 참여자이면 참여 task_info를 받아서 전달, 평가자이면 평가한 file_info를 받아서 전달
  // 참여자이면 file_info에 빈칸 전달
  // 평가자이면 task_info에 빈칸 전달
  // 빈칸 전달하면 알아서 처리됨 ㅇㅇ
  /*
    var ret = {
      user_info: [{id: '2015147531', name: '서기원', role: '제출자', gender: 'm', taskList: ['1','2']}],
      task_info: [
        {name: '생각보다 어려웠다', fileNumber: '10', tupleNumber: '1000', nullProperty: '5'},
        {name: '생각보다 어려웠다1', fileNumber: '10', tupleNumber: '1000', nullProperty: '5'},
        {name: '생각보다 어려웠다2', fileNumber: '10', tupleNumber: '1000', nullProperty: '5'},
        {name: '생각보다 어려웠다3', fileNumber: '10', tupleNumber: '1000', nullProperty: '5'},
        {name: '생각보다 어려웠다4', fileNumber: '10', tupleNumber: '1000', nullProperty: '5'},
      ],
      file_info: [
        {id: '1', score: '10', pnp: 'pass'},
        {id: '2', score: '6', pnp: 'pass'},
        {id: '3', score: '4', pnp: 'non-pass'},
        {id: '4', score: '1', pnp: 'non-pass'},
      ]
    };
    res.json(ret)*/

  
    var ret = {};
    Functions.get_member_info(user_id)
    .then((results)=>{
      ret.user_info = results.user_info;
      role = results.user_info[0].role;
      if(role == 'SUBMITTER'){
        Functions.get_submitter_info(user_id)
        .then((results)=>{
          ret.user_info[0].role = '제출자';
          ret.user_info.taskList = results.taskList;
          ret.task_info = results.task;
          res.json(ret);
        })

      } else if(role == 'EVALUATOR'){
        Functions.get_evaluator_info(user_id)
        .then((results)=>{
          ret.user_info[0].role = '평가자';
          ret.file_info = results;
          res.json(ret);
        })
      } else if(role == 'ADMINISTRATOR'){
        ret.user_info[0].role = '관리자';
        res.json(ret);
      }
    })
});

router.post('/search', function (req, res, next) {

  // 검색어 모음
  
  var ret = {
    member_list: [                                            // 참여자 리스트
        {id: '2015147531', name: '서기원', role: 'evaluator', gender: 'm', taskList:['1','2']},
        {id: '2015147533', name: '유현석', role: 'evaluator', gender: 'm', taskList:['6','7']},
        //{id: '2015147562', name: '이의동', role: 'user', gender: 'm', taskList:['9','8']},
        //{id: '2015147563', name: '류동철', role: 'user', gender: 'm', taskList:['4','3']},
      ]
  };
  
  var ret = {};
  Functions.get_search_users()
  .then((results)=>{
    var search_info = {
      id : req.body.userId,
      age : req.body.userAge,
      role : req.body.userRole 
    }
    currentYear = new Date().getFullYear();
    users = results;
    member_list = [];
    for(i = 0; i < users.length; i ++){
      valid = true;
      user = users[i];
      for(j = 0; j < 3; j ++){
        key = Object.keys(search_info)[j];
        if(search_info[key] == '') continue;
        if(key == 'age'){
          birthYear = parseInt(String(user.birthday).split(' ')[3]);
          if((currentYear - birthYear).toString() != search_info[key]){
            valid = false;
          }
        } else if(key == 'role'){
          if(user.role == 'SUBMITTER' && search_info[key] != '제출자'){
            valid = false;
          } else if(user.role == 'EVALUATOR' && search_info[key] != '평가자'){
            valid = false;
          } else if(user.role == 'ADMINISTRATOR' && search_info[key] != '관리자'){
            valid = false;
          }
        } else if(search_info[key] != user[key]){
            valid = false;
        }
      }
      if(valid) member_list.push(user);
    }
    ret.member_list = member_list;
    res.json(ret);
  })
  
});

module.exports = router;