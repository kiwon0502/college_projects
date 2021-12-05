// Functions.js
// DB를 사용하는 function들을 정의    

const DBConn = require('./DBConnection.js');
const stats = require('./Stats.js');

async function compute_db1(name, source_data_types, table_name){
  var res = {};
  var temp = 0;
  for(var i = 0; i < source_data_types.length; i ++){
    source_data_type = source_data_types[i].table_name;
    query = 'select count(*) from '+source_data_type;
    results = await DBConn.MakeQuery(query);
    temp += results[0]['count(*)'];
  }
  res.data_type_level_tuple_num = temp;

  query = 'select count(*) from '+table_name;
  results = await DBConn.MakeQuery(query);
  res.passed_tuple_num = results;

  query = 'select column_name as value, column_name as text from information_schema.columns where table_schema = \'main_db\' and table_name = \''+tablename+'\'';
  results = await DBConn.MakeQuery(query);
  res.task_schema = results; 

  query = 'select column_name as a from information_schema.columns where table_schema = \'main_db\' and table_name = \''+tablename+'\'';
  results = await DBConn.MakeQuery(query);
  res.task_schema2 = results; 
  
  var temp = []
  for(i = 0; i < source_data_types.length; i ++){
    source_data_type = source_data_types[i].table_name;
    query = 'select column_name from information_schema.columns where table_schema = \'main_db\' and table_name = \''+source_data_type+'\'';
    results = await DBConn.MakeQuery(query);
    var temp2 = []
    temp2.push({id:i+1});
    for(j = 0; j < results.length; j ++){
      item = results[j];
      temp2.push({a:item[Object.keys(item)[0]]});
    }
    temp.push(temp2);
  }
  res.original_data_types =temp;
  return res;
}

