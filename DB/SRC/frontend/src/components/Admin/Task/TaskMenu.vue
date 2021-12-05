<template>
    <div class="menu">
        <div :class="showall_style" @click="on_click_showall">
            TASK 통계
        </div>
        <div :class="create_style" @click="on_click_create">
            TASK 생성
        </div>
        <div :class="manage_style" @click="on_click_manage">
            TASK 관리
        </div>
    </div>
</template>

<script>
export default {
    props: {
        current: {
            type: String,
            required: true
        }
    },
    computed: {
        showall_style() {
            return {
                list: true,
                current: this.current === "showall"
            }
        },
        create_style() {
            return {
                list: true,
                current: this.current === "create"
            }
        },
        manage_style() {
            return {
                list: true,
                current: this.current === "manage"
            }
        }
    },
    methods: {
        on_click_showall() {
            if (this.current === "showall") return
            this.$router.push('/admin/task/showall')
        },
        on_click_create() {
            if (this.current === "create") return
            this.$router.push('/admin/task/create')
        },
        on_click_manage() {
            if (this.current === "manage") return
            this.$router.push('/admin/task/manage')
        }
    }
}
</script>

<style scoped>
div.menu {
  width: 800px;
  background-color: #cccccc;
  padding: 5px 20px;
  margin: 35px;
}

div.list {
  display: inline-block;
  width:225px;
  height:50px;
  margin: 10px;
  padding: 14px 0px;
  background-color:  #f2f2f2;
}

div.list:hover:not(.current) {
  background-color: #257e70ad;
  font-weight: bold;
  cursor: pointer;
}

div.list:active:not(.current) {
  background-color: #f2f2f2;
}

div.current {
  background-color: #247e70;
  color: white;
  font-weight: bold;
}
</style>
