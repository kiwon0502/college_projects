package web.dao;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.util.ArrayList;

import javax.naming.Context;
import javax.naming.InitialContext;
import javax.naming.NamingException;
import javax.sql.DataSource;

import web.util.MyException;
import web.vo.BoardVO;
import web.vo.HouseDeal;

public class BoardDAO {
	DataSource ds;
	
	public BoardDAO() {
		try {
			Context initCtx = new InitialContext();
			Context envCtx = (Context) initCtx.lookup("java:comp/env");
			ds = (DataSource) envCtx.lookup("jdbc/HappyHouseConnectionPool");
		} catch (NamingException e) {
			e.printStackTrace();
		}
	}

	public void articleInsert(BoardVO b) throws MyException {
		try(Connection con=ds.getConnection()) {
			String sql = "insert into board(title, content, writer, reg_datetime) values(?, ?, ?, ?)";
			PreparedStatement stmt = con.prepareStatement(sql);
			stmt.setString(1, b.getTitle());
			stmt.setString(2, b.getContent());
			stmt.setString(3, b.getWriter());
			stmt.setString(4, b.getReg_datetime());
			int i=stmt.executeUpdate();
			System.out.println(i+"행이 insert되었습니다");
		} catch (SQLException e) {
			e.printStackTrace();
			throw new MyException("게시글 등록 실패");
		}
	}

	public ArrayList<BoardVO> searchAll() throws MyException {
		try(Connection con=ds.getConnection()) {
			String sql = "SELECT * FROM board ORDER BY originNo DESC, groupOrd ASC";
			PreparedStatement stmt = con.prepareStatement(sql);
			ResultSet rs=stmt.executeQuery();
			
			ArrayList<BoardVO> list = new ArrayList<>();
			while(rs.next()) {
				BoardVO h=new BoardVO();
				h.setCode(rs.getInt("code"));
				h.setOriginNo(rs.getInt("originNo"));
				h.setGroupOrd(rs.getInt("groupOrd"));
				h.setGroupLayer(rs.getInt("groupLayer"));
				h.setTitle(rs.getString("title"));
				h.setContent(rs.getString("content"));
				h.setWriter(rs.getString("writer"));
				h.setReg_datetime(rs.getString("reg_datetime"));
				list.add(h);
			}
			return list;
			
		} catch (SQLException e) {
			e.printStackTrace();
			throw new MyException("searchAll 실패");
		}
	}
}