// 1. parse_and_create_new_task: 
//    역할: 관리자가 정의한 태스크 정보를 DB의 TASK 테이블에 저장하고, 태스크 데이터 테이블을 생성함
//    파라미터:
//      task_info: 태스크 정보를 담고 있는 json 딕셔너리
//                 name: 태스크 이름
//                 description: 태스크 설명
//                 start_period: 태스크 시작일
//                 end_period: 태스크 종료일
//                 min_submit_period: 최소업로드 주기
//                 standard_of_pass: 평가점수 통과 기준
//
//      task_schema: 태스크 스키마 정보를 담고 있는 json 딕셔너리, 또는 테이블 정의 sql문
//                   name: 태스크 데이터 테이블 이름
//                   fields: 속성 정보를 담고 있는 json 딕셔너리
//                           name: 속성 이름
//                           type: 속성 타입. 
//                                 text, discrete, integer, big integer, float, date, time, datetime 중 하나
//      
//      use_sql: true 일시 테이블 정의 sql문 사용, false 일시 json 딕셔너리 사용
//
//    리턴: 실패/성공 여부 메시지
async function parse_and_create_new_task(task_info, field_info, task_schema, use_sql, data_type_name, mapping_info){
    task_name = task_info.name;
    task_table_name = task_info.name.split(' ').join('');
    data_type_table_name = data_type_name.split(' ').join('');
  
    query = 'select name from task where name = \''+task_name+'\'';
    results = await DBConn.MakeQuery(query);
    if(results == -1) return stats.ERROR_DB_CONNECTION_FAIL;
    if(results[0] != null) return stats.ERROR_TASK_NAME_DUPLICATE;
  
    query = 'select * from information_schema.tables where table_name = \''+task_table_name+'\'';
    results = await DBConn.MakeQuery(query);
    if(results == -1) return stats.ERROR_DB_CONNECTION_FAIL;
    if(results[0] != null) return stats.ERROR_TASK_NAME_DUPLICATEE;
  
    if(use_sql){
      results = DBConn.MakeQuery(task_schema);
      if(results == -1) return stats.ERROR_DB_CONNECTION_FAIL;
      task_table_name = task_schema.split(' ')[2].split('(')[0].split(' ').join('');
    } else {
      fields = field_info;
      query = 'create table '+task_table_name+'(';
      for(f = 0; f < fields.length; f ++){
        query += fields[f]['name'] + ' ';
        
        if(fields[f]['type'] == 'text') {
          query += 'text';
        }
  
        if(fields[f]['type'] == 'integer') {
          query += 'int';
        }
  
        if(fields[f]['type'] == 'big integer') {
          query += 'bigint';
        }
  
        if(fields[f]['type'] == 'float') {
          query += 'float';
        }
  
        if(fields[f]['type'] == 'date') {
          query += 'date';
        }
  
        if(fields[f]['type'] == 'time') {
          query += 'time';
        }
  
        if(fields[f]['type'] == 'datetime'){
          query += 'datetime';
        }
  
        if(f != fields.length - 1) query += ',';
      }
      query += ');'
  
      results = await DBConn.MakeQuery(query);
      if(results == -1) return stats.ERROR_DB_CONNECTION_FAIL;
    }
  
    description = task_info['description'];
    start_period = task_info['start_period'];
    end_period = task_info['end_period'];
    min_submit_period = task_info['min_submit_period'];
    standard_of_pass = task_info['standard_of_pass'];
  
    query = 'insert into task values(\''+task_name+'\', \''+description+'\', \''+start_period+'\', \''
              +end_period+'\','+min_submit_period+', '+standard_of_pass+', \''+task_table_name+'\')';
    results = DBConn.MakeQuery(query);
    if(results == -1) return stats.ERROR_DB_CONNECTION_FAIL;

    query = 'select * from source_data_type where table_name = \''+data_type_table_name+'\'';
    results = await DBConn.MakeQuery(query);
    if(results == -1) return stats.ERROR_DB_CONNECTION_FAIL;
    if(results[0] != null) return stats.ERROR_TASK_NAME_DUPLICATE;

    fields = mapping_info;
    save_schema = {};
    query = 'create table '+data_type_table_name+'(';
    query += 'file_id varchar(30) not null,';
      for(f = 0; f < fields.length; f ++){
        save_schema[fields[f]['name']] = fields[f]['schema'];
        query += fields[f]['name'] + ' ';
        
        if(fields[f]['type'] == 'text') {
          query += 'text';
        }
  
        if(fields[f]['type'] == 'integer') {
          query += 'int';
        }
  
        if(fields[f]['type'] == 'big integer') {
          query += 'bigint';
        }
  
        if(fields[f]['type'] == 'float') {
          query += 'float';
        }
  
        if(fields[f]['type'] == 'date') {
          query += 'date';
        }
  
        if(fields[f]['type'] == 'time') {
          query += 'time';
        }
  
        if(fields[f]['type'] == 'datetime'){
          query += 'datetime';
        }
  
        if(f != fields.length - 1) query += ',';
      }
      query += ');'
  
      results = await DBConn.MakeQuery(query);
      if(results == -1) return stats.ERROR_DB_CONNECTION_FAIL;

      query = 'insert into source_data_type values(\''+ task_name +'\',\''+data_type_table_name+'\',\''+JSON.stringify(save_schema)+'\')';
      results = await DBConn.MakeQuery(query);
      if(results == -1) return stats.ERROR_DB_CONNECTION_FAIL;
      return stats.SUCCESS;
  }

  async function add_source_data_type(taskname, data_type_name, field_info){
    fields = field_info;
    save_schema = {};
    data_type_table_name = data_type_name.split(' ').join('');
    query = 'create table '+data_type_table_name+'(';
    query += 'file_id varchar(50) not null,';
      for(f = 0; f < fields.length; f ++){
        save_schema[fields[f]['name']] = fields[f]['schema'];
        query += fields[f]['name'] + ' ';
        
        if(fields[f]['type'] == 'text') {
          query += 'text';
        }
  
        if(fields[f]['type'] == 'integer') {
          query += 'int';
        }
  
        if(fields[f]['type'] == 'big integer') {
          query += 'bigint';
        }
  
        if(fields[f]['type'] == 'float') {
          query += 'float';
        }
  
        if(fields[f]['type'] == 'date') {
          query += 'date';
        }
  
        if(fields[f]['type'] == 'time') {
          query += 'time';
        }
  
        if(fields[f]['type'] == 'datetime'){
          query += 'datetime';
        }
  
        if(f != fields.length - 1) query += ',';
      }
      query += ');'
  
      results = await DBConn.MakeQuery(query);
      if(results == -1) return stats.ERROR_DB_CONNECTION_FAIL;

      query = 'insert into source_data_type values(\''+ taskname +'\',\''+data_type_table_name+'\',\''+JSON.stringify(save_schema)+'\')';
      results = await DBConn.MakeQuery(query);
      if(results == -1) return stats.ERROR_DB_CONNECTION_FAIL;
      return stats.SUCCESS;
  }
  
