const express = require('express');
const router = express.Router();
let {PythonShell} = require('python-shell');
const Functions = require('../scripts/Functions')

router.get('/:taskName', function(req, res, next){
    taskName = req.params.taskName;
    Functions.get_table_name(taskName)
    .then((results)=>{
        tableName = results[0].table_name;
        var columns = [];
        var types = [];
        Functions.get_columns(tableName)
        .then((results)=>{
            for(i = 0; i < results.columns.length; i ++){
                columns.push(results.columns[i].column_name);
                types.push(results.columns[i].data_type);
            }
            Functions.get_file2(tableName)
            .then((results)=>{
                var args = [];
                var tuples = results;
                args.push(tuples.length);
                args.push(columns.length);
                for(i - 0; i < columns.length; i ++){
                    args.push(columns[i]);
                }
                for(i = 0; i < tuples.length; i ++){
                    for(j = 0; j < columns.length; j ++){
                        args.push(tuples[i][columns[j]]);
                    }
                }

                var options = {
                    mode: 'text',
                    pythonPath: '',
                    pythonOptions: ['-u'],
                    scriptPath: '',
                    args: [taskName, args, columns, types]
                };
        
                PythonShell.run('./scripts/save_csv.py', options, function(err, results){
                    if(err){
                        res.json({stat:1, filename: taskName});
                    } else {
                        res.json({stat:0, filename: taskName});
                    }
                });
            });
        });
    })
});

module.exports = router;