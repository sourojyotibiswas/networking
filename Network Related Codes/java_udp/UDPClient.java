import java.net.*;
import java.io.*;

public class UDPClient {
    public static void main(String[] args) throws Exception {
        DatagramSocket clientSocket = new DatagramSocket();
        InetAddress serverAddress = InetAddress.getByName("localhost");

        BufferedReader userInput = new BufferedReader(new InputStreamReader(System.in));

        System.out.print("Enter message: ");
        String message = userInput.readLine();
        byte[] sendData = message.getBytes();

        // Send packet to server
        DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, serverAddress, 9876);
        clientSocket.send(sendPacket);

        // Receive response
        byte[] receiveData = new byte[1024];
        DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
        clientSocket.receive(receivePacket);

        String modifiedMessage = new String(receivePacket.getData(), 0, receivePacket.getLength());
        System.out.println("FROM SERVER: " + modifiedMessage);

        clientSocket.close();
    }
}