// 2. user_apply_task:
//    역할: 제출자 태스크 신청 정보를 DB의 APPLY 테이블에 저장함
//    파라미터:
//      user_id: 신청자 id
//      task_name: 태스크 이름
//
//    리턴: 실패/성공 여부 메시지
async function user_apply_task(user_id, task_name){
    query = 'select * from apply where applicant_id = \''+user_id+'\' AND task_name = \''+task_name+'\'';
    results = await DBConn.MakeQuery(query);
    if(results == -1) return stats.ERROR_DB_CONNECTION_FAIL;
    if(results[0] != null) return stats.ERROR_ALREADY_APPLIED;
  
    query = 'insert into apply values(\''+user_id+'\', \''+task_name+'\')';
    results = await DBConn.MakeQuery(query);
    if(results == -1) return stats.ERROR_DB_CONNECTION_FAIL;
  
    return stats.SUCCESS;
}
  
// 3. user_participate_task:
//    역할: 제출자 태스크 참여 정보를 DB의 PARTICIPATE 테이블에 저장함
//    파라미터:
//      user_id: 참여자 id
//      task_name: 태스크 이름
//
//    리턴: 실패/성공 여부 메시지
async function user_participate_task(user_id, task_name){
    query = 'select * from participate where participant_id = \''+user_id+'\' AND task_name = \''+task_name+'\'';
    results = await DBConn.MakeQuery(query);
    if(results == -1) return stats.ERROR_DB_CONNECTION_FAIL;
    if(results[0] != null) return stats.ERROR_ALREADY_PARTICIPATING;
  
    query = 'insert into participate values(\''+user_id+'\', \''+task_name+'\')';
    results = await DBConn.MakeQuery(query);
    if(results == -1) return stats.ERROR_DB_CONNECTION_FAIL;
  
    return stats.SUCCESS;
}
 
// 4. user_sign_up:
//    역할: 유저 회원가입 정보를 DB의 USER 테이블에 저장함
//    파라미터: 유저 정보들
//    리턴: 실패/성공 여부 메시지
async function user_sign_up(id, password, name, phone_number, address, birthday, type){
    query = 'select * from user where id = \''+id+'\'';
    results = await DBConn.MakeQuery(query);
    if(results == -1) return stats.ERROR_DB_CONNECTION_FAIL;
    if(results[0] != null) return stats.ERROR_ID_DUPLICATE;
  
    query = 'insert into user values(\''+id+'\', \''+name+'\', \''+password+'\', \''+phone_number+'\', \''+address+'\',\''+birthday+'\', \''+type+'\',0)';
    results = await DBConn.MakeQuery(query);
    if(results == -1) return stats.ERROR_DB_CONNECTION_FAIL;
  
    return stats.SUCCESS;
}
  
// 4-1. check_id:
//      역할: id 중복 체크
//      파라미터: user id
//      리턴: 실패/성공 여부 메시지
async function check_id(id){
  query = 'select * from user where id = \''+id+'\'';
  results = await DBConn.MakeQuery(query);
  if(results == -1) return stats.ERROR_DB_CONNECTION_FAIL;
  if(results[0] != null) return stats.ERROR_ID_DUPLICATE;
  
  return stats.SUCCESS;
}

async function user_edit(id, password, phone_number,address){
  query = 'update user set password=\''+password+'\',phone_number=\''+phone_number+'\',address=\''+address+'\' where id=\''+id+'\'';
  results = await DBConn.MakeQuery(query);
  if(results == -1) return stats.ERROR_DB_CONNECTION_FAIL;
  return stats.SUCCESS;
}

async function withdraw(id){
  query = 'delete from user where id = \''+id+'\'';
  results = await DBConn.MakeQuery(query);
  if(results == -1) return stats.ERROR_DB_CONNECTION_FAIL;
  return stats.SUCCESS;
}

// 5. user_authorize:
//    역할: 유저 로그인 정보를 DB의 USER 테이블과 비교하고 실패/성공 여부를 반환함
//    파라미터: 유저 아이디, 패스워드
//    리턴: 로그인 실패/성공 여부 메시지
async function user_authorize(id, password){
    query = 'select password from user where id=\''+id+'\'';
    results = await DBConn.MakeQuery(query);
    if(results == -1) return stats.ERROR_DB_CONNECTION_FAIL;
    if(results[0] == null) return stats.ERROR_NO_ID;
    if(results[0]['password'] != password) return stats.ERROR_WRONG_PASSWORD;
    return stats.SUCCESS;
}

