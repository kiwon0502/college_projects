<template>
<!--2. 참여 중인 제출자들의 목록
        - 제출자 선택 시 참여 중인 테스크 확인 -->
    <div style="margin: 10px; flex-grow: 3;">
        <div class="a">
            <div class="b">
                <div class="c bold">태스크 이름</div>
                |
                <div class="c">{{ task.name }}</div>
            </div>
            <div class="b">
                <div class="c bold">태스크 설명</div>
                |
                <div class="c">{{ task.des }}</div>
            </div>
        </div>
        <hr>
        <div class="a">
            <div class="b">
                <div class="c bold">제출 파일 개수</div>
                |
                <div class="c">{{ task.all_file_number }}</div>
            </div>
            <div class="b">
                <div class="c bold">PASS 튜플 개수</div>
                |
                <div class="c">{{ task.pass_tuple_number }}</div>
            </div>
            <div class="b">
                <div class="c bold">원본 데이터 타입 수준 튜플 수</div>
                |
                <div class="c">{{ task.data_type_level_tuple_number }}</div>
            </div>
        </div>
        <hr>
        <div class="a">
            <ul>
                <li>
                    <b-button variant="info" @click="CreateFile" type="file">파일 생성</b-button>
                </li>
                <li>
                    <b-button variant="info" @click="Download" type="file">다운로드</b-button>
                </li>
            </ul>
        </div>
        <hr>

        <div class="a">
            <div class="b">
                <div class="c bold">태스크 스키마</div>
                |
                <div class="c" v-for="attribute in table_Schema" :key="attribute.a">{{ attribute.a }}</div>
            </div>
        </div>
        <hr>

        <div class="a" v-for="data_type in originData_type" :key="data_type.id">
            <div class="b">
                <div class="c bold">원본 데이터 타입</div>
                |
                <div class="c" v-for="attribute in data_type" :key="attribute.a">{{attribute.a}}</div>
            </div>
        </div>
        
        <hr>
        <UserView :users="user_list"/>
    </div>
</template>

<script>
import UserView from '@/components/Admin/Task/Stat/UserView.vue';
export default {
    components: {
        UserView
    },
    data () {
        return {
            task: {},
            user_list: [],
            table_Schema: [],
            originData_type: [],
            fileName: '',
            status: false
        }
    },
    created () {
        this.$http.get('/api/task/' + this.$route.params.taskName)
            .then((res) => {
                this.task = res.data.task
                this.user_list = res.data.user_list
                this.table_Schema = res.data.tableSchema
                this.originData_type = res.data.originData_type
                this.fileName = res.data.fileName
            })
            .catch((err) => {
                console.error(err)
            })
    },
    methods: {
        CreateFile() {
            this.$http.get('/api/createFile/' + this.task.name)
                .then((res) => {
                    if(res.data.stat == 0) {
                        alert("파일을 성공적으로 생성했습니다.");
                        this.fileName = res.data.filename;
                    }
                    else alert("다시 시도해주세요.")
                })
                .catch((err) => {
                    console.error(err)
                })
        },
        Download() {
            this.$http.get('/api/download/' + this.fileName)
                .then((res) => {
                    if (res.data != "해당 파일이 없습니다.") {
                        console.log("download success")
                        const url = window.URL.createObjectURL(new Blob([res.data], { type: res.headers['content-type'] }));
                        const link = document.createElement('a');
                        link.href = url;
                        link.setAttribute('download', this.fileName + '.csv');
                        document.body.appendChild(link);
                        link.click();
                    }
                    else {
                        alert("해당 파일이 없습니다.");
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
ul > li {
  font-size : large;
  display : inline-block;
  margin : 0 80px;
  font-weight : bold;
}
</style>