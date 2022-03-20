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
import web.vo.HouseDeal;
import web.vo.MemberVo;

public class HouseDealDAO {
	DataSource ds;
	
	public HouseDealDAO() {
		try {
			Context initCtx = new InitialContext();
			Context envCtx = (Context) initCtx.lookup("java:comp/env");
			ds = (DataSource) envCtx.lookup("jdbc/HappyHouseConnectionPool");
		} catch (NamingException e) {
			e.printStackTrace();
		}
	}

	/*public void memeberInsert(MemberVo m) throws MyException {
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
	}*/

	public ArrayList<HouseDeal> searchAll() throws MyException {
		try(Connection con=ds.getConnection()) {
			String sql = "select * from HouseDeal limit 5";
			PreparedStatement stmt = con.prepareStatement(sql);
			ResultSet rs=stmt.executeQuery();
			
			ArrayList<HouseDeal> list = new ArrayList<>();
			while(rs.next()) {
				HouseDeal h=new HouseDeal();
				h.setNo(rs.getInt("no"));
				h.setDong(rs.getString("dong"));
				h.setAptName(rs.getString("aptName"));
				h.setDealAmount(rs.getString("dealAmount"));
				list.add(h);
			}
			
			return list;
			
		} catch (SQLException e) {
			e.printStackTrace();
			throw new MyException("searchAll 실패");
		}
	}
}
