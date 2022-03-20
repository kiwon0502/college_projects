<template>
  <form v-on:submit.prevent="checkForm" class='form'>
    <div>
      <label for="name">이름 :</label>
      <input id="name" type="text" v-model="name" />
    </div>
    <div>
      <label for="id">아이디 :</label>
      <input id="id" type="text" v-on:blur='checkId' v-model="id"/>
			<small id="id_check" v-bind:class="{red: !rightID, green: rightID}">{{id_check_str}}</small>
			<!-- <button v-on:click='checkId'>아이디 중복체크</button> -->
    </div>
    <div>
      <label for="password">비밀번호 :</label>
      <input id="password" type="password" v-model="password"  />
    </div>
		    <div>
      <label for="password_check">비밀번호 확인 :</label>
      <input id="password_check" type="password" v-model="password_check"  />
    </div>
    <div>
      <label for="phone_number">휴대폰 번호:</label>
      <input id="phone_number1" type="text" class="phone_number" maxlength="3" v-model="phone_number1"  />
      <small>-</small>
      <input id="phone_number2" type="text" class="phone_number" maxlength="4" v-model="phone_number2"  />
      <small>-</small>
      <input id="phone_number3" type="text" class="phone_number" maxlength="4" v-model="phone_number3"  />
    </div>
    <div>
      <label for="address">주소:</label>
      <input id="address" type="textarea" v-model="address"  />
    </div>
    <div>
      <label for="birthday">생일:</label>
      <input id="birthday" type="date" min='1900-01-01' v-model="birthday"  />
    </div>
    <div>
      <label for="type">권한:</label>
			<fieldset>
				<input id='type1' class='type' type='radio' value='submitter' v-model='type'/>
				<label for='type1' class='radio-label'>제출자</label>
				<input id='type2' class='type' type='radio' value='evaluator' v-model='type'/>
				<label for='type2' class='radio-label'>평가자</label>
			</fieldset>
		</div>
    <button type="submit">회원가입</button>
  </form>
</template>

