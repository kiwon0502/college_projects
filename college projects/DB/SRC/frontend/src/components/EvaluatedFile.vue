<template>
  <div :class="rowType">
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
      <span v-if="typeof(fileData.p_np) === 'number'">
        {{ fileData.p_np === 1 ? 'Pass' : 'Non-Pass' }}
      </span>
      <span v-else>
        {{ fileData.p_np }}
      </span>
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
.tableCell {
  display: table-cell;
  border-radius: 5px;
  /* border: 1px solid black; */
  background-color:white;
  padding: 2px;
  vertical-align: middle;
}
</style>
