<template>
    <div class="content">
        <div v-if ="!isEmpty" class="table">
            <MemList :MemData="{id: '회원번호', name: '회원 이름'}" rowType="tableHeader" />
            <div style="display: table-row">
                <div class="table-hr"></div>
                <div class="table-hr"></div>
            </div>
            <MemList v-for="member in members" :key="member.name" :MemData="member" />
        </div>
        <div v-else>
            <h1 class="no-margin">아직 가입한 회원이 없습니다.</h1>
        </div>
    </div>
</template>

<script>
import MemList from './Member.vue';
export default {
    props: {
        members: {
            type: Array,
            required: true
        }
    },
    components: {
        MemList
    },
    computed: {
        isEmpty() {
            if (this.members.length === 0) {
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
