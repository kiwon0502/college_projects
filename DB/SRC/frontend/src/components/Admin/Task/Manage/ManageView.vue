<template>
    <div class="wrapper">
        <Menu current="manage"/>
        <div class="column">
            <div id="register">
                <Register :registers="register_list"/>
            </div>

            <hr>
            <div class="content" id="reset">
                <ResetSt :standard="value"/>
            </div>

            <hr>
            <div id="addtype">
                <AddType />
            </div>
        <div>
    </div>
</template>

<script>
import Menu from '@/components/Admin/Task/TaskMenu.vue';
import Register from '@/components/Admin/Task/Manage/Register/Register.vue';
import ResetSt from '@/components/Admin/Task/Manage/ResetStand/ResetStandard.vue';
import AddType from '@/components/Admin/Task/Manage/AddType/AddType.vue';
export default {
    components: {
        Menu,
        Register,
        ResetSt,
        AddType
    },
    data () {
        return {
            register_list: [],
            value: ''
        }
    },
    created () {
        this.$http.get('/api/task/' + this.$route.params.taskName + '/manage')
            .then((res) => {
                this.register_list = res.data.register_list
                this.value = res.data.task_standard
            })
            .catch((err) => {
                console.error(err)
            })
    }
}
</script>

<style scoped>
div.wrapper {
  display: flex;
  justify-content: center;
  align-items: flex-start;
}
div.content {
    background-color: #cccccc;
    padding: 5px;
    margin: 10px;
}
div.column {
    flex-grow: 3;
}
</style>