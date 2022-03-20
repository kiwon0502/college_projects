var createError = require('http-errors');
var express = require('express');
var path = require('path');
var cookieParser = require('cookie-parser');
var logger = require('morgan');
var session =require('express-session');
var passport = require('passport');
var bodyParser = require('body-parser')
require('./passport').config(passport);
require('dotenv').config();

var indexRouter = require('./routes/index');
var memberRouter = require('./routes/member');
var loginRouter = require('./routes/login');
var signUpRouter = require('./routes/sign_up');
var profileRouter = require('./routes/profile');
var evaluatorRouter = require('./routes/evaluator');
var taskRouter = require('./routes/task');
var tableRouter = require('./routes/getTable');
var rTableRouter = require('./routes/getRTable');
var registerRouter = require('./routes/registerTask');
var checkIdRouter = require('./routes/check_id');
var withdrawRouter = require('./routes/withdraw');
var logoutRouter = require('./routes/logout');
var loadRouter = require('./routes/upload');

var downloadRouter = require('./routes/download');
var createFileRouter = require('./routes/createFile');

var app = express();

// view engine setup
app.set('views', path.join(__dirname, 'views'));
app.set('view engine', 'pug');

app.use(logger('dev'));
app.use(express.json());
app.use(express.urlencoded({ extended: false }));
app.use(cookieParser(process.env.COOKIE_SECRET));
app.use(session({
  resave: false,
  saveUninitialized: false,
  secret: process.env.COOKIE_SECRET,
  cookie: {
    httpOnly: true,
    secure: false,
  }
}));
app.use(passport.initialize());
app.use(passport.session());

app.use(bodyParser.urlencoded({extended:true}));
app.use(bodyParser.json());

app.use(express.static(path.join(__dirname, 'public')));

app.use('/', indexRouter);
app.use('/api/member', memberRouter);
app.use('/api/sign_up', signUpRouter);
app.use('/api/profile', profileRouter);
app.use('/api/evaluator', evaluatorRouter);
app.use('/api/task', taskRouter);

app.use('/api/login',loginRouter);
app.use('/api/logout',logoutRouter);

app.use('/api/getTable', tableRouter);
app.use('/api/getRTable', rTableRouter);
app.use('/api/registerTask', registerRouter);
app.use('/api/check_id', checkIdRouter);
app.use('/api/withdraw', withdrawRouter);
app.use('/api/upload', loadRouter);

app.use('/api/download', downloadRouter);
app.use('/api/createFile', createFileRouter);

// catch 404 and forward to error handler
app.use(function(req, res, next) {
  next(createError(404));
});

// error handler
app.use(function(err, req, res, next) {
  // set locals, only providing error in development
  res.locals.message = err.message;
  res.locals.error = req.app.get('env') === 'development' ? err : {};

  // render the error page
  res.status(err.status || 500);
  res.render('error');
});

module.exports = app;