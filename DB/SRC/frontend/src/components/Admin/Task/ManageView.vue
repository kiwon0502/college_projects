<template>
  <div class="wrapper">
    <Menu current="manage"/>
    <Register :registers="register_list"/>
  </div>
</template>

<script>
import Menu from '@/components/Admin/Task/TaskMenu.vue';
import Register from '@/components/Admin/Task/Register.vue';
export default {
    components: {
        Menu,
        Register
    },
    data () {
        return {
            register_list: [],
        }
    },
    created () {
        this.$http.get('/api/task/' + this.$route.params.taskName + '/Register')
            .then((res) => {
                this.register_list = res.data.register_list
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