async function get_users(){
  query = 'select id, password, name, type as position from user';
  results = await DBConn.MakeQuery(query);
  return results;
}

async function get_user_tasks_and_score(id){
  res = {};
  query = 'select name, description, start_period, end_period, min_submit_period as period from task, participate where participant_id = \''+id+'\' and name=task_name';
  results = await DBConn.MakeQuery(query);
  res.items = results;
  query = 'select score from user where id=\''+id+'\'';
  results = await DBConn.MakeQuery(query);
  res.score = results;
  return res;
}

async function get_task_source_data_types(name){
  res = {};
  query = 'select table_name as typeName from source_data_type, task where name=task_name and name=\''+name+'\'';
  results = await DBConn.MakeQuery(query);
  res.type = results;
  return res;
}

async function get_source_data_type_info(id, name){
  res = {};
  query = 'select f.id as filename, f.number as subNum, p.p_np as isPass from file f, parsing_data_sequence_file p, submit s where f.table_name = \''+name+'\' and f.id = p.file_id and f.id = s.file_id and s.submitter_id = \''+id+'\' order by subNum';
  results = await DBConn.MakeQuery(query);
  res.submitFiles = results;
  query = 'select count(*) from file, submit where table_name = \''+name+'\' and file_id = id and submitter_id = \''+id+'\'';
  results = await DBConn.MakeQuery(query);
  res.subFileNum = results;
  query = 'select count(*) from '+name+' where file_id in (select file_id from submit where submitter_id = \''+id+'\')';
  results = await DBConn.MakeQuery(query);
  res.tupleNum = results;
  return res;
}

async function get_appliable_tasks(id){
  res = {};
  query = 'select name, description, start_period, end_period, min_submit_period as period from task where name not in(select task_name from apply where applicant_id = \''+id+'\' union select task_name from participate where participant_id = \''+id+'\')';
  results = await DBConn.MakeQuery(query);
  res.rTask = results;
  query = 'select name, description, start_period, end_period, min_submit_period as period from task, apply where applicant_id=\''+id+'\' and name=task_name';
  results = await DBConn.MakeQuery(query);
  res.wTask = results;
  return res;
}

async function user_apply_task(id, taskname){
  query = 'insert into apply values(\''+id+'\', \''+taskname+'\')';
  results = await DBConn.MakeQuery(query);
  return stats.SUCCESS;
}

async function get_columns_and_eval(tablename){
  res = {};
  query = 'select column_name, data_type from information_schema.columns where table_schema = \'main_db\' and table_name = \''+tablename+'\' and column_name != \'FILE_ID\'';
  results = await DBConn.MakeQuery(query);
  res.columns = results;
  //query = 'select evaluator_id from (select evaluator_id, count(*) cnt from parsing_data_sequence_file group by evaluator_id) t order by cnt';
  query = 'select id as evaluator_id from user where type = \'evaluator\' order by rand() limit 1';
  results = await DBConn.MakeQuery(query);
  if(results[0] == null){
    query = 'select id as evaluator_id from user where type = \'evaluator\'';
    results = await DBConn.MakeQuery(query);
  }
  res.eval = results;
  return res;
}

async function insert_tuple(sql){
  results = await DBConn.MakeQuery(sql);
}

async function submit_file(id, filename){
  query = 'insert into submit values(\''+id+'\', \''+filename+'\')';
  await DBConn.MakeQuery(query);
}

async function get_duplicates_and_sums(fileid, tablename){
  res = {};
  query = 'select count(*) from '+tablename+' where file_id=\''+fileid+'\'';
  results = await DBConn.MakeQuery(query);
  res.all_tuples = results;
  query = 'select count(*) from (select distinct * from '+tablename+' where file_id=\''+fileid+'\') t';
  results = await DBConn.MakeQuery(query);
  res.duplicates = results;
  return res;
}

async function parse_file(fileid, type, duplicates, submit_time, all_tuples, evaluator_id){
  query = 'insert into parsing_data_sequence_file(file_id, type, duplicated_tuple_number, submit_time, all_tuple_number, evaluator_id) values(\''+fileid+'\',\''+type+'\','+duplicates+',\''+submit_time+'\','+all_tuples+',\''+evaluator_id+'\')';
  await DBConn.MakeQuery(query);
}

