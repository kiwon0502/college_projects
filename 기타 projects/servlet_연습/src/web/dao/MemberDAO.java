package web.dao;

import java.sql.*;

import javax.naming.*;
import javax.sql.DataSource;

import web.util.MyException;
import web.vo.MemberVo;

public class MemberDAO {
	DataSource ds;
	
	public MemberDAO() {
		try {
			Context initCtx = new InitialContext();
			Context envCtx = (Context) initCtx.lookup("java:comp/env");
			ds = (DataSource) envCtx.lookup("jdbc/HappyHouseConnectionPool");
		} catch (NamingException e) {
			e.printStackTrace();
		}
	}

	public void memeberInsert(MemberVo m) throws MyException {
		try(Connection con=ds.getConnection()) {
			String sql = "insert  into member(name, email, pw) values(?, ?, ?)";
			PreparedStatement stmt = con.prepareStatement(sql);
			stmt.setString(1, m.getName());
			stmt.setString(2, m.getEmail());
			stmt.setString(3, m.getPw());
			int i=stmt.executeUpdate();
			System.out.println(i+"행이 insert되었습니다");
		} catch (SQLException e) {
			e.printStackTrace();
			throw new MyException("회원 가입 실패");
		}
	}

	public MemberVo login(MemberVo m) throws MyException {
		try(Connection con=ds.getConnection()) {
			String sql = "select name from member where email=? and pw=?";
			PreparedStatement stmt = con.prepareStatement(sql);
			stmt.setString(1, m.getEmail());
			stmt.setString(2, m.getPw());
			ResultSet rs=stmt.executeQuery();
			
			if (rs.next()) {
				m.setName(rs.getString(1));
				return m;
			}
			
			return null;
			
		} catch (SQLException e) {
			e.printStackTrace();
			throw new MyException("login 실패");
		}
	}
	
	public MemberVo find(MemberVo m) throws MyException {
		try(Connection con=ds.getConnection()) {
			String sql = "select name from member where email=?";
			PreparedStatement stmt = con.prepareStatement(sql);
			stmt.setString(1, m.getEmail());
			ResultSet rs=stmt.executeQuery();
			
			if (rs.next()) {
				m.setName(rs.getString(1));
				return m;
			}
			return null;
			
		} catch (SQLException e) {
			e.printStackTrace();
			throw new MyException("해당 회원 없음");
		}
	}
}
