package com.dreamcrushed.DeviceUser;
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.UnknownHostException;

import com.dreamcrushed.DeviceUser.Packet.CommandPacket;


public class Main {

	/**
	 * @param args
	 */
	public static void main(String[] args) {
		try {
			NetworkManager nm = new NetworkManager("localhost", 8010);
			nm.start();
			nm.login("user", "pass");
			while (true) {
				BufferedReader readIn = new BufferedReader(new InputStreamReader(System.in));
				String command = readIn.readLine();
				command = command.substring(0, command.length());
//				System.out.println(command.length() + "");
				nm.sendPacket(new CommandPacket(command));
//				try {
//					Thread.sleep(1000);
//				} catch (InterruptedException e) {
//					e.printStackTrace();
//				}
			}
		} catch (UnknownHostException e) {
			e.printStackTrace();
		} catch (IOException e) {
			e.printStackTrace();
		} catch (LoginException e) {
			e.printStackTrace();
		}
	}

}
