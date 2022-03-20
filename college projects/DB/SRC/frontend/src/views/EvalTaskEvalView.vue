<template>
  <div class="wrapper">
    <Menu current="todo"/>
    <EvaluationPage/>
  </div>
</template>

<script>
import Menu from '@/components/EvalMenu.vue';
import EvaluationPage from '@/components/EvalTodoTask.vue';
export default {
  components: {
    Menu,
    EvaluationPage
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