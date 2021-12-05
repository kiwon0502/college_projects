<template>
    <div class="menu">
        <div :class="show_style">
            회원 상세 정보
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
        show_style() {
            return {
                list: true,
                current: this.current === "show"
            }
        },
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
