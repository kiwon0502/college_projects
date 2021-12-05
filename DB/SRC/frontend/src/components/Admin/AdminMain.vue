<template>
  <div>
      <h1>Welcome! {{ user.name }}님</h1>
      <h2>{{ msg }}</h2>
        <br>
      <ul>
        <li>
          <button type="submit" v-on:click = to_task()>TASK</button>
        </li>
        <li>
          <button type="submit" v-on:click = to_memb()>회원관리</button>
        </li>
      </ul>
      <ul>
        <p>© ED's DBD</p>
      </ul>
  </div>
</template>

<script>
export default {
    name: 'AdminMain',
    data () {
        return {
            msg: '[ADMINISTRATOR Page]'
        }
    },
    methods:{
        to_task() {
            this.$router.push({name:"ShowTaskInfo"});
        },
        to_memb() {
            this.$router.push({name:"ShowMember"});
        }
    },
    computed: {
        user() {return this.$store.getters.user;}
    }
}
</script>

<style scoped>
div {
  margin : 200px;
}
h1, h2 {
  font-weight : bold;
}
ul {
  position : relative;
  top : 80px;
  list-style-type : none;
  padding : 0;
}
ul > li {
  font-size : large;
  display : inline-block;
  margin : 0 80px;
  font-weight : bold;
}
a {
  text-decoration : none;
}
a > div {
  margin : 0px;
  height : 100px;
  width : 100px;
  border-color : #42b983;
  text-align: center;
}
p {
  position : relative;
  top : 300px;
  padding-bottom : 40px;
  font-size : small;
}
button[type=submit]{background-color: #247e70;color: white;padding: 14px 20px;margin: 8px 0;border: none;border-radius: 4px;cursor: pointer;}
button[type=submit]:hover{background-color: #257e70ad;}
</style>
