<template>
    <div style="flex-grow: 3;">
        <b-form @submit="onSubmit" @reset="onReset" v-if="show">
            <b-form-group id="input-group-1" label="TASK 이름:" label-for="input-1">
                <b-form-input
                    id="input-1"
                    v-model="form.name"
                    required
                    placeholder="TASK 이름을 입력하세요."
                ></b-form-input>
            </b-form-group>

            <b-form-group id="input-group-2" label="TASK 설명:" label-for="input-2">
                <b-form-input
                    id="input-2"
                    v-model="form.des"
                    required
                    placeholder="TASK에 대한 간략한 설명을 써주세요."
                ></b-form-input>
            </b-form-group>

            <b-form-group id="input-group-3" label="최소업로드 주기:" label-for="input-3">
                <b-form-input
                    id="input-3"
                    v-model="form.min_submit_period"
                    required
                    placeholder="TASK에 제출할 파일의 최소업로드 주기를 입력하세요."
                ></b-form-input>
            </b-form-group>

            <b-form-group id="input-group-4" label="제출 파일 PASS 기준:" label-for="input-4">
                <b-form-input
                    id="input-4"
                    v-model="form.standard"
                    required
                    placeholder="제출 파일이 PASS 되는 기준 점수를 입력하세요."
                ></b-form-input>
            </b-form-group>

            <label for="example-datepicker1">DATA 수집 시작 날짜</label>
            <b-form-datepicker id="example-datepicker" v-model="form.start" class="mb-2"></b-form-datepicker>

            <label for="example-datepicker2">DATA 수집 종료 날짜</label>
            <b-form-datepicker id="example-datepicker2" v-model="form.end" class="mb-2"></b-form-datepicker>

            <hr>
            <b-form-checkbox
                id="checkbox-1"
                v-model="form.use_sql"
                name="checkbox-1"
                value=true
                unchecked-value=false
                >
                DATA TABLE 스키마 정의 SQL 사용 여부
            </b-form-checkbox>

            <hr>
            <b-form-group id="input-group-5" label="DATA 테이블 스키마:" label-for="input-5" v-if="form.use_sql">
                <b-form-input
                    id="input-5"
                    v-model="form.taskSchema"
                    required
                    placeholder="DATA 테이블의 스키마를 설정해주세요."
                ></b-form-input>
            </b-form-group>
            <hr>

            <div><strong>DATA TABLE 스키마 설정</strong></div>
                <table class="table">
                    <thead>
                        <tr>
                            <td><strong>속성 이름</strong></td>
                            <td><strong>변수 타입</strong></td>
                            <td></td>
                        </tr>
                    </thead>
                    <tbody>
                        <tr v-for="row in attri_info" :key="row.key">
                            <td><b-form-input v-model="row.name" placeholder="이름 입력"></b-form-input></td>
                            <td><b-form-select v-model="row.type" :options="options"></b-form-select></td>
                        </tr>
                    </tbody>
                </table>
                <div>
                    <b-button id="add" variant="primary" v-on:click="addRow">속성 추가</b-button>
                    <b-button id="resetRow" variant="danger" v-on:click="resetRow">리셋</b-button>
                </div>
            <hr>

            <div><strong>원본 데이터 타입 설정</strong></div>
                <b-row class="my-1">
                    <b-col sm="2">
                        <label for="DName">원본 데이터 타입 이름:</label>
                    </b-col>
                    <b-col sm="10">
                        <b-form-input id="DName" v-model="data_type_name" placeholder="원본 데이터 타입 이름을 입력해주세요."></b-form-input>
                    </b-col>
                </b-row>
                <table class="table">
                    <thead>
                        <tr>
                            <td><strong>속성 이름</strong></td>
                            <td><strong>속성 타입</strong></td>
                            <td><strong>스키마 매핑</strong></td>
                            <td></td>
                        </tr>
                    </thead>
                    <tbody>
                        <tr v-for="row in schema_info" :key="row.key">
                            <td><b-form-input v-model="row.name" placeholder="이름 입력"></b-form-input></td>
                            <td><b-form-select v-model="row.type" :options="options"></b-form-select></td>
                            <td><b-form-input v-model="row.schema" placeholder="매핑할 스키마 입력"></b-form-input></td>
                        </tr>
                    </tbody>
                </table>
                <div>
                    <b-button id="addSchema" variant="primary" v-on:click="addSchema">속성 추가</b-button>
                    <b-button id="resetSchema" variant="danger" v-on:click="resetSchema">리셋</b-button>
                </div>
            <hr>

            <b-button type="submit" variant="success">TASK 생성</b-button>
            <b-button type="reset" variant="danger">내용 리셋</b-button>
        </b-form>      
    </div>
