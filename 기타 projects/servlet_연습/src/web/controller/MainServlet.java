package web.controller;

import java.io.IOException;
import java.io.PrintWriter;
import java.time.LocalDateTime;
import java.util.ArrayList;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServlet;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.json.JSONArray;
import org.json.JSONObject;

import web.dao.BoardDAO;
import web.dao.HouseDealDAO;
import web.dao.MemberDAO;
import web.util.MyException;
import web.vo.BoardVO;
import web.vo.HouseDeal;
import web.vo.MemberVo;

public class MainServlet extends HttpServlet {
	
	MemberDAO memberDAO;
	HouseDealDAO houseDealDAO;
	BoardDAO boardDAO;

	@Override
	public void init() throws ServletException {
		memberDAO = new MemberDAO();
		houseDealDAO = new HouseDealDAO();
		boardDAO = new BoardDAO();
	}

	protected void doGet(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		
	}

	protected void doPost(HttpServletRequest request, HttpServletResponse response) throws ServletException, IOException {
		// 들어오는 데이터의 한글 처리
		request.setCharacterEncoding("utf-8");
		response.setContentType("text/html;charset=utf-8");
		PrintWriter out = response.getWriter();
		
		String sign=request.getParameter("sign");
		if(sign!=null) {
			if(sign.equals("memberInsert")) { // 회원 가입
				String name=request.getParameter("name");
				String email=request.getParameter("email");
				String pw=request.getParameter("pw");
				try {
					MemberVo m = new MemberVo(name, email, pw);
					System.out.println(m);
					memberDAO.memeberInsert(m);
					out.append("ok");
					
				} catch (MyException e) {
					out.append("fail");
					e.printStackTrace();
				}
				
			} else if(sign.equals("login")) { // 로그인
				String id=request.getParameter("id");
				String pwd=request.getParameter("pwd");
				
				try {
					MemberVo m = new MemberVo(id, pwd);
					m = memberDAO.login(m);
					if (m!=null) {
						HttpSession session = request.getSession();
						session.setAttribute("login_user", m);
						
						out.append("ok");
					} else {
						out.append("fail");
					}
				} catch (MyException e) {
					out.append(e.getMessage());
					e.printStackTrace();
				}
			} else if(sign.equals("logout")) { // 로그 아웃
				HttpSession session = request.getSession(false);
				if(session!=null) {
					session.invalidate();
					out.append("ok");
				}
				
			} else if(sign.equals("HouseDealSearch")) { // 주택 거래 조회
				try {
					ArrayList<HouseDeal> list=houseDealDAO.searchAll();
					JSONArray arr = new JSONArray();
					for (HouseDeal h : list) {
						JSONObject jo=new JSONObject();
						jo.put("no",h.getNo());
						jo.put("dong", h.getDong());
						jo.put("aptName", h.getAptName());
						jo.put("dealAmount", h.getDealAmount());
						arr.put(jo);
					}
					out.append(arr.toString());
					
				} catch (MyException e) {
					out.append(e.getMessage());
					e.printStackTrace();
				}
				
				
			} else if(sign.equals("boardList")) { // 게시판 조회
				try {
					ArrayList<BoardVO> list=boardDAO.searchAll();
					JSONArray arr = new JSONArray();
					for (BoardVO h : list) {
						JSONObject jo=new JSONObject();
						jo.put("code",h.getCode());
						jo.put("title", h.getTitle());
						jo.put("writer", h.getWriter());
						jo.put("reg_datetime", h.getReg_datetime());
						arr.put(jo);
					}
					out.append(arr.toString());
					
				} catch (MyException e) {
					out.append(e.getMessage());
					e.printStackTrace();
				}
				
			} else if(sign.equals("articleInsert")) { // 게시글 등록
				String title=request.getParameter("title");
				String content=request.getParameter("content");
				String email=request.getParameter("email");
				String now=LocalDateTime.now().toString();
				String dTime = now.substring(0, now.indexOf('T')) + " " + now.substring(now.indexOf('T')+1);
				
				System.out.println(email);
				System.out.println(title);
				System.out.println(content);
				System.out.println(dTime);
				try {
					MemberVo m = new MemberVo(email);
					m = memberDAO.find(m);
					String writer=m.getName();

					BoardVO b = new BoardVO(title, content, writer, dTime);
					boardDAO.articleInsert(b);
					out.append("ok");
					
				} catch (MyException e) {
					out.append(e.getMessage());
					e.printStackTrace();
				}
			}
			
		} else {
			
		}
	}

}
