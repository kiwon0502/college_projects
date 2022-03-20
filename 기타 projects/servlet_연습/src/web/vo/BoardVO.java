package web.vo;

public class BoardVO {

	public BoardVO() {
		super();
	}
	
	public BoardVO(String title, String content, String writer, String reg_datetime) {
		super();
		this.setTitle(title);
		this.setContent(content);
		this.setWriter(writer);
		this.setReg_datetime(reg_datetime);
	}
	
	public BoardVO(int code, String title, String content, String writer, String reg_datetime, int originNo,
			int groupOrd, int groupLayer) {
		super();
		this.code = code;
		this.title = title;
		this.content = content;
		this.writer = writer;
		this.reg_datetime = reg_datetime;
		this.originNo = originNo;
		this.groupOrd = groupOrd;
		this.groupLayer = groupLayer;
	}
	
	/** 글 번호 **/
    private int code;
    
    /** 글 제목 **/
    private String title = "";
    
    /** 글 내용 **/
    private String content = "";
    
    /** 작성자 **/
    private String writer = "";
    
    /** 등록시간 **/
    private String reg_datetime = "";
    
    /*
     * 계층형 게시판을 위한 추가 필드
     * originNo, groupOrd, groupLayer 
     */
    
    /** 원글 번호 **/
    private int originNo;
    
    /** 원글(답글포함)에 대한 순서 **/
    private int groupOrd;
 
    /** 답글 계층 **/
    private int groupLayer;

	public int getCode() {
		return code;
	}

	public void setCode(int code) {
		this.code = code;
	}

	public String getTitle() {
		return title;
	}

	public void setTitle(String title) {
		this.title = title;
	}

	public String getContent() {
		return content;
	}

	public void setContent(String content) {
		this.content = content;
	}

	public String getWriter() {
		return writer;
	}

	public void setWriter(String writer) {
		this.writer = writer;
	}

	public String getReg_datetime() {
		return reg_datetime;
	}

	public void setReg_datetime(String reg_datetime) {
		this.reg_datetime = reg_datetime;
	}

	public int getOriginNo() {
		return originNo;
	}

	public void setOriginNo(int originNo) {
		this.originNo = originNo;
	}

	public int getGroupOrd() {
		return groupOrd;
	}

	public void setGroupOrd(int groupOrd) {
		this.groupOrd = groupOrd;
	}

	public int getGroupLayer() {
		return groupLayer;
	}

	public void setGroupLayer(int groupLayer) {
		this.groupLayer = groupLayer;
	}
	
}
