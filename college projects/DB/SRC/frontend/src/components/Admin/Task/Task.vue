<template>
    <div :class="rowType" @click="goTo">
        <div class="tableCell">
            {{ taskData.name }}
        </div>
        <div class="tableCell">
            {{ taskData.des }}
        </div>
        <div class="tableCell">
            {{ taskData.upload }}
        </div>
        <div class="tableCell">
            {{ taskData.table_name }}
        </div>
        <div class="tableCell">
            {{ taskData.table_schema }}
        </div>
        <div class="tableCell">
            {{ taskData.data_type }}
        </div>
    </div>
</template>

<script>
export default {
    props: {
        taskData: {
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
            this.$router.push(this.$route.path + '/' + this.taskData.name.toString())
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
    background-color: rgb(209, 242, 255);
    /* background-color: rgb(135,206,235); */
    padding: 2px;
    vertical-align: middle;
}
</style>
