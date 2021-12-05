<template>
  <div>
    <div class="hello">
      <h1>{{ msg }}</h1>
      <img src="../../assets/EDs_DBD.png" alt="logo">
    </div>
    <form v-on:submit.prevent="login" class='form'>
      <div>
       <label for="id">아이디 :</label>
       <input name="id" type="text" v-model="id" />
      </div>
      <div>
       <label for="password">비밀번호 :</label>
       <input name="password" type="password" v-model="password"  />
      </div>
      <button type="login" v-on:click="login">로그인</button>
      <button type="newregister" v-on:click="newone">회원가입</button>
    </form>
    <ul>
      <p>© ED's DBD</p>
    </ul>
  </div>
</template>
<script>
export default {
    name: 'Hello',
    data() {
        return {
            msg: 'Welcome!',
            id: "",
            password:"",
        }
    },
    methods:{
      login:function(){
        const id = this.id;
        const password = this.password;
        this.$http.post("api/login",{id,password, },
        {"Content-Type":"application-json"})
          .then((res)=>{
            if(res.data.user){
              this.$store.commit("setUser",res.data.user);
              this.$router.push({name: "IndexPage"});
            }else if (res.data.message){
              alert(res.data.message);
            }
          })
          .catch((err)=>{
              console.error(err);
          });
      },
      newone:function(){
        this.$router.push({name:"SignUpPage"});
      }
    }
}
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
.hello{float: left;padding-left: 100px;}
.form{width:50%;float:right;border-radius: 5px;background-color: #f2f2f2;margin: 20px;padding:20px;}
label{width: 80px; text-align: right;}
button{width: 150px;background-color: #247e70;color: white;padding: 14px 20px;margin: 8px 0;border: none;border-radius: 4px;cursor: pointer;}
button:hover{background-color: #257e70ad;}
input, select {width: 250px;padding: 12px 20px;margin: 8px 0;border: 1px solid #ccc;border-radius: 4px;box-sizing: border-box;}
img{width:250px;}
div {margin : 20px;}
h1, h2 {font-weight : bold;}
ul {position : relative;top : 70px;list-style-type : none;padding : 0;}
a {text-decoration : none;}
p {position : relative;top : 300px;margin-bottom : 40px;font-size : small;}
</style>