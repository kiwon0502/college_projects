<template>
  <div class="wrapper">
    <Menu current="showall"/>
    <TaskDetail/>
  </div>
</template>

<script>
import Menu from '@/components/Admin/Task/TaskMenu.vue';
import TaskDetail from '@/components/Admin/Task/TaskDetail.vue';
export default {
  components: {
    Menu,
    TaskDetail
  }
}
</script>

<style scoped>
div.wrapper {
  display: flex;
  justify-content: center;
  align-items: flex-start;
}
</style>