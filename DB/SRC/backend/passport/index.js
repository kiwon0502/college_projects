const LocalStrategy = require('passport-local').Strategy;
const Functions = require('../scripts/Functions');
var users;
Functions.get_users()
.then((res)=>{ users = res; });

exports.config=(passport)=>{

    passport.serializeUser((user,done)=>{
        done(null,user.id);
    });

    passport.deserializeUser((id,done)=>{
        const result = users.filter((user)=> user.id === id);
        if(result.length>0){
            done(null,result[0]);
        }
    });

    passport.use(new LocalStrategy({
        usernameField: 'id',
        passwordField: 'password',
        session: true,
        passReqToCallback:false,
    },(id,password,done)=>{
        Functions.get_users()
        .then((res)=>{ 
            users = res;
            const result = users.filter((user)=>user.id===id);
            if(result.length>0){
                const user = result[0];
                if(password === user.password){
                    done(null,user,);
                }else{
                    done(null,false,{message:"비밀번호 틀림"});
                }
            }else{
                done(null,false,{message:"가입되지 않은 회원"});
            } 
        });
    }));
}