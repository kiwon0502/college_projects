<template>
    <div>
        <label for="range-1">데이터 PASS 기준 재설정</label>
        <b-form-input id="range-1" v-model="standard" type="range" min="0" max="10" step="0.5"></b-form-input>
        <div class="mt-2">Score: {{ standard }}</div>
        <b-button @click="resetStandard">수정</b-button>
    </div>
</template>

<script>
export default {
    props: ['standard'],
    methods: {
        resetStandard(evt) {
            evt.preventDefault()
            this.$http.post('/api/task/' + this.$route.params.taskName + '/resetStandard', {standard: this.standard}, {"Content-Type": "application-json"})
                .then((res) => {
                    // post가 성공하면
                    if (res.data.success) {
                        alert('정상적으로 수정되었습니다.')
                        this.$route.push("/admin/task/manage/" + this.$route.params.taskName)
                    } else {
                        alert("수정 과정에서 오류가 발생하였습니다.")
                    }
                })
                .catch((err) => {
                    console.error(err)
                })
        },
    }
}
</script>

<style>
</style>