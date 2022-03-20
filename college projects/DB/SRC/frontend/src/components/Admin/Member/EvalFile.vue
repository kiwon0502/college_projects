<template>
    <div class="content">
        <div v-if ="!isEmpty" class="table">
            <FileList :fileData="{id: '파일 ID', score: '평가 점수', pnp: 'PASS 여부'}" rowType="tableHeader" />
            <div style="display: table-row">
                <div class="table-hr"></div>
                <div class="table-hr"></div>
                <div class="table-hr"></div>
            </div>
            <FileList v-for="file in files" :key="file.id" :fileData="file" />
        </div>
        <div v-else>
            <h1 class="no-margin">제출자 입니다.</h1>
        </div>
    </div>
</template>

<script>
import FileList from '@/components/Admin/Member/File.vue';
export default {
    props: {
        files: {
            type: Array,
            required: true
        }
    },
    components: {
        FileList
    },
    computed: {
        isEmpty() {
            if (this.files.length === 0) {
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
