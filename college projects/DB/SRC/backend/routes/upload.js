const express = require('express');
const router = express.Router();
const bodyParser = require('body-parser');
const multer = require('multer');
const Functions = require('../scripts/Functions');
let {PythonShell} = require('python-shell');
const storage = multer.diskStorage({
    destination: (req, file, cb) => {
      cb(null, './upload/');      // 업로드 위치
    },
    filename: (req, file, cb) => {
      var date = new Date();
      cb(null, `${req.user.id}-${date.getMonth()+1}-${date.getDay()}-${date.getHours()}-${date.getMinutes()}-${date.getSeconds()}-${date.getMilliseconds()}`);
    }
})
const upload = multer({ storage });
router.use(bodyParser.json());
router.use(bodyParser.urlencoded({ extended: true }));
router.use(express.json());
router.use(express.static('public'));
router.get('/', (req, res) => {
    res.sendFile('public/index.html');
});
router.post('/', upload.single('file'), function(req, res) {
  filename = req.file.filename;
  filetype = req.file.originalname.split('.')[1];
  subNum = req.body.subNum;
  start_period = req.body.start_period;
  end_period = req.body.end_period;
  taskname = req.body.taskName;
  tablename = req.body.dataType;

  var attrs = [];
  var types = [];
  var dateReg = /^\d{4}-\d{2}-\d{2}$/;
  if(!start_period.match(dateReg) || !end_period.match(dateReg)){
    res.json({stat:-1});
    return;
  }
  
  Functions.get_columns_and_eval(tablename)
  .then((results)=>{
    var columns = results.columns;
    var eval = results.eval[0].evaluator_id;
    
    for(var i = 0; i < columns.length; i ++){
      attrs.push(columns[i].column_name);
      types.push(columns[i].data_type);
    }

    var options = {
      mode: 'text',
      pythonPath: '',
      pythonOptions: ['-u'],
      scriptPath: '',
      args: [filename, attrs, types]
    };
    var valid = 0;
    
    PythonShell.run('./scripts/parse_csv.py', options, function(err, results){
      if(err) throw err;
      if(results[0] == '1'){
        valid = 1;
      }
      
      else if(results[1] == '1'){
        valid = 2;
      }

      if(valid == 0){
      
      type_sql = 'insert into '+tablename+'(file_id,';
      for(var i = 0; i < types.length; i ++){
        type_sql += attrs[i];
        if(i != types.length - 1) type_sql += ',';
      }
      type_sql += ') ';

      num_attrs = attrs.length;
      count = 0;
      sql = 'values(\''+filename+'\',';
      for(var i = 2; i < results.length; i ++){
        if(types[count].substr(0, 3) != 'int' && types[count].substr(0, 6) != 'bigint' && types[count].substr(0, 5) != 'float' && results[i] != 'nan'){
          sql += ('\''+ results[i] + '\'');
        }
        else {
          if(results[i] == 'nan') sql += 'NULL';
          else sql += results[i];
        }
        count ++;
        if(count == num_attrs){
          count = 0;
          sql += ')';
          Functions.insert_tuple(type_sql + sql);
          sql = 'values(\''+filename+'\',';
        } else {
          sql += ',';
        }
      }
      var date = new Date();
      var currentdate = date.getFullYear().toString()+'-'+(date.getMonth()+1).toString() +'-'+date.getDate().toString();
      Functions.get_duplicates_and_sums(filename, tablename)
      .then((results)=>{
        var all_tuples = results.all_tuples[0]['count(*)'];
        var duplicates = results.duplicates[0]['count(*)'];
        duplicates = all_tuples - duplicates;
        Functions.parse_file(filename, filetype, duplicates, currentdate, all_tuples, eval);
      });
      Functions.add_file(filename, subNum, start_period, end_period, filetype, tablename);
      Functions.submit_file(req.user.id, filename);
      console.log(valid);
      }
      res.json({stat:valid});
    });
  });
});

module.exports = router;