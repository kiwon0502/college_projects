<template>
  <div class="menu">
    <div :class="alloc_list_style" @click="on_click_alloc">
      배당 파일 목록
    </div>
    <div :class="finished_list_style" @click="on_click_eval">
      평가 완료 파일 목록
    </div>
  </div>
</template>

<script>
export default {
  props: {
    current: {
      type: String,
      required: true
    }
  },
  computed: {
    alloc_list_style() {
      return {
        list: true,
        current: this.current === "todo"
      }
    },
    finished_list_style() {
      return {
        list: true,
        current: this.current === "evaluated"
      }
    }
  },
  methods: {
    on_click_alloc() {
      if (this.current === "todo") return
      this.$router.push('/evaluator/' + this.$route.params.userID + '/todo')
    },
    on_click_eval() {
      if (this.current === "evaluated") return
      this.$router.push('/evaluator/' + this.$route.params.userID + '/evaluated')
    }
  }
}
</script>

<style scoped>
div.menu {
  width: 800px;
  background-color: #cccccc;
  padding: 5px 20px;
  margin: 35px;
}

div.list {
  display: inline-block;
  width:270px;
  height:50px;
  margin: 10px;
  padding: 14px 0px;
  background-color:  #f2f2f2;
}

div.list:hover:not(.current) {
  background-color: #257e70ad;
  font-weight: bold;
  cursor: pointer;
}

div.list:active:not(.current) {
  background-color: #f2f2f2;
}

div.current {
  background-color: #247e70;
  color: white;
  font-weight: bold;
}
</style>