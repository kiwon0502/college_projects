<template>
    <div class="menu">
        <div :class="showlist_style" @click="on_click_showlist">
            가입 회원 정보
        </div>
        <div :class="search_style" @click="on_click_search">
            회원 검색
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
        showlist_style() {
            return {
                list: true,
                current: this.current === "showlist"
            }
        },
        search_style() {
            return {
                list: true,
                current: this.current === "search"
            }
        }
    },
    methods: {
        on_click_showlist() {
            if (this.current === "showlist") return
            this.$router.push('/admin/member/showlist')
        },
        on_click_search() {
            if (this.current === "search") return
            this.$router.push('/admin/member/search')
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
  width:270px;
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

