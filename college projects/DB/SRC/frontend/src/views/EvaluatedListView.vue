<template>
  <div class="wrapper">
    <Menu current="evaluated"/>
    <EvaluatedFileList :files="evaluatedFiles"/>
  </div>
</template>

<script>
import Menu from '@/components/EvalMenu.vue';
import EvaluatedFileList from '@/components/EvaluatedFileList.vue';
export default {
  components: {
    Menu,
    EvaluatedFileList
  },
  data() {
    return {
      evaluatedFiles: []
    }
  },
  created() {
    this.$http.get('/api/evaluator/' + this.$route.params.userID + '/evaluated')
      .then((res) => {
        this.evaluatedFiles = res.data.evaluated_list
      })
      .catch((err) => {
        console.error(err)
      })
  }
}
</script>

<style scoped>
div.wrapper {
  display: flex;
  justify-content: center;
  align-items: flex-start;
  flex-flow: row wrap;
}
</style>