$(document).ready(function() {
	const noticeInfo = JSON.parse(localStorage.getItem("noticeInfo"));
	const userinfo = $.cookie("recentUser");
	let noticeNum = noticeInfo.등록번호;
	
	$.post("main", {noticeNum, sign:"noticeDetail"},
			function(data) {
				const dt = JSON.parse(data);
				if (dt.status == "success") {
					$("#noticeTitle").text(dt.제목);
					$("#noticeAuthor").text(dt.작성자);
					$("#noticeDate").text(dt.작성일);
					$("#noticeContent").text(dt.작성내용);
					
					if(userinfo) {
						const info = JSON.parse(userinfo);
						let user = info.fN + " " + info.lN;
						if (noticeInfo.작성자 == user) {
							// 수정 화면으로 바꾸기
							$("#modifyTitle").html("<input id=\"noticeTitle\" type=\"text\" placeholder=\""+dt.제목+"\"style=\"border:none;width:700px;text-align:center\">");
							$("#modifyContent").html("<input id=\"noticeContent\" type=\"text\" placeholder=\""+dt.작성내용+"\"style=\"border:none;width:700px;height:600px;text-align:center\">");
						}
					}
				} else {
					alert("무언가 잘못됨ㅋ");
					$(location).attr("href", "notice.html");
				}
			});
});

function noticeModify() {
	const noticeInfo = JSON.parse(localStorage.getItem("noticeInfo"));
	let noticeNum = noticeInfo.등록번호;
	let title = $("#noticeTitle").val();
	let content = $("#noticeContent").val();
	console.log(title);
	console.log(content);
	
	if (!title && !content) {
		alert("수정한 사항이 없습니다.");
		return;
	}
	
	$.post("main", {noticeNum, title, content, sign:"noticeModify"},
			function(data) {
				const dt = JSON.parse(data);
				if (dt.status == "success") {
					alert("성공적으로 수정되었습니다.");
					$(location).attr("href", "notice.html");
				} else {
					alert("무언가 잘못됨ㅋ");
					$(location).attr("href", "notice.html");
				}
			});
}

function noticeDelete() {
	const noticeInfo = JSON.parse(localStorage.getItem("noticeInfo"));
	let noticeNum = noticeInfo.등록번호;
	
	$.post("main", {noticeNum, sign:"noticeDelete"},
			function(data) {
				const dt = JSON.parse(data);
				if (dt.status == "success") {
					alert("성공적으로 삭제되었습니다.");
					$(location).attr("href", "notice.html");
				} else {
					alert("무언가 잘못됨ㅋ");
					$(location).attr("href", "notice.html");
				}
			});
}









