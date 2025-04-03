# networking
This repository contains all my practiced Packet Tracer files, networking configurations, related commands and also few codes.


UDP-client in Java


import java.io.*;
import java.net.*;
class UDPClient {
public static void main(String args[ ]) throws Exception {
BufferedReader inFromUser = new BufferedReader(new
InputStreamReader(System.in)); DatagramSocket clientSocket =
new DatagramSocket();
InetAddress IPAddress = InetAddress.getByName(”hostname”);
byte[ ] sendData = new byte[1024];
byte[ ] recieveData = new byte[1024];
String sentence = inFromUser.readLine();
sendData = sentence.getBytes ();
DatagramPacket sendPacket = new DatagramPacket(sendData,
sendData.length, IPAddress, 9876); clientSocket.send(sendPacket);
DatagramPacket receivePacket = new
DatagramPacket(receiveData, receiveData.length);
clientSocket.receive(receivePacket);
String modefiedSentence = new String(receivePacket.getData());
System.out.println(”FROM SERVER:” + modifiedSentence);
clientSocket.close();
} }




UDP-server in Java


import java.io.*;
import java.net.*;
class UDPClient {
public static void main(String args[ ]) throws Exception {
DatagramSocket serverSocket = new DatagramSocket(9876);
byte[ ] receiveData = new byte[1024];
byte[ ] sendData = new byte[1024];
while(true) {
DatagramPacket receivePacket = new
DatagramPacket(receiveData, receiveData.length);
serverSocket.receive(receivePacket);
String sentence = new String(receivePacket.getData());
InetAddress IPAddress = receivePacket.getAddress();
int port = receivePacket.getPort();
String catitalizedSentence = sentence.toUpperCase();
sendData = capetalizedSentence.getBytes ();
DatagramPacket sendPacket = new DatagramPacket(sendData,
sendData.length, IPAddress, port); clientSocket.send(sendPacket);
DatagramPacket receivePacket = new
DatagramPacket(receiveData, receiveData.length);
serverSocket.send(sendPacket); } } }