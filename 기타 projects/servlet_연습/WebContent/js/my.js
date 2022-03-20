$(document).ready(function() {
	
	const id=$.cookie("id");
	const flag=$.cookie("flag");
	if(id) {
		$("#loginSpan").html('${id} <button id="logoutBtn">logout</button>');
	}
	
	if(flag) {
		$.post('main', {sign:"boardList"}, function(data){
			data=JSON.parse(data);
            let tableDiv="<table class='table'><thead><tr><th>#</th><th>Title</th><th>Writer</th><th>Date</th></tr></thead><tbody>";
            data.forEach(function(item,index) {
                tableDiv+=`<tr><td>${item.code}</td><td>${item.title}</td><td>${item.writer}</td><td>${item.reg_datetime}</td></tr>`;
            });
            tableDiv+="</tbody></table>";
            tableDiv+="<br><button type='button' class='btn' data-toggle='modal' data-target='#myModal' style='background-color:gray;color:white'>글쓰기</button>";
            $("#boardDiv").html(tableDiv);
		});
		$.removeCookie("flag");
	}
	
	$(document).on("click", "#logoutBtn", function() {
		$.post('main', {sign:"logout"}, function(data) {
			if(data=="ok") {
				$.removeCookie("id");
				location.reload();
			} else {
				alert("shit");
			}
		});
	});
	
	$("#loginBtn").click(function() {
		const id=$("#id").val();
		const pwd=$("#pwd").val();
		// alert(id+":"+pwd);
		$.post("main",{id, pwd, sign:"login"},function(data) {
			alert(data);
			if (data=="ok") {
				$.cookie("id", id);
				location.reload();
			}
		});
	});
	
	$("#memeberInsertBtn").click(function() {
		const name=$("#name").val();
		const email=$("#email").val();
		const pw=$("#pw").val();
		$.post("main",{name, email, pw, sign:"memberInsert"},function(data) {
			alert(data);
		});
	});
	
	$("#HouseDealSearchBtn").click(function() {
        $.post('main',{sign:"HouseDealSearch"},function(data){
            //console.log(data);
            data=JSON.parse(data);
            //console.log(data);
            let tableDiv="<table class='table'><thead><tr><th>#</th><th>dong</th><th>APT name</th><th>거래가</th></tr></thead><tbody>";
            data.forEach(function(item,index) {
                tableDiv+=`<tr><td>${item.no}</td><td>${item.dong}</td><td>${item.aptName}</td><td>${item.dealAmount}</td></tr>`;
            });
            tableDiv+="</tbody></table>";
            tableDiv+="<br><input placeholder='동'><input placeholder='아파트명'><button>search</button><br>";
            $("#contentDiv").html(tableDiv);
        });
    });
	
	$("#boardClick").click(function() {
		$.post('main', {sign:"boardList"}, function(data){
			data=JSON.parse(data);
            //console.log(data);
            let tableDiv="<table class='table'><thead><tr><th>#</th><th>Title</th><th>Writer</th><th>Date</th></tr></thead><tbody>";
            data.forEach(function(item,index) {
                tableDiv+=`<tr><td>${item.code}</td><td>${item.title}</td><td>${item.writer}</td><td>${item.reg_datetime}</td></tr>`;
            });
            tableDiv+="</tbody></table>";
            tableDiv+="<br><button type='button' class='btn' data-toggle='modal' data-target='#myModal' style='background-color:gray;color:white'>글쓰기</button>";
            $("#boardDiv").html(tableDiv);
		});
	});
	
	$(document).on("click", "#articleInsert", function() {
		let title = $("#articleTitle").val();
		let content = $("#articleContent").val();
		let email = $.cookie("id");
		
		if (!email) {
			alert("로그인 이후 이용해주세요!!");
			location.reload();
			return;
		} else if (!title || !content) {
			alert("빈칸을 채워주세요");
			return;
		}
		
		$.post('main', {email, title, content, sign:"articleInsert"}, function(data) {
			alert(data);
			$("#myModal").modal("toggle");
			$.cookie("flag", "insertDone");
			location.reload();
		});
	});
	
});



