<template>
  <div class="hello">
    <h1>{{ msg }}</h1>
    <h2>[직책에 맞는 아이디로 로그인 부탁드립니다]</h2>
      <br>
    <form v-on:submit.prevent="submitForm">
      <div>
       <label for="userid">id:</label>
       <input id="userid" type="text" v-model="userid" />
       <label for="password">PW:</label>
       <input id="password" type="password" v-model="password"  />
      </div>
    </form>
    <button type="login">로그인</button>
    <button type="newregister" v-on:click="newone">회원가입</button>
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
            msg: 'Welcome! ED\'s DBD에 오신걸 환영합니다',
        };
    },
    methods:{
      newone:function(){
        this.$router.push({name:"SignUpPage"});
      }
    },
};
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
div {
  margin : 150px;
}
h1, h2 {
  font-weight : bold;
}
ul {
  position : relative;
  top : 70px;
  list-style-type : none;
  padding : 0;
}
ul > li {
  font-size : large;
  display : inline-block;
  margin : 0 80px;
  font-weight : bold;
  color : #42b983;
}
a {
  text-decoration : none;
}
p {
  position : relative;
  top : 300px;
  margin-bottom : 40px;
  font-size : small;
}
</style>