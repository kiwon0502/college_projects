<template>
  <div class="content">
    <div v-if ="!isEmpty" class="table">
      <AllocatedFile :fileData="{id: 'ID', task: 'Task 이름', type: '원본 Data Type', number: '회차', start_period: '기간', end_period: ''}" rowType="tableHeader" />
      <div style="display: table-row">
        <div class="table-hr"></div>
        <div class="table-hr"></div>
        <div class="table-hr"></div>
        <div class="table-hr"></div>
        <div class="table-hr"></div>
      </div>
      <AllocatedFile v-for="file in files" :key="file.id" :fileData="file" />
    </div>
    <div v-else>
      <h1 class="no-margin">할당된 파일이 없습니다.</h1>
    </div>
  </div>
</template>

<script>
import AllocatedFile from './AllocatedFile.vue';
export default {
  props: {
    files: {
      type: Array,
      required: true
    }
  },
  components: {
    AllocatedFile
  },
  computed: {
    isEmpty() {
      if (this.files.length === 0) {
        return true
      } else {
        return false
      }
    }
  }
}
</script>

<style scoped>
div.content {
  width:1000px;
  background-color: #cccccc;
  padding: 5px;
  margin: 10px;
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
