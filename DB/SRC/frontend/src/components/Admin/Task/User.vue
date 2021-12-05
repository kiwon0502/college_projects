<template>
    <div :class="rowType">
        <div class="tableCell">
            {{ userData.id }}
        </div>
        <div class="tableCell">
            {{ userData.name }}
        </div>
    </div>
</template>

<script>
export default {
    props: {
        userData: {
            type: Object,
            required: true
        },
        rowType: {
            type: String,
            default: 'tableRow'
        }
    },/*<div :class="rowType" @click="goTo">
    methods: {
        goTo () {
            this.$router.push('/admin/' + this.userData.id.toString())
        }
    }*/
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
