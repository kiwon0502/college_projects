function changeSelect1(){  
	const e =document.getElementById("dosi");		
	const selectValue = e.options[e.selectedIndex].value;  
	
	$.get("https://grpc-proxy-server-mkvo6j4wsq-du.a.run.app/v1/regcodes?regcode_pattern=*00000000"
			,function(data){						
				$.each(data.regcodes,function(index,item){
					if(item.name==selectValue){								
						let code=(item.code+"").slice(0,2)
						$.get("https://grpc-proxy-server-mkvo6j4wsq-du.a.run.app/v1/regcodes?regcode_pattern="+code+"*000000",function(data2){
							//console.log(data2);
							localStorage.setItem("siguArr", JSON.stringify(data2));
							let sigu=""
							$.each(data2.regcodes,function(index2,item2){
								if(index2!=0){
								 sigu+="<option>"+item2.name+"</option>";
								}
							});
							$("#sigu").html(sigu);
						});
					}
				});
	});
} 

function search() {
	var ServiceKey = 'Yi8vcEjKxlnBpzM9f8jsNdN0TW3jwL/rh3DLtaf21ZVky4KUct/aFrGCTYuG19OBbLJnNs+ici+pzQMZ4fD2Og==';
    var LAWD_CD = '11110'; // 지역 코드
    var DEAL_YMD = '202012'; // 거래년월일
    let contractDate = $("#contractDate").val();
    if (contractDate) {
    	DEAL_YMD = contractDate;
    }
    
    // 시/구 항목에서 골랐던 값을 가져와서 그 지역의 지역코드를 넣어준다.
    const e = document.getElementById("sigu");
    const selectValue = e.options[e.selectedIndex].value;
    
	let siguArr=localStorage.getItem("siguArr");
	siguArr=JSON.parse(siguArr);
	
	$.each(siguArr.regcodes,function(index,item){
		if(item.name==selectValue){
			LAWD_CD=(item.code+"").slice(0,5);
		}
	});			
    // server에서 넘어온 data
	$.ajax({
		type:"GET",
		url:'http://openapi.molit.go.kr/OpenAPI_ToolInstallPackage/service/rest/RTMSOBJSvc/getRTMSDataSvcAptTradeDev',
		data:{"ServiceKey": ServiceKey,
			"numOfRows" : '100',
			"LAWD_CD": LAWD_CD,
			"DEAL_YMD": DEAL_YMD},
		dataType:"json",
		success: function(data) {
			let dt = data.response.body.items.item;
			console.log(dt);
			$("#aptTable").DataTable().destroy();
			$("#aptTable").DataTable({
        		data : dt,
        		searching: false,
        		columns: [
        			{data : "아파트"},
        			{data : "거래금액"},
        			{data : "법정동"},
        			{data : "건축년도"},
        			{data : "전용면적"},
        			{data : "지역코드"}
        		]
        	});
		}
	});
}

function noticeSearch() {
	let date = $("#noticeDate").val();
	let title = $("#noticeTitle").val();
	let author = $("#noticeAuthor").val();
	const query = {date, title, author, sign:"noticeSearch"};
	$.post("main", query,
			function(data) {
				const js = JSON.parse(data);
				$("#noticeTable").DataTable().destroy();
				$("#noticeTable").DataTable({
	        		data : js,
	        		searching: false,
	        		columns: [
	        			{data : "등록번호"},
	        			{data : "제목"},
	        			{data : "작성자"},
	        			{data : "작성일"},
	        			{data : "조회수"}
	        		]
	        	});
			});
}

function register() {
	let fN = $("#FirstName").val();
	let lN = $("#LastName").val();
	let emailAddr = $("#InputEmail").val();
	let pwd = $("#InputPassword").val();
	let rpwd = $("#RepeatPassword").val();
	
	if (!fN || !lN || !emailAddr || !pwd || !rpwd) {
	    alert("빈칸이 없도록 입력해주세요.");
	    return;
	}
	if (pwd != rpwd) {
	    alert("똑같은 비밀번호를 입력해주세요.");
	    return;
	}
	
	const user = {fN, lN, emailAddr, pwd, sign:"register"};
	$.post("main", user,
			function(data) {
				console.log(data);
				const status = JSON.parse(data).status;
				if (status == "success") {
					alert("회원가입 성공!");
					$(location).attr("href", "login.html");
				} else if (status == "fail"){
					alert("회원가입에 실패하였습니다.");
				}
			});
}

function login() {
	let emailAddr = $("#InputEmail").val();
	let pwd = $("#InputPassword").val();
	
	if (!emailAddr || !pwd) {
	    alert("빈칸이 없도록 입력해주세요.");
	    return;
	}
	
	$.post("main", {emailAddr, pwd, sign:"login"},
			function(data) {
				const info = JSON.parse(data);
				if (info.status == "success") {
					$.cookie("recentUser", JSON.stringify(info));
					
					alert("로그인 성공!");
					$(location).attr("href", "index.html");
				} else if (info.status == "not_member"){
					alert("존재하지 않는 회원입니다.");
				} else if (info.status == "wrong_pwd") {
					alert("비밀번호가 틀렸습니다.");
				}
			});
}

function logout() {	
	$.post("main", {sign:"logout"},
			function(data) {
				const status = JSON.parse(data).status;
				if (status == "success") {
					alert("로그아웃 성공!");
					$.removeCookie("recentUser");
					$(location).attr("href", "login.html");
					
				} else {
					alert("다시 시도해주세요.");
				}
			});
}

function profileChange() {
	let fN = $("#profileFN").val();
	let lN = $("#profileLN").val();
	let emailAddr = $("#profileEmail").attr("placeholder");
	let pwd = $("#profilePWD").val();
	let rpwd = $("#profileRPWD").val();
	
	if (!fN) fN = $("#profileFN").attr("placeholder");
	if (!lN) lN = $("#profileLN").attr("placeholder");
	
	if (!fN || !lN || !emailAddr || !pwd || !rpwd) {
	    alert("빈칸이 없도록 입력해주세요.");
	    return;
	}
	if (pwd != rpwd) {
	    alert("똑같은 비밀번호를 입력해주세요.");
	    return;
	}

	const user = {fN, lN, emailAddr, pwd, sign:"change"};
	$.post("main", user,
			function(data) {
				const info = JSON.parse(data);
				if (info.status == "success") {
					$.removeCookie("recentUser");
					$.cookie("recentUser", JSON.stringify(info));
					alert("성공적으로 변경되었습니다");
					$(location).attr("href", "index.html");
				} else if (info.status == "fail"){
					alert("무언가 잘못됨 ㅋ");
				}
			});
}

function quit() {
	$.post("main", {sign:"quit"},
			function(data) {
				const status = JSON.parse(data).status;
				if (status == "success") {
					$.removeCookie("recentUser");
					alert("회원탈퇴 성공!");
					$(location).attr("href", "login.html");
				} else {
					alert("다시 시도해주세요.");
				}
			});
}

function resetPwd() {
	let emailAddr = $("#forgotEmail").val();
	$.post("main", {emailAddr, sign:"reset"},
			function(data) {
				const status = JSON.parse(data).status;
				console.log(data);
				if (status == "success") {
					alert("너도 아는 그 비밀번호로 변경됨ㅋ");
					$(location).attr("href", "login.html");
				} else {
					alert("존재하지 않는 회원입니다.");
				}
			});
}

function toInfo(flag) {
	const userinfo = $.cookie("recentUser");
	if (userinfo) {
		if (flag) {
			$(location).attr("href", "profileInfo.html");
		} else {
			$(location).attr("href", "profileChange.html");
		}
	} else {
		alert("로그인 이후 이용해주십시오.");
	}
}

function addNotice() {
	let title = $("#noticeTitle").val();
	let author = $("#noticeAuthor").text();
	let date = $("#noticeDate").text();
	let content = $("#noticeContent").val();
	if (!title || !author || !date || !content) {
	    alert("빈칸이 없도록 입력해주세요.");
	    return;
	}
	
	$.post("main", {title, author, date, content, sign:"noticeAdd"},
			function(data) {
				const info = JSON.parse(data);
				if (info.status == "success") {
					alert("성공적으로 추가되었습니다");
				} else if (info.status == "fail"){
					alert("무언가 잘못됨 ㅋ");
				}
			});
	$(location).attr("href", "notice.html");
}


$(document).ready(function() {
	// 페이지 초기 설정
	// 관리자 계정 설정 및 공지사항 한개 등록
	$.get("main", {sign:"init"}, function(data) {
		// DB로 연결했다면 필요 없는 작업
	})
	
	// 로그인 상황 관리
	const userinfo = $.cookie("recentUser");
	if(userinfo) {
		const info = JSON.parse(userinfo);
		let user = info.fN + " " + info.lN;
		$("#loginSpan").html("<a class=\"nav-link dropdown-toggle\" href=\"#\" id=\"userDropdown\"" +
				"role=\"button\"data-toggle=\"dropdown\" aria-haspopup=\"true\" aria-expanded=\"false\">" +
				"<span class=\"mr-2 d-none d-lg-inline text-gray-600 small\">" + user + "</span>" +
				"<img class=\"img-profile rounded-circle\" src=\"img/undraw_profile.svg\"></a>" +
				"<div class=\"dropdown-menu dropdown-menu-right shadow animated--grow-in\" aria-labelledby= \"userDropdown\">" +
				"<a class=\"dropdown-item\" href=\"profileInfo.html\"><i class=\"fas fa-user fa-sm fa-fw mr-2 text-gray-400\"></i>Profile</a>" +
                "<a class=\"dropdown-item\" href=\"#\"><i class=\"fas fa-cogs fa-sm fa-fw mr-2 text-gray-400\"></i>Settings</a>" +
                "<a class=\"dropdown-item\" href=\"#\"><i class=\"fas fa-list fa-sm fa-fw mr-2 text-gray-400\"></i>Activity Log</a>" +
                "<div class=\"dropdown-divider\"></div>" +
                "<a class=\"dropdown-item\" href=\"#\" data-toggle=\"modal\" data-target=\"#logoutModal\" onclick=\"logout()\">" +
                "<i class=\"fas fa-sign-out-alt fa-sm fa-fw mr-2 text-gray-400\"></i>Logout</a></div>");
		
		$("#profileEmail").attr("placeholder", info.email);
		$("#profileFN").attr("placeholder", info.fN);
		$("#profileLN").attr("placeholder", info.lN);
	}
});






