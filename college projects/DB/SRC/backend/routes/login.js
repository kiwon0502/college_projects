const express = require('express');
const passport = require('passport');
const router = express.Router();

router.get('/', function(req, res, next){

    if(req.isAuthenticated()&& req.user){
        return res.json({user: req.user});
    }
    return res.json({user: null});
});

router.post('/',function(req,res,next){

    if (req.isAuthenticated()){
        return res.redirect('/');
    }
    passport.authenticate('local',(authError,user,info)=>{
        if(authError){
            console.error(authError);
            return next(authError);
        }
        if(!user){
            return res.json(info);
        }
        return req.login(user,(loginError)=>{
            if(loginError){
                console.error(loginError);
                return next(loginError);
            }
            return res.json({user});
        });
    })(req,res,next);
});

module.exports = router;