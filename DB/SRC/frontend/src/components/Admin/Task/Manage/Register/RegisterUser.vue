<template>
    <div :class="rowType" @click="approval">
        <div class="tableCell">
            {{ userData.id }}
        </div>
        <div class="tableCell">
            {{ userData.name }}
        </div>
        <div class="tableCell">
            {{ userData.score }}
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
    },
    methods: {
        approval(evt) {
            evt.preventDefault()
            this.$http.post('/api/task/' + this.$route.params.taskName + '/Register/' + this.userData.id, 
            {approval: true}, {"Content-Type": "application-json"})
                .then((res) => {
                    // post가 성공하면
                    if (res.data.success) {
                        alert('정상적으로 승인되었습니다')
                        this.$route.push(this.$route.path + '/' + this.taskName.toString());
                    } else {
                        alert("승인 과정에서 오류가 발생하였습니다.")
                    }
                })
                .catch((err) => {
                    console.error(err)
                })
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