async function get_not_evaluated(id){
  res = {};
  query = 'select f.id, s.task_name as task, s.table_name as type, f.number, f.start_period, f.end_period from parsing_data_sequence_file p, source_data_type s, file f where p.evaluator_id = \''+id+'\' and p.file_id = f.id and f.table_name = s.table_name and p.p_np = \'empty\'';
  results = await DBConn.MakeQuery(query);
  res.todo_list = results;
  return res;
}

async function get_evaluated(id){
  res = {};
  query = 'select f.id, s.task_name as task, s.table_name as type, f.number, p.p_np from parsing_data_sequence_file p, source_data_type s, file f where p.evaluator_id = \''+id+'\' and p.file_id = f.id and f.table_name = s.table_name and p.p_np != \'empty\'';
  results = await DBConn.MakeQuery(query);
  res.evaluated_list = results;
  return res;
}

async function add_file(filename, subNum, start_period, end_period, filetype, tablename){
  query = 'insert into file values(\''+filename+'\','+subNum+',\''+start_period+'\',\''+end_period+'\',\''+filetype+'\',\''+tablename+'\')';
  await DBConn.MakeQuery(query);
}

async function get_parsing_data_info(fileID){
  query = 'select p.file_id as id, p.type, s.table_name as task, f.number, f.start_period, f.end_period, p.all_tuple_number, p.duplicated_tuple_number, f.table_name from parsing_data_sequence_file p, source_data_type s, file f where p.file_id = \''+fileID+'\' and p.file_id = f.id and s.table_name = f.table_name';
  results = await DBConn.MakeQuery(query);
  return results;
}

async function get_columns(tablename){
  res = {};
  query = 'select column_name, data_type from information_schema.columns where table_schema = \'main_db\' and table_name = \''+tablename+'\' and column_name != \'FILE_ID\'';
  results = await DBConn.MakeQuery(query);
  res.columns = results;
  return res;
}

async function get_null_values(filename, tablename, attr){
  res = {};
  for(i = 0; i < attr.length; i ++){
    query = 'select count(*) from '+tablename+' where file_id=\''+filename+'\' and '+attr[i]+' is null';
    results = await DBConn.MakeQuery(query);
    res[attr[i]] = results[0]['count(*)'];
  }
  return res;
}

async function evaluate(fileID, score, p_np){
  if(p_np == 'non-pass') p_np = 'nonpass';
  query = 'update parsing_data_sequence_file set score='+score+',p_np=\''+p_np+'\' where file_id=\''+fileID+'\'';
  await DBConn.MakeQuery(query);
  return stats.SUCCESS;
}

// ============== ADMIN ============ //
async function get_task_status(){
  query = 'select name, description as des, min_submit_period as upload, data_table_name as table_name from task';
  results = await DBConn.MakeQuery(query);
  return results;
}

async function get_task_info(name){
  res = {};
  query = 'select name, description as des, data_table_name from task where name = \''+name+'\'';
  results = await DBConn.MakeQuery(query);
  res.info1 = results;
  query = 'select count(*) from file f, source_data_type s where f.table_name = s.table_name and s.task_name = \''+name+'\'';
  results = await DBConn.MakeQuery(query);
  res.info2 = results;
  query = 'select p.participant_id as id, u.name from participate p, user u where u.id = p.participant_id and p.task_name = \''+name+'\'';
  results = await DBConn.MakeQuery(query);
  res.info3 = results;
  query = 'select table_name from task, source_data_type where task_name = name and name =\''+name+'\'';
  results = await DBConn.MakeQuery(query);
  res.info4 = results;

  return res;
}

async function get_participants(name){
  res = {};
  query = 'select a.applicant_id as id, u.name from apply a, user u where u.id = a.applicant_id and a.task_name = \''+name+'\'';
  results = await DBConn.MakeQuery(query);
  res.register_list = results;
  query = 'select standard_of_pass from task where name = \''+name+'\'';
  results = await DBConn.MakeQuery(query);
  res.task_standard = results;
  return res;
}

async function confirm_apply(name, id){
  query = 'insert into participate values(\''+id+'\',\''+name+'\')';
  results = await DBConn.MakeQuery(query);
  query = 'delete from apply where applicant_id=\''+id+'\' and task_name=\''+name+'\'';
  results = await DBConn.MakeQuery(query);
  return stats.SUCCESS;
}