</template>

<script>
export default {
    data() {
        return {
            form: {
                name: '',
                des: '',
                start: '',
                end: '',
                min_submit_period: '',
                standard: '',
                use_sql: false,
                taskSchema: ''
            },
            show: true,
            attri_info: [],
            schema_info: [],
            options: [
                {value: "text", text: "text"},
                {value: "integer", text: "integer"},
                {value: "big integer", text: "big integer"},
                {value: "float", text: "float"},
                {value: "date", text: "date"},
                {value: "time", text: "time"},
                {value: "datetime", text: "datetime"}
            ],
            field_key: 1,
            schema_key: 1,
            data_type_name: ''
        }
    },
    methods: {
        onSubmit(evt) {
            evt.preventDefault()
            if(this.form.start === '') {
                alert("데이터 수집 시작 날짜를 정하세요.")
                return
            }
            if(this.form.end === '') {
                alert("데이터 수집 종료 날짜를 정하세요.")
                return
            }
            else if (this.form.end < this.form.start) {
                alert("데이터 수집 기간을 잘못 설정했습니다.")
                return
            }
            if(!this.form.use_sql) {
                if(this.attri_info.length === 0) {
                    alert("데이터 테이블 스키마를 설정하세요.")
                    return
                }
            }
            if(this.data_type_name.length === 0) {
                alert("원본 데이터 타입 이름을 입력하세요.")
                return
            }
            if(this.schema_info.length === 0) {
                alert("원본 데이터 타입을 설정하세요.")
                return
            }
            this.$http.post('/api/task/create', 
            {name: this.form.name, des: this.form.des, start_period: this.form.start, end_period: this.form.end,
            min_submit_period: this.form.min_submit_period, standard_of_pass: this.form.standard,
            use_sql: this.form.use_sql, taskSchema: this.form.taskSchema, field_info: this.attri_info, dName:this.data_type_name,
            map_info: this.schema_info}, {"Content-Type": "application-json"})
                .then((res) => {
                    // post가 성공하면
                    if (res.data.stat == 0) {
                        alert('정상적으로 테스크가 생성되었습니다.')
                        this.$route.push("/admin/task")
                    } else if (res.data.stat == -1) {
                        alert("다시 시도해 주세요.")
                    } else if (res.data.stat == 6) {
                        alert("같은 이름의 태스크 또는 원본 데이터 타입이 이미 존재합니다.");
                    }
                })
                .catch((err) => {
                    console.error(err)
                })
        },
        onReset(evt) {
            evt.preventDefault()
                // Reset our form values
                this.form.name = ''
                this.form.des = ''
                this.form.start = ''
                this.form.end = ''
                this.form.min_submit_period = ''
                this.form.standard = ''
                this.form.use_sql = false
                this.form.taskSchema = ''
                this.attri_info = []
                this.data_type_name = ''
                this.schema_info = []
                // Trick to reset/clear native browser form validation state
                this.show = false
                this.$nextTick(() => {
                this.show = true
            })
        },
        addRow(evt) {
            evt.preventDefault()
            this.attri_info.push({name: '', type: '', key: this.field_key})
            this.field_key = this.field_key + 1
        },
        resetRow(evt) {
            evt.preventDefault()
            this.attri_info = []
        },
        addSchema(evt) {
            evt.preventDefault()
            this.schema_info.push({name: '', type: '', schema: '', key: this.schema_key})
            this.schema_key = this.schema_key + 1
        },
        resetSchema(evt) {
            evt.preventDefault()
            this.data_type_name = ''
            this.schema_info = []
        }
    }
}
</script>