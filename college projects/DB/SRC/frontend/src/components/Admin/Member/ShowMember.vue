<template>
    <div class="wrapper">
        <Menu current="showlist"/>
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
            member_list: []
        }
    },
    created () {
        this.$http.get('/api/member/')
            .then((res) => {
                this.member_list = res.data.member_list
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
}
</style>