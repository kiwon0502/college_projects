<template>
    <div class="wrapper">
        <Menu current="search"/>
        <div class="column">
            <div id="IDSearch">
                <b-col sm="2">
                    <label for="ID">회원 번호:</label>
                </b-col>
                <b-col sm="10">
                    <b-form-input id="ID" size="lg" v-model="SearchData.id"></b-form-input>
                </b-col>
            </div>
            <hr>
            <div id="Age">
                <b-col sm="2">
                    <label for="age">나이:</label>
                </b-col>
                <b-col sm="10">
                    <b-form-input id="age" size="lg" v-model="SearchData.age"></b-form-input>
                </b-col>
            </div>
            <hr>
            <div id="role">
                <b-col sm="2">
                    <label for="role">역할:</label>
                </b-col>
                <b-col sm="10">
                    <b-form-input id="role" size="lg" v-model="SearchData.role"></b-form-input>
                </b-col>
            </div>
            <hr>
            <b-button variant="outline-primary" @click="onSearch">검색</b-button>
            <b-button variant="danger" @click="onReset">초기화</b-button>
        <div>
        <MemberInfo :members="member_list"/>
    </div>
</template>

<script>
import Menu from '@/components/Admin/Member/Menu.vue';
import MemberInfo from '@/components/Admin/Member/MemberInfo.vue';
export default {
    components: {
        Menu,
        MemberInfo
    },
    data() {
        return {
            SearchData: {
                id: '',
                age: '',
                role: ''
            },
            member_list : []
        }
    },
    methods: {
        onSearch(evt) {
            evt.preventDefault()
            this.$http.post('/api/member/search', {userId: this.SearchData.id, 
            userAge: this.SearchData.age, userRole: this.SearchData.role}, {"Content-Type": "application-json"})
                .then((res) => {
                    this.member_list = res.data.member_list
                })
                .catch((err) => {
                    console.error(err)
                })
        },
        onReset(evt) {
            evt.preventDefault()
                // Reset our form values
                this.SearchData.id = ''
                this.SearchData.age = ''
                this.SearchData.role = ''
        }
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
div.column {
    flex-grow: 3;
}
</style>