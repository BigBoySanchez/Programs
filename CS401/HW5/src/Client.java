import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.Socket;
import java.util.Scanner;

public class Client {
	public static void main(String[] args) throws Exception {
		try (// get user input
		Scanner sc = new Scanner(System.in)) {
			System.out.print("Enter the host address to connect to: ");
			String host = "localhost"; // TODO
			
			System.out.print("Enter the port number to connect to: ");
			int port = 8080; // TODO
			
			try (// Connect to the ServerSocket at host:port
			Socket socket = new Socket(host, port)) {
				System.out.println("Connected to " + host + ":" + port);
				
				// init obj streams for socket
				ObjectOutputStream oos = new ObjectOutputStream(socket.getOutputStream());
				ObjectInputStream ois = new ObjectInputStream(socket.getInputStream());
				
				// On connection, pass a ‘login message’ to the server.
				oos.writeObject(new Message("login", "undefined", "undefined"));
				
				Message loginReply = (Message) ois.readObject();
				if(!loginReply.getStatus().equals("success")) {
					throw new Exception("Client login, found: " + loginReply.getStatus());
				}
				System.out.println("Logged in.");
				
				while(true) {
					System.out.print("Enter message: ");
					String input = sc.next();
					
					if(input.equals("logout")) {
						// send logout message
						oos.writeObject(new Message("logout", "undefined", "undefined"));
						Message logoutReply = (Message) ois.readObject();
						if(!logoutReply.getStatus().equals("success")) {
							throw new Exception("Client logout, found: " + logoutReply.getStatus());
						}
						
						break;
					}
					
					oos.writeObject(new Message("text", "undefined", input));
					Message textReply = (Message) ois.readObject();
					System.out.println(textReply.getText());
				}
				
				System.out.println("Logged out.");
			}
		}
		
	}
}