<script>
import '@/style/base.css'
export default {
	data: function() {
		return {
			id:'',
			password:'',
			password_check:'',
			name:'',
			phone_number1:'',
			phone_number2:'',
			phone_number3:'',
			address:'',
			birthday:'',
			type:'',
			id_check_str:'',
			rightID:false,
			// user:null,
		};
	},
	methods: {
	checkId: function()	{
		var RegExp = /^[a-zA-Z0-9]{4,12}$/; //id와 pwassword 유효성 검사 정규식
		if(!this.id)	{
			// alert("아이디를 입력해주세요.");
			return false;
		}
		if(!RegExp.test(this.id)){ //아이디 유효성검사
			this.id_check_str="아이디는 4~12자의 영문 대소문자와 숫자로만 입력해주세요.";    
			this.rightID=false;    
			return false;
		}
		var params = {
			id: this.id
		}
		this.$http.post('/api/check_id', params)
			.then((response)=>{
				if(response.data['STAT']==1)	{
					alert("다시 시도해 주세요.");
					return false;
				}
				if(response.data['STAT']==2)	{
					this.id_check_str="이미 존재하는 아이디 입니다.";
					this.rightID = false;
					return false;
				}
				if(response.data['STAT']==0)	{
					this.id_check_str="사용 가능한 아이디 입니다.";
					this.rightID = true;
					return true;
				}
			})
			.catch((error)=>{
				console.log(error);
			});
	},
	checkForm: function()	{
		console.log("checkForm");
		var RegExp = /^[a-zA-Z0-9]{4,12}$/; //id와 pwassword 유효성 검사 정규식
		var n_RegExp = /^[a-zA-Z가-힣]{2,15}$/; //이름 유효성검사 정규식
		var num_RegExp = /^[0-9]*$/; //숫자 유효성검사 정규식

		// console.log(this.id);
		// console.log(this.name);
		// console.log(this.password);
		// console.log(this.password_check);
		// console.log(this.phone_number1);
		// console.log(this.phone_number2);
		// console.log(this.phone_number3);
		// console.log(this.address);
		// console.log(this.birthday);
		// console.log(this.type);
		// ================ 이름 유효성검사 ================ //        
		if(!this.name){
			alert("이름을 입력해주세요.");
			return false;
		}
		if(!n_RegExp.test(this.name)){
			alert("유효한 이름을 입력해주세요.");
			return false;
		}
		// ================ ID 유효성검사 ===============//
		if(!this.rightID)	{
			alert("유효한 아이디를 입력해주세요.")
			return false;
		}
		// ================ PASSWORD 유효성검사 ===============//
		if(!this.password){ // 비밀번호 입력여부 검사
			alert("비밀번호를 입력해주세요.");
			return false;
		}
		if(!RegExp.test(this.password)){ //패스워드 유효성검사
			alert("비밀번호는 4~12자의 영문 대소문자와 숫자로만 입력해주세요.");
			return false;
		}
		if(this.id==this.password){ //패스워드와 ID가 동일한지 검사
			alert("아이디와 비밀번호가 동일합니다.");
			return false;
		}
		if(this.password!=this.password_check){ //비밀번호와 비밀번호확인이 동일한지 검사
			alert("비밀번호가 틀립니다. 다시 확인하여 입력해주세요.");
			return false;
		}        
		// ================ 전화번호 유효성검사 ================ //  
		if(!this.phone_number1 || !this.phone_number2 || !this.phone_number3)	{
			alert("핸드폰 번호를 입력해 주세요.");
			return false;
		} 
		var phone_number = this.phone_number1 + this.phone_number2 + this.phone_number3;
		if(!num_RegExp.test(phone_number))	{
			alert("핸드폰 번호는 숫자만 입력해 주세요.");
			return false;
		}
		// ================ 주소 유효성검사 ===============//
		if(!this.address)	{
			alert("주소를 입력하세요.");
			return false;
		}
		// ================ 생년월일 유효성검사 ================ //  
		if(!this.birthday)	{
			alert("생일을 입력해주세요.");
			return false;
		}
		// ================ 권한 유효성검사 ================ //  
		if(!this.type)	{
			alert("권한을 선택해주세요.");
			return false;
		}	
		this.submitForm();
	},
	submitForm: function(){
		var data = {
			id: this.id,
			password: this.password,
			name:this.name,
			phone_number: this.phone_number1 + this.phone_number2 + this.phone_number3,
			address: this.address,
			birthday: this.birthday,
			type: this.type,
			score: 0
		}
		console.log(data);
		this.$http.post('/api/sign_up', data)
			.then((response)=>{
				if(response.data['STAT']==0)	{
					alert('회원가입이 완료되었습니다.');
					this.$router.push({name:"LoginPage"});
				}
			})
			.catch(function(error){
				console.log(response);
			});
	}},

	/*
	created(){
			this.$http.get('/api/login')
			.then((res) => {
					const user = res.data.user;
					if(user) this.user = user;
			})
			.catch((err) => {
					console.error(err);
			});
	}*/
}
</script>

<style scoped>
.form{border-radius: 5px;background-color: #f2f2f2;padding: 20px;padding-right:100px;}
label{width: 120px; text-align: right;}
.radio-label{width:50px;}
fieldset{display:inline;width: 250px;padding: 12px 20px;margin: 8px 0;border: 1px solid #ccc;border-radius: 4px;box-sizing: border-box;}
button[type=submit]{width: 250px;background-color: #247e70;color: white;padding: 14px 20px;margin-left:125px;border: none;border-radius: 4px;cursor: pointer;}
button[type=submit]:hover{background-color: #257e70ad;}
input, select {width: 250px;padding: 12px 20px;margin: 8px 0;border: 1px solid #ccc;border-radius: 4px;box-sizing: border-box;}
.phone_number{width: 77px;}
.type{width: 40px;}
</style>