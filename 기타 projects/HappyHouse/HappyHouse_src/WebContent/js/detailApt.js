var map;
$(document).ready(function(){
//	// table의 행을 눌렀을 때 상세 페이지로 이동
//	$("#aptTable").on("click","tbody tr",function(){
//		let row = $("#aptTable").DataTable().row(this).data();
//		localStorage.setItem("detailApt", JSON.stringify(row));
////		$("#detailApt").html("<img src=\""+row.아파트+".jpg\">");
//		location.href="aptDetail.html";
//	});
	const aptInfo = JSON.parse(localStorage.getItem("detailApt"));
	$("#detailApt").html(
			"<div style='font-size:50px'>"+aptInfo.아파트+"</div>"+
			"<img style='width: 30%' src=\"img/"+aptInfo.아파트+".jpg\" onerror=\"this.src='img/baseHouse.jpg'\">"+
			"<div style='font-size:30px'>거래금액: "+aptInfo.거래금액+"</div>"+
			"<div style='font-size:30px'>법정동: "+aptInfo.법정동+"</div>"+
			"<div style='font-size:30px'>전용면적: "+aptInfo.전용면적+"</div>");

	var mapContainer = document.getElementById('map'); //지도를 담을 영역의 DOM 레퍼런스
	var mapOption = { //지도를 생성할 때 필요한 기본 옵션
		center: new kakao.maps.LatLng(33.450701, 126.570667), //지도의 중심좌표.
		level: 3 //지도의 레벨(확대, 축소 정도)
	};

	map = new kakao.maps.Map(mapContainer, mapOption); //지도 생성 및 객체 리턴
	var geocoder = new kakao.maps.services.Geocoder(); 
	
	let name = aptInfo.법정동+" "+aptInfo.지번;

	geocoder.addressSearch(`${name}`, function(result, status) {

    	console.log(status);
        // 정상적으로 검색이 완료됐으면 
         if (status === kakao.maps.services.Status.OK) {

            var coords = new kakao.maps.LatLng(result[0].y, result[0].x);

            // 결과값으로 받은 위치를 마커로 표시합니다
            var marker = new kakao.maps.Marker({
                map: map,
                position: coords
            });

            // 인포윈도우로 장소에 대한 설명을 표시합니다
            var infowindow = new kakao.maps.InfoWindow({
                content: `<div style="width:150px;text-align:center;padding:6px 0;">위치</div>`
            });
            infowindow.open(map, marker);

            // 지도의 중심을 결과값으로 받은 위치로 이동시킵니다
            map.setCenter(coords);
        } 
    });
})
	
