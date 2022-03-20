<template>
  <div :class="rowType" @click="goTo">
    <div class="tableCell">
      {{ fileData.id }}
    </div>
    <div class="tableCell">
      {{ fileData.task }}
    </div>
    <div class="tableCell">
      {{ fileData.type }}
    </div>
    <div class="tableCell">
      {{ fileData.number }}
    </div>
    <div class="tableCell">
      {{ fileData.start_period }}
      <span v-if="fileData.end_period !== ''"> ~ {{ fileData.end_period }}</span>
    </div>
  </div>
</template>

<script>
export default {
  props: {
    fileData: {
      type: Object,
      required: true
    },
    rowType: {
      type: String,
      default: 'tableRow'
    }
  },
  methods: {
    goTo () {
      if (this.fileData.id === 'ID') return
      this.$router.push(this.$route.path + '/' + this.fileData.id.toString())
    }
  }
}
</script>

<style scoped>
.tableHeader {
  display: table-header-group;
  font-weight: bold;
  text-align: center;
}
.tableRow {
  display: table-row;
}
.tableRow:hover > .tableCell {
  background-color: #f2f2f2;
  cursor: pointer;
}
.tableCell {
  display: table-cell;
  border-radius: 5px;
  /* background-color: #96ffff; */
  background-color: white;
  /* background-color: rgb(135,206,235); */
  padding: 2px;
  vertical-align: middle;
}
</style>
