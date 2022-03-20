<template>
  <div class="wrapper">
    <Menu current="todo"/>
    <AllocList :files="allocatedFiles"/>
  </div>
</template>

<script>
import Menu from '@/components/EvalMenu.vue';
import AllocList from '@/components/AllocatedFileList.vue';
export default {
  components: {
    Menu,
    AllocList
  },
  data() {
    return {
      allocatedFiles: [
        { id: 5, task: 'android', type: 'seoul', number: 1, start_period: '2020-11-22', end_period: '2020-11-23'},
        { id: 8, task: 'windows10', type: 'busan', number: 1, start_period: '2020-11-22', end_period: '2020-11-26'},
      ]
    }
  },
  created() {
    this.$http.get('/api/evaluator/' + this.$route.params.userID + '/todo')
      .then((res) => {
        this.allocatedFiles = res.data.todo_list
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