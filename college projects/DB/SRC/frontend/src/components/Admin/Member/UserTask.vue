<template>
    <div class="content">
        <div v-if ="!isEmpty" class="table">
            <TaskList :taskData="{name: 'TASK 이름', fileNumber: '제출 파일 개수', tupleNumber: 'PASS 튜플 수', nullProperty: 'Null 비율'}" rowType="tableHeader" />
            <div style="display: table-row">
                <div class="table-hr"></div>
                <div class="table-hr"></div>
                <div class="table-hr"></div>
                <div class="table-hr"></div>
            </div>
            <TaskList v-for="task in tasks" :key="task.name" :taskData="task" />
        </div>
        <div v-else>
            <h1 class="no-margin">평가자 입니다.</h1>
        </div>
    </div>
</template>

<script>
import TaskList from '@/components/Admin/Member/Task.vue';
export default {
    props: {
        tasks: {
            type: Array,
            required: true
        }
    },
    components: {
        TaskList
    },
    computed: {
        isEmpty() {
            if (this.tasks.length === 0) {
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