async function reset_standard(name, pass_standard){
  query = 'update task set standard_of_pass='+pass_standard+' where name = \''+name+'\'';
  results = await DBConn.MakeQuery(query);
  return stats.SUCCESS;
}

async function get_columns2(tablename){
  query = 'select column_name as value, column_name as text from information_schema.columns where table_schema = \'main_db\' and table_name = \''+tablename+'\'';
  results = await DBConn.MakeQuery(query);
  return results;
}

async function get_members(){
  query = 'select id, name, type as role from user';
  results = await DBConn.MakeQuery(query);
  return results;
}

async function check_member_type(user_id){
  query = 'select type from user where id = \''+user_id+'\'';
  results = await DBConn.MakeQuery(query);
  return results;
}

async function get_mapping_schema(filename){
  query = 'select schema_info, f.table_name, s.task_name, t.data_table_name as task_table_name from source_data_type s, file f, task t where id = \''+filename+'\' and f.table_name = s.table_name and s.task_name = t.name';
  results = await DBConn.MakeQuery(query);
  return results;
}

async function get_file(fileID, table_name){
  query = 'select * from '+table_name+' where file_id=\''+fileID+'\'';
  results = await DBConn.MakeQuery(query);
  return results;
}

async function get_file2(table_name){
  query = 'select * from '+table_name;
  results = await DBConn.MakeQuery(query);
  return results;
}

async function put_into_task_table(task_table_name, tuples, columns, schema_info){
  for(i = 0; i < tuples.length; i ++){
    var task_attrs = '(';
    var sd_values = '(';
    for(j = 0; j < columns.length; j ++){
      sd_value = tuples[i][columns[j]];
      task_attr = schema_info[columns[j]];
      sd_values += sd_value;
      task_attrs += task_attr;
      if(j != columns.length - 1){
        task_attrs += ',';
        sd_values += ',';
      }
    }
    task_attrs += ')';
    sd_values += ')';
    query = 'insert into '+task_table_name +task_attrs+' values'+sd_values;
    results = await DBConn.MakeQuery(query);
    if(results == -1) return stats.ERROR_DB_CONNECTION_FAIL;
  }
  return stats.SUCCESS;
}

async function make_file(task_name){
  var filepath = (__dirname + '\\' + task_name + '.csv').replace(/\\/gi, '/');
  console.log(filepath);
  table_name = task_name.split(' ').join('');
  query = 'select * from '+table_name+' into outfile \''+filepath+'\' fields enclosed by \"\" escaped by \"\" terminated by \',\' lines terminated by \'\\r\\n\'';
  await DBConn.MakeQuery(query);
  return stats.SUCCESS;
}

async function get_table_name(task_name){
  query = 'select data_table_name as table_name from task where name = \''+task_name+'\'';
  results = await DBConn.MakeQuery(query);
  return results;
}

async function get_member_info(id){
  res = {};
  query = 'select id, name, type as role from user where id = \''+id+'\'';
  results = await DBConn.MakeQuery(query);
  res.user_info = results;
  return res;
}

async function get_submitter_info(id){
  res = {};
  query = 'select task_name as name from participate where participant_id = \''+id+'\'';
  results = await DBConn.MakeQuery(query);
  task = results;
  taskList = [];
  for(i = 0; i < task.length; i ++){
    task_name = task[i].name;
    taskList.push(task_name);
    query = 'select count(*) from submit s, file f, source_data_type sd where s.submitter_id = \''+id+'\' and s.file_id = f.id and f.table_name = sd.table_name and sd.task_name = \''+task_name+'\'';
    results = await DBConn.MakeQuery(query);
    num_task_submitter_files = results;
    task[i].fileNumber = num_task_submitter_files[0]['count(*)'];

    query = 'select s.file_id, p.all_tuple_number from submit s, parsing_data_sequence_file p, file f, source_data_type sd where s.submitter_id = \''+id+'\' and s.file_id = p.file_id and p.p_np = \'PASS\' and s.file_id = f.id and f.table_name = sd.table_name and sd.task_name = \''+task_name+'\'';
    results = await DBConn.MakeQuery(query);
    submit_files = results;
    tupleNumber = 0;
    for(j = 0; j < submit_files.length; j ++){
      temp = submit_files[j].all_tuple_number;
      tupleNumber += temp;
    }
    task[i].tupleNumber = tupleNumber;

    query = 'select table_name from source_data_type where task_name = \''+task_name+'\'';
    results = await DBConn.MakeQuery(query);
    source_data_types = results;
    nullProperty = 0;
    for(j = 0; j < source_data_types.length; j ++){
      source_data_type = source_data_types[j].table_name;
      query = 'select column_name from information_schema.columns where table_schema = \'main_db\' and table_name = \''+source_data_type+'\' and column_name != \'FILE_ID\'';
      results = await DBConn.MakeQuery(query);
      for(k = 0; k < results.length; k ++){
        column = results[k].column_name;
        query = 'select count(*) from '+source_data_type+' sd, submit s where s.submitter_id = \''+id+'\' and s.file_id = sd.file_id and sd.'+column+' is null';
        results = await DBConn.MakeQuery(query);
        nullProperty += results[0]['count(*)'];
      }
    }
    task[i].nullProperty = nullProperty;
  }
  res.taskList = taskList;
  res.task = task;
  return res;
}

