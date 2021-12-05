
<template>
  <form v-on:submit.prevent="onSubmit">
    <div v-if="user">
      <h1> 접속한 유저 </h1>
      <p> 아이디 : {{user.id}} </p>
      <p> 비밀번호 : {{user.password}} </p>
      <p> 이름 : {{user.name}} </p>
      <p> 직책 : {{user.position}} </p>
    </div>
    <button>로그아웃</button>
    <ul>
      <p>© ED's DBD</p>
    </ul>
  </form>
  
</template>

<script>
export default {
    created(){
        this.$http.get('/api/login')
        .then((res) => {
            const user = res.data.user;
            if(user){
              this.$store.commit("setUser",user);
              if(user.position =="ADMINISTRATOR"){
                this.$router.push("/admin");
              }
              else if (user.position === "EVALUATOR") {
                this.$router.push("/evaluator/" + user.id)
              }
              else if (user.position == "SUBMITTER") {
                this.$router.push("/submitter/" + user.id);
              }
            }else{
              this.$router.push({name:"LoginPage"});
            }
        })
        .catch((err) => {
            console.error(err);
        });
    },
    methods:{
      onSubmit(){
        this.$http.get("api/logout")
        this.$store.commit("initdata");
        this.$router.push({name:"LoginPage"});
      }
    },
    computed:{
     user(){return this.$store.getters.user;}  
    }
}
</script>

<style scoped>

</style>
