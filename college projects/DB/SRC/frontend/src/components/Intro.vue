<template>
    <div class="intro">
        <h1><strong>ED's DBD</strong></h1>
        <h1>개발 기간</h1>
        <div class="outer">20.09.7 ~ 20.12.06 [90일]</div>
        <div><br></div>
        <hr>
        <h1>개발자 소개</h1>
        <div class="outer">
            <div class="team1">
                <div><strong>TEAM 1</strong></div>
                <div class="centered" v-for="person in team1" :key=person.id>
                    <div>
                        <i>{{person.role}}<br></i>
                        <strong>{{person.id}}</strong> - <i>{{person.name}}</i>
                        <i><br></i>
                    </div>
                </div>
            </div>
            <hr>
            <div class="team2">
                <div><strong>TEAM 2</strong></div>
                <div class="centered" v-for="person in team2" :key=person.id>
                    <div>
                        <i>{{person.role}}<br></i>
                        <strong>{{person.id}}</strong> - <i>{{person.name}}</i>
                        <i><br></i>
                    </div>
                </div>
            </div>
            <hr>
        </div>
        <ul>
            <p>© ED's DBD</p>
        </ul>
    </div>
</template>

<script>
export default {
    data: function() {
        return {
            team1 : [
                {id: '2015147533', name: '유현석', role: '로그인 환경 구성'},
                {id: '2015147561', name: '송낙원', role: '평가자 환경 구성'},
                {id: '2015147565', name: '박성현', role: '제출자 환경 구성'},
            ],
            team2 : [
                {id: '2015147531', name: '서기원', role: '관리자 환경 구성'},
                {id: '2015147550', name: '최희란', role: '회원관리 환경 구성'},
                {id: '2015147562', name: '이의동', role: '데이터베이스 환경 구성'},
            ]
        }
    }
}
</script>