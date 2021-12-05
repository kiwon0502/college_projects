<template>
    <div class="wrapper">
        <Menu current="manage"/>
        <TaskList :tasks="task_list"/>
    </div>
</template>

<script>
import Menu from '@/components/Admin/Task/TaskMenu.vue';
import TaskList from '@/components/Admin/Task/TaskList.vue';
export default {
    components: {
        Menu,
        TaskList
    },
    data() {
        return {
            task_list: []
        }
    },
    created () {
        this.$http.get('/api/task')
            .then((res) => {
                this.task_list = res.data.task_list
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
</style>