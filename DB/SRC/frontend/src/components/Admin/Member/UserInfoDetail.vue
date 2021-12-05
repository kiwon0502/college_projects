<template>
    <div style="margin: 10px;">
        <div class="a">
            <div class="b">
                <div class="c bold">ID</div>
                |
                <div class="c">{{ user[0].id }}</div>
            </div>
            <div class="b" style="width: 30%;">
                <div class="c bold">Name</div>
                |
                <div class="c">{{ user[0].name }}</div>
            </div>
        </div>
        <hr>
        <div class="a">
            <div class="b">
                <div class="c bold">역할</div>
                |
                <div class="c">{{ user[0].role }}</div>
            </div>
            <div class="b">
                <div class="c bold">성별</div>
                |
                <div class="c">{{ user[0].gender }}</div>
            </div>
        </div>
        <hr>
        <TaskInfo :taskinfo="user[0].taskinfo"/>
        <!--<FileInfo :files="user[0].fileList" v-if="ifEvaluator"/>-->
    </div>
</template>

<script>
import TaskInfo from '@/components/Admin/Member/UserTask.vue';
//import FileInfo from '@/components/Admin/Task/Stat/TaskInfo.vue';
export default {
    components: {
        Tasklist
    },
    props: {
        user: {
            type: Array,
            required: true
        }
    }
}
</script>

<style scoped>
.a {
    background-color: #cccccc;
    border-radius: 3px;
    padding: 4px;
    margin: 4px, 0px;
    /* font-size: 2em; */
}
.b {
    display: inline-flex;
    justify-content: center;
    align-items: center;
    background-color: #fff;
    width: 15%;
    border-radius: 4px;
    padding: 4px;
    margin: 3px 3px;
}
.c {
    display: inline-block;
    height: 100%;
    padding: 0px 5px;
}
.bold {
    font-weight: bold;
}

table {
    /* border-collapse: collapse; */
    border-spacing: 0px;
    padding: 10px;
}
th {
    border: 1px solid black;
    border-bottom: 3px solid black;
    padding: 4px;
}
td {
    border: 1px solid black;
    padding: 4px;
}
table thead th:first-child {
    border-radius: 5px 0 0 0;
}
table thead th:last-child {
    border-radius: 0 5px 0 0;
}
table tbody tr:last-child td:first-child {
    border-radius: 0 0 0 5px;
}
table tbody tr:last-child td:last-child {
    border-radius: 0 0 5px 0;
}
</style>
