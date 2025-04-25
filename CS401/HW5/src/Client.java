import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.Scanner;

public class Client {
	public static void main(String[] args) throws Exception {
		try (// get user input
		Scanner sc = new Scanner(System.in)) {
			System.out.print("Enter the host address to connect to: ");
			String host = sc.next();
			
			System.out.print("Enter the port number to connect to: ");
			int port = sc.nextInt();
			
			try (// Connect to the ServerSocket at host:port
			Socket socket = new Socket(host, port)) {
				System.out.println("Connected to " + host + ":" + port);
				
				// init obj streams for socket
				ObjectOutputStream oos = new ObjectOutputStream(socket.getOutputStream());
				ObjectInputStream ois = new ObjectInputStream(socket.getInputStream());
				
				// On connection, pass a ‘login message’ to the server.
				oos.writeObject(new Message(
						MessageType.LOGIN, 
						MessageStatus.UNDEFINED, 
						""));
				
				Message loginReply = (Message) ois.readObject();
				if(loginReply.getStatus() != MessageStatus.SUCCESS) {
					throw new Exception("Client login, found: " + loginReply.getStatus());
				}
				System.out.println("Logged in.");
				
				while(true) {
					System.out.print("Enter message: ");
					String input = sc.next();
					
					if(input.equals("logout")) {
						// send logout message
						oos.writeObject(new Message(
								MessageType.LOGOUT, 
								MessageStatus.UNDEFINED, 
								""));
						Message logoutReply = (Message) ois.readObject();
						if(logoutReply.getStatus() != MessageStatus.SUCCESS) {
							throw new Exception("Client logout, found: " + logoutReply.getStatus());
						}
						
						break;
					}
					
					oos.writeObject(new Message(
							MessageType.TEXT, 
							MessageStatus.UNDEFINED, 
							input));
					Message textReply = (Message) ois.readObject();
					System.out.println(textReply.getText());
				}
				
				System.out.println("Logged out.");
			}
		}
		
	}
}
