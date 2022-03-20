package web.vo;

import web.util.MyException;

public class MemberVo {
	private String name, email, pw;

	public MemberVo() {
		super();
		// TODO Auto-generated constructor stub
	}
	
	public MemberVo(String email) throws MyException {
		super();
		setEmail(email);
	}
	
	public MemberVo(String email, String pw) throws MyException {
		super();
		setEmail(email);
		setPw(pw);
	}

	public MemberVo(String name, String email, String pw) throws MyException {
		super();
		setName(name);
		setEmail(email);
		setPw(pw);
	}

	public String getName() {
		return name;
	}

	public void setName(String name) throws MyException {
		if(name!=null && !name.equals("")) this.name = name;
		else throw new MyException("name이 필요합니다");
	}

	public String getEmail() {
		return email;
	}

	public void setEmail(String email) throws MyException {
		if(email!=null && !email.equals("")) this.email = email;
		else throw new MyException("email이 필요합니다");
	}

	public String getPw() {
		return pw;
	}

	public void setPw(String pw) throws MyException {
		if(pw!=null && !pw.equals("")) this.pw = pw;
		else throw new MyException("pw가 필요합니다");
	}
	
	@Override
	public String toString() {
		return "MemberVo [name=" + name + ", email=" + email + ", pw=" + pw + "]";
	}
	
}
