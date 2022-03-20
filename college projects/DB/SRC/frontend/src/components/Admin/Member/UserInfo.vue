<template>
  <div class="wrapper">
    <Menu current="show"/>
    <div style="margin: 10px; flex-grow: 3;">
        <div class="a">
            <div class="b">
                <div class="c bold">회원 번호</div>
                |
                <div class="c">{{ userinfo[0].id }}</div>
            </div>
            <div class="b" style="width: 30%;">
                <div class="c bold">이름</div>
                |
                <div class="c">{{ userinfo[0].name }}</div>
            </div>
        </div>
        <hr>
        <div class="a">
            <div class="b">
                <div class="c bold">역할</div>
                |
                <div class="c">{{ userinfo[0].role }}</div>
            </div>
            <div class="b">
                <div class="c bold">성별</div>
                |
                <div class="c">{{ userinfo[0].gender }}</div>
            </div>
        </div>
        <hr>
        <TaskInfo :tasks="taskinfo" />
        <FileInfo :files="fileinfo" />
    </div>
  </div>
</template>

<script>
import Menu from '@/components/Admin/Member/UserMenu.vue';
import TaskInfo from '@/components/Admin/Member/UserTask.vue';
import FileInfo from '@/components/Admin/Member/EvalFile.vue';
export default {
    components: {
        Menu,
        TaskInfo,
        FileInfo
    },
    data () {
        return {
            userinfo : [],
            taskinfo : {},
            fileinfo : {}
        }
    },
    created () {
        this.$http.get('/api/member/' + this.$route.params.userID)
            .then((res) => {
                this.userinfo = res.data.user_info
                this.taskinfo = res.data.task_info
                this.fileinfo = res.data.file_info
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
  flex-flow: row wrap;
}
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
</style>