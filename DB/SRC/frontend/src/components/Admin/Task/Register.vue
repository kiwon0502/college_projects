<template>
    <div class="content">
        <div v-if ="!isEmpty" class="table">
            <UserList :userData="{id: 'ID', name: '신청자 이름', score: '평가 점수'}" rowType="tableHeader"/>
            <div style="display: table-row">
                <div class="table-hr"></div>
                <div class="table-hr"></div>
                <div class="table-hr"></div>
            </div>
            <UserList v-for="user in register_list" :key="user.id" :userData="user" />
        </div>
        <div v-else>
            <h1 class="no-margin">아직 신청 대기중인 회원이 없습니다.</h1>
        </div>
    </div>
</template>

<script>
import UserList from './RegisterUser.vue';
export default {
    props: {
        users: {
            type: Array,
            required: true
        }
    },
    components: {
        UserList
    },
    computed: {
        isEmpty() {
            if (this.users.length === 0) {
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
    flex-grow: 3;
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
