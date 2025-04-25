import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.io.StreamCorruptedException;
import java.net.ServerSocket;
import java.net.Socket;

public class Server {
	public static void main(String[] args) throws IOException{
		int port = 8080;
		
		try (ServerSocket serverSocket = new ServerSocket(port)) {
		    System.out.println("Server is listening on port " + port);
		
		    while(true) {
				Socket socket = serverSocket.accept(); // Waits for a client to connect
				
				System.out.println("New client connected");
				Thread ct = new Thread(new ClientThread(socket));
				ct.start();
		    }
		}
	}
	

}

class ClientThread implements Runnable {
	private Socket socket;
	
	// NOTE one message obj at a time
	private ObjectInputStream ois;
	private ObjectOutputStream oos;
	
	public ClientThread(Socket socket) throws IOException, 
	StreamCorruptedException, 
	SecurityException {
		this.socket = socket;
		this.oos = new ObjectOutputStream(this.socket.getOutputStream());
		this.ois = new ObjectInputStream(this.socket.getInputStream());
	}
	
	public void run() {
		try {
			// look for login message
			Message m = (Message) ois.readObject();
			if(!m.getType().equals("login")) {
				throw new Exception("Expected login, found: " + m.getType());
			}
			
			// send login success message
			m.setStatus("success");
			oos.writeObject(m);
			
			// start handling text and logouts
			handleConnection();
			
		} catch (Exception e) {
			System.out.println(e.toString());
		}
	}
	
	private void handleConnection() throws Exception {
		while(true) {
			Message m = (Message) this.ois.readObject();
			
			if(m.getType().equals("text")) {
				// capitalize and send back
				// no status change
				m.setText(m.getText().toUpperCase());
				oos.writeObject(m);
			} else if(m.getType().equals("logout")) {
				// send message back with "success"
				// terminate connection
				m.setStatus("success");
				oos.writeObject(m);
				break;
			} else {
				throw new Exception("handleConnection invalid type: " + m.getType());
			}
		}
	}
}