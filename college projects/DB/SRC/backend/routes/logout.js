const express = require('express');
const passport = require('passport');
const router = express.Router();

router.get('/', function(req, res, next){
    req.logOut();
    req.session.save(function(){
        res.redirect('/');
    })
});
module.exports = router;