<template>
    <div class="wrapper">
        <Menu current="create"/>
        <CreateForm/>
    </div>
</template>

<script>
import Menu from '@/components/Admin/Task/TaskMenu.vue';
import CreateForm from '@/components/Admin/Task/CreateForm.vue';
export default {
    components: {
        Menu,
        CreateForm
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