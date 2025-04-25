import java.io.Serializable;

public class Message implements Serializable {
    private static final long serialVersionUID = 4395563451540715277L;
    
	private MessageType type;
	private MessageStatus status;
	private String text;

    public Message() {
        this.type = MessageType.UNDEFINED;
        this.status = MessageStatus.UNDEFINED;
        this.text = "";
    }

    public Message(MessageType type, MessageStatus status, String text) {
    	this.type = type;
        this.status = status;
        this.text = text;
    }

	public void setStatus(MessageStatus status) {
        this.status = status;
    }

	public void setText(String text) {
        this.text = text;
    }

    public MessageType getType() {
        return this.type;
    }

    public MessageStatus getStatus() {
        return this.status;
    }

    public String getText() {
        return this.text;
    }

}
