package web.controller;

import java.io.IOException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;


public class MainServlet extends HttpServlet {
	
	private static final HashMap<String, Account> members = new HashMap<>();
	private static final ArrayList<Notice> notices = new ArrayList<>();
	private static final String resetCode = "1q2w3e4r!";
	private static int init_val = 0;

	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		request.setCharacterEncoding("utf-8");
		response.setContentType("text/html;charset=utf-8");
		PrintWriter out = response.getWriter();
		String sign = request.getParameter("sign");
		if (sign.equals("init") && init_val == 0) {
			members.put("admin", new Account("admin", "My", "admin", "admin"));
			notices.add(new Notice(1, "반갑습니다.", "admin My", "2022-03-11", "HappyHouse에 오신 것을 환영합니다. 잘 즐겨주십시오."));
			init_val++;
		}
	}

	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		request.setCharacterEncoding("utf-8");
		response.setContentType("text/html;charset=utf-8");
		PrintWriter out = response.getWriter();
		String sign = request.getParameter("sign");
		
		if (sign != null) {
			if (sign.equals("register")) {
				String fN = request.getParameter("fN");
				String lN = request.getParameter("lN");
				String email = request.getParameter("emailAddr");
				String pwd = request.getParameter("pwd");
				
				if(!members.containsKey(email)) {
					members.put(email, new Account(fN, lN, email, pwd));
					out.print("{\"status\":\"success\"}");
				} else {
					out.print("{\"status\":\"fail\"}");
				}
				
			} else if (sign.equals("login")) {
				String email = request.getParameter("emailAddr");
				String pwd = request.getParameter("pwd");
				
				if(!members.containsKey(email)) {
					out.print("{\"status\":\"not_member\"}");
				}else {
					Account member = members.get(email);
					if(member.pwd.equals(pwd)) {
						HttpSession session = request.getSession();
						session.setAttribute("email", email);
						out.print("{\"status\":\"success\","
								+ "\"fN\":\"" + member.firstName + "\","
								+ "\"lN\":\"" + member.lastName + "\","
								+ "\"email\":\"" + member.emailAddr + "\","
								+ "\"pwd\":\"" + member.pwd + "\"}");
					}else {
						out.print("{\"status\":\"wrong_pwd\"}");
					}
				}
				
			} else if (sign.equals("logout")) {
				HttpSession session = request.getSession();
				session.invalidate();
				out.print("{\"status\":\"success\"}");
				
			} else if (sign.equals("change")) {
				String fN = request.getParameter("fN");
				String lN = request.getParameter("lN");
				String email = request.getParameter("emailAddr");
				String pwd = request.getParameter("pwd");
				
				Account member = members.get(email);
				member.firstName = fN;
				member.lastName = lN;
				member.pwd = pwd;
				out.print("{\"status\":\"success\","
						+ "\"fN\":\"" + member.firstName + "\","
						+ "\"lN\":\"" + member.lastName + "\","
						+ "\"email\":\"" + member.emailAddr + "\","
						+ "\"pwd\":\"" + member.pwd + "\"}"); // 쿠기 수정해야함
				
			} else if (sign.equals("quit")) {
				HttpSession session = request.getSession();
				String email = (String) session.getAttribute("email");
				members.remove(email);
				out.print("{\"status\":\"success\"}"); // 사실 remove 됬는지 확인해줘야함 ㅈㅅ
				
			} else if (sign.equals("reset")) {
				String email = request.getParameter("emailAddr");
				if(members.containsKey(email)) {
					Account member = members.get(email);
					member.pwd = resetCode;
					out.print("{\"status\":\"success\"}");
				} else {
					out.print("{\"status\":\"fail\"}");
				}
				
			} else if (sign.equals("noticeSearch")) {
				String date = request.getParameter("date");
				String title = request.getParameter("title");
				String author = request.getParameter("author");
				StringBuilder jsB = new StringBuilder("[");
				boolean hasContent = false;
				
				for (Notice notice : notices) {
					if (!date.equals("") && !notice.date.equals(date)) continue;
					if (!title.equals("") && !notice.title.equals(title)) continue;
					if (!author.equals("") && !notice.author.equals(author)) continue;
					hasContent = true;
					jsB.append("{\"등록번호\":\"").append(notice.num).append("\",")
					.append("\"제목\":\"").append(notice.title).append("\",")
					.append("\"작성자\":\"").append(notice.author).append("\",")
					.append("\"작성일\":\"").append(notice.date).append("\",")
					.append("\"조회수\":\"").append(notice.hits).append("\"},");
				}
				jsB.append("]");
				if(hasContent) jsB.deleteCharAt(jsB.lastIndexOf(","));
				else jsB = new StringBuilder("[]");
				out.print(jsB.toString());
				
			} else if (sign.equals("noticeAdd")) {
				String date = request.getParameter("date");
				String title = request.getParameter("title");
				String author = request.getParameter("author");
				String content = request.getParameter("content");
				int num = notices.size()+1;
				notices.add(new Notice(num, title, author, date, content));
				if (notices.size() == num) {
					out.print("{\"status\":\"success\"}");
				} else {
					out.print("{\"status\":\"fail\"}");
				}
				
			} else if (sign.equals("noticeDetail")) {
				int num = Integer.parseInt(request.getParameter("noticeNum"));
				if (notices.size() < num) {
					out.print("{\"status\":\"fail\"}");
				} else {
					Notice n = notices.get(num-1);
					n.hits++;
					
					StringBuilder jsB = new StringBuilder("{\"status\":\"success\",");
					jsB.append("\"등록번호\":\"").append(n.num).append("\",")
					.append("\"제목\":\"").append(n.title).append("\",")
					.append("\"작성자\":\"").append(n.author).append("\",")
					.append("\"작성일\":\"").append(n.date).append("\",")
					.append("\"작성내용\":\"").append(n.content).append("\",")
					.append("\"조회수\":\"").append(n.hits).append("\"}");
					
					out.print(jsB.toString());
				}
				
			} else if (sign.equals("noticeModify")) {
				int num = Integer.parseInt(request.getParameter("noticeNum"));
				String title = request.getParameter("title");
				String content = request.getParameter("content");
				
				if (notices.size() < num) {
					out.print("{\"status\":\"fail\"}");
				} else {
					Notice n = notices.get(num-1);
					if (!title.equals("")) n.title = title;
					if (!content.equals("")) n.content = content;
					out.print("{\"status\":\"success\"}");
				}
				
			} else if (sign.equals("noticeDelete")) {
				int num = Integer.parseInt(request.getParameter("noticeNum"));
				if (notices.size() < num) {
					out.print("{\"status\":\"fail\"}");
				} else {
					notices.remove(num-1);
					for (int idx = num-1; idx < notices.size(); idx++) {
						notices.get(idx).num -= 1;
					}
					out.print("{\"status\":\"success\"}");
				}
				
			}	
			
		} else {
			out.print("비상~!!! " + request.getRemoteAddr());
		}
	}

}

class Account {
	String firstName;
	String lastName;
	String emailAddr;
	String pwd;
	public Account(String fN, String lN, String email, String pwd) {
		this.firstName = fN;
		this.lastName = lN;
		this.emailAddr = email;
		this.pwd = pwd;
	}
	
	// getter setter는 시간관계상 생략합니다 ㅎㅎ
	// 귀엽게 봐주세요~
}

class Notice {
	int num;
	String title;
	String author;
	String date;
	String content;
	int hits;
	public Notice(int num, String title, String author, String date, String content) {
		this.num = num;
		this.title = title;
		this.author = author;
		this.date = date;
		this.content = content;
		this.hits = 0;
	}
}


