<template>
  <div class="parent">
    <div class="half">
      <div v-if ="!allocEmpty" class="table">
        <AllocatedTask :taskData="{id: 'ID', task: 'Task 이름', type: '원본 Data Type', number: '회차', start_period: '기간', end_period: ''}" rowType="tableHeader" />
        <div style="display: table-row">
          <div class="table-hr"></div>
          <div class="table-hr"></div>
          <div class="table-hr"></div>
          <div class="table-hr"></div>
          <div class="table-hr"></div>
        </div>
        <AllocatedTask v-for="task in allocatedTasks" :key="task.id" :taskData="task" />
      </div>
      <div v-else>
        <h1 class="no-margin">배정된 Task가 없습니다.</h1>
      </div>
    </div>
    <div class="half">
      <div v-if="!evalEmpty" class="table">
        <EvaluatedTask :taskData="{id: 'ID', task: 'Task 이름', type: '원본 Data Type', number: '회차', p_np: 'Pass'}" rowType="tableHeader" />
        <div style="display: table-row">
          <div class="table-hr"></div>
          <div class="table-hr"></div>
          <div class="table-hr"></div>
          <div class="table-hr"></div>
          <div class="table-hr"></div>
        </div>
        <EvaluatedTask v-for="task in evaluatedTasks" :key="task.id" :taskData="task" />
      </div>
      <div v-else>
        <h1 class="no-margin">아직 평가한 Task가 없습니다.</h1>
      </div>
    </div>
  </div>
</template>

<script>
import AllocatedTask from '@/components/AllocatedTask.vue'
import EvaluatedTask from '@/components/EvaluatedTask.vue'
export default {
  components: {
    AllocatedTask,
    EvaluatedTask
  },
  data () {
    return {
      allocatedTasks: [],
      evaluatedTasks: []
    }
  },
  computed: {
    allocEmpty () {
      if (this.allocatedTasks.length === 0) {
        return true
      } else {
        return false
      }
    },
    evalEmpty () {
      if (this.evaluatedTasks.length === 0) {
        return true
      } else {
        return false
      }
    }
  },
  created () {
    this.$http.get('/api/evaluator/' + this.$route.params.userID)
      .then((res) => {
        this.allocatedTasks = res.data.todo_list
        this.evaluatedTasks = res.data.evaluated_list
      })
      .catch((err) => {
        console.error(err)
      })
  }
}
</script>

<style scoped>
div {
  margin: 0px;
  padding: 0px;
}
.parent {
  display: flex;
  align-items: flex-start;
}
.half {
  background-color: #cccccc;
  margin: 10px;
  padding: 2px;
  width: 100%;
}
.table {
  width: 100%;
  display: table;
  border-spacing: 2px;
  margin: 0px;
  padding: 0px;
}
.table-hr {
  display: table-cell;
  border-bottom: 1px solid black;
}
.no-margin {
  margin: 0;
}
</style>
