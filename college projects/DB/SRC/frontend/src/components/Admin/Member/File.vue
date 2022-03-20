<template>
    <div :class="rowType">
        <div class="tableCell">
            {{ fileData.id }}
        </div>
        <div class="tableCell">
            {{ fileData.score }}
        </div>
        <div class="tableCell">
            {{ fileData.pnp }}
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
    /* background-color: #96ffff; */
    background-color: white;
    /* background-color: rgb(135,206,235); */
    padding: 2px;
    vertical-align: middle;
}
</style>