async function get_evaluator_info(id){
  query = 'select file_id as id, score, p_np as pnp from parsing_data_sequence_file where evaluator_id = \''+id+'\' and p_np != \'EMPTY\'';
  results = await DBConn.MakeQuery(query);
  return results;
}

async function get_search_users(){
  query = 'select id, name, type as role, birthday from user';
  results = await DBConn.MakeQuery(query);
  return results;
}

async function update_user_score(fileID, score){
  query = 'select id from user, submit where submitter_id = id and file_id = \''+fileID+'\'';
  results = await DBConn.MakeQuery(query);
  user_id = results[0].id;

  query = 'select sum(score) from parsing_data_sequence_file p, submit s where p.file_id = s.file_id and s.submitter_id = \''+user_id+'\' and p.p_np != \'EMPTY\'';
  results = await DBConn.MakeQuery(query);
  user_score = results[0]['sum(score)'];

  query = 'select count(*) from parsing_data_sequence_file p, submit s where p.file_id = s.file_id and s.submitter_id = \''+user_id+'\' and p.p_np != \'EMPTY\'';
  results = await DBConn.MakeQuery(query);
  user_file_num = results[0]['count(*)'];

  user_score = (user_score + score)/(user_file_num + 1);
  query = 'update user set score='+user_score+' where id = \''+user_id+'\'';
  results = await DBConn.MakeQuery(query);
}

module.exports = {
    parse_and_create_new_task: parse_and_create_new_task,
    user_apply_task: user_apply_task,
    user_participate_task: user_participate_task,
    user_sign_up: user_sign_up,
    user_authorize: user_authorize,
    get_users: get_users,
    get_user_tasks_and_score: get_user_tasks_and_score,
    get_task_source_data_types: get_task_source_data_types,
    get_source_data_type_info: get_source_data_type_info,
    get_appliable_tasks: get_appliable_tasks,
    get_columns_and_eval: get_columns_and_eval,
    insert_tuple: insert_tuple,
    submit_file: submit_file,
    parse_file: parse_file,
    add_file: add_file,
    get_duplicates_and_sums: get_duplicates_and_sums,
    get_not_evaluated: get_not_evaluated,
    get_evaluated: get_evaluated,
    get_parsing_data_info: get_parsing_data_info,
    get_columns: get_columns,
    get_null_values: get_null_values,
    evaluate:  evaluate,
    check_id: check_id,
    user_edit:user_edit,
    withdraw: withdraw,
    get_task_info: get_task_info,
    get_task_status: get_task_status,
    get_participants: get_participants,
    confirm_apply: confirm_apply,
    reset_standard: reset_standard,
    get_columns2: get_columns2,
    compute_db1: compute_db1,
    get_members: get_members,
    check_member_type: check_member_type,
    add_source_data_type: add_source_data_type,
    get_mapping_schema: get_mapping_schema,
    get_file: get_file,
    put_into_task_table: put_into_task_table,
    make_file: make_file,
    get_file2: get_file2,
    get_table_name: get_table_name,
    get_member_info: get_member_info,
    get_submitter_info: get_submitter_info,
    get_evaluator_info: get_evaluator_info,
    get_search_users: get_search_users,
    update_user_score: update_user_score,
}