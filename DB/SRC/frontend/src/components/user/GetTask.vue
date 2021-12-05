<template>
  <div v-if="user">
    <br>

    <h3>
      신청 가능한 Task 목록
    </h3>
    <b-table :fields="fields" :items="rTask">
      <template #cell(name)="data">
      <!-- 테스크 표 테스크 클릭 시 선택 가능 selected 에 저장 -->
      <b-button size="sm" variant="info" @click="selectTask(data.value)">{{ data.value }}</b-button>
    </b-table>

    <div class="s_task"> Selected Task : {{ selected }} </div>

    <br>

    <h3>
      신청 대기 중인 목록
    </h3>
    <b-table :fields="fields" :items="wTask"></b-table>

    <br>

    <div class="check">
        <b-form-checkbox
          id="checkbox-1"
          v-model="status"
          name="checkbox-1"
          value="true"
          unchecked-value="false"
        >
          개인정보 이용동의서에 동의하신다면 체크하십시오.(필수)  
        </b-form-checkbox>
    </div>
    <div class="detail_btn">
        <b-button v-b-toggle.collapse-1 variant="info">자세히</b-button>
    </div>

    <b-collapse id="collapse-1" class="mt-2">
      <b-card>
        <p class="card-text">
          귀하의 개인정보는 시스템 운용을 위해 시스템 내부에서 이용될 수 있습니다. 외부로 방출되어 사용되지 않습니다.
          동의하신다면 위 체크박스를 체크하여 주십시오.
        </p>
      </b-card>
    </b-collapse>
    <br>

    <ul>
      <li>
        <button type="submit" @click="registerTask">TASK 신청</button>
      </li>
      <li>
        <button type="submit" class="red" @click="backPage">뒤로 가기</button>
      </li>
    </ul>
    <ul>
      <p>© ED's DBD</p>
    </ul>
  </div>
</template>

<script>
export default {
  created() {
      this.$http.post('/api/getRTable', this.$route.params.userID)
          .then((res) => {
              this.rTask = res.data.rTask;
              this.wTask = res.data.wTask;
          })
          .catch((err) => {
              console.error(err)
          })
  },
  data () {
      return {
            selected: '',
            fields: [
                {key: 'name', label: 'TASK 이름'},
                {key: 'period', label: '최소 업로드 주기'},
                {key: 'description', label: '설명'}
            ],
            rTask: [],
            wTask: [],
            status: 'false'
      }
  },
  methods: {
    backPage() {
      this.$router.push({name: "Submitter"});
    },
    selectTask(value) {
        this.selected = value;
    },
    registerTask() {
      if (this.selected != '' && this.status == 'true') {
        this.$http.post('/api/registerTask', {taskName: this.selected, userID: this.$route.params.userID})
          .then((res) => {
            if(res.data.stat == 0){
              alert('태스크 신청이 완료되었습니다.');
            }
          })
          .catch((err) => {
            console.error(err)
          });

        // 테이블 다시 리로드
        this.$http.post('/api/getRTable', this.$route.params.userID)
          .then((res) => {
              this.rTask = res.data.rTask;
              this.wTask = res.data.wTask;
          })
          .catch((err) => {
              console.error(err)
          });
      }
      else {
        if (this.selected == '') {
          alert("선택된 TASK가 없습니다.");
        }
        else {
          alert("개인정보 이용동의를 하십시오.");
        }
      } 
    }
  },
  computed:{
     user() {return this.$store.getters.user;}  
  }
}
</script>

<!-- Add "scoped" attribute to limit CSS to this component only -->
<style scoped>
ul {
  position : relative;
  top : 80px;
  list-style-type : none;
  padding : 0;
}
ul > li {
  font-size : large;
  display : inline-block;
  margin : 0 80px;
  font-weight : bold;
}
ul > p {
  position : relative;
  top : 300px;
  padding-bottom : 40px;
  font-size : small;
}
.red{background-color: tomato!important;}
.red:hover{background-color: rgba(255, 99, 71, 0.849)!important;}
button[type=submit]{background-color: #247e70;color: white;padding: 14px 20px;margin: 8px 0;border: none;border-radius: 4px;cursor: pointer;}
button[type=submit]:hover{background-color: #257e70ad;}
.s_task{text-align: left; padding: 10px;}
h3{padding-bottom: 20px; font-weight: bold;}
.check{display: flex; padding-bottom: 10px;}
.detail_btn{display: flex;}
</style>