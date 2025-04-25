import java.io.Serializable;

public class Message implements Serializable {
    private static final long serialVersionUID = 4395563451540715277L;
    
	private String type;
	private String status;
	private String text;

    public Message() {
        this.type = "undefined";
        this.status = "undefined";
        this.text = "undefined";
    }

    public Message(String type, String status, String text) {
    	if(type.equals("login") || type.equals("logout") || type.equals("text")) {
            this.type = type;
        } else {
        	this.type = "undefined";
        }
    	
        this.status = status;
        this.text = text;
    }

	public void setStatus(String status) {
        status.toLowerCase();
        this.status = status;
    }

	public void setText(String text) {
        this.text = text;
    }

    public String getType() {
        return this.type;
    }

    public String getStatus() {
        return this.status;
    }

    public String getText() {
        return this.text;
    }

}
