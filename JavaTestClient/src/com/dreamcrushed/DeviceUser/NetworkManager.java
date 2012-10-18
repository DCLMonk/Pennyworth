/**
 * Pennyworth - A new smarthome protocol.
 * Copyright (C) 2012  Dream-Crusher Labs LLC
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
package com.dreamcrushed.DeviceUser;


import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;

import com.dreamcrushed.DeviceUser.Packet.GetDevicesPacket;
import com.dreamcrushed.DeviceUser.Packet.LoginPacket;
import com.dreamcrushed.DeviceUser.Packet.Packet;

/**
 * The network manager handles all of the threads related to communicating
 * with the TerraSoul server. This is done through a series of HTTP POST
 * Requests. 
 * 
 * @author jmonk
 */
public class NetworkManager {
	public static NetworkManager instance;
	private ReaderThread reader;
	private WriterThread writer;
	private DeviceManager manager;
	private int id;
	private String session;
	private String password;
	private String user;
	private boolean loggedIn;
	private Socket socket;

	public NetworkManager(String host, int port) throws UnknownHostException, IOException {
		instance = this;
		this.socket = new Socket(host, port);
		reader = null;
		writer = null;
		manager = new DeviceManager();
		invalidateLogin();
	}
	
	/**
	 * Clears the current login information and resets the state of the
	 * network manager to have no login information. Resets the user id
	 * as well as the session id.
	 */
	public void invalidateLogin() {
		loggedIn = false;
		id = 0;
		session = "0";
	}

	/**
	 * This starts up both of the networking threads (reader and writer).
	 * They will remain asleep most of the time. The reader thread will read
	 * packets at the set read rate and the writer thread will remain asleep
	 * except for when packets are in the send queue.
	 * @throws IOException 
	 */
	public void start() throws IOException {
		if (reader != null) {
			reader.mRun = false;
		}
		reader = new ReaderThread(this.socket.getInputStream(), this);
		if (writer != null) {
			writer.mRun = false;
		}
		writer = new WriterThread(this.socket.getOutputStream());
		reader.start();
		writer.start();
	}
	
	/**
	 * This stops both of the network threads. The reader thread will finish
	 * reading any packets already downloaded from the server and parsing those,
	 * while the writer thread will immediately transmit all packets in its queue
	 * followed by shutting down.
	 */
	public void stop() {
		reader.mRun = false;
		writer.mRun = false;
	}

	/**
	 * Gets the username of the player currently logged in.
	 * 
	 * @return Username or NULL if none known.
	 */
	public String getUser() {
		return user;
	}

	/**
	 * Gets the session id of the user logged in that is passed to TerraSoul
	 * scripts. This will be "0" if not logged in currently.
	 *
	 * @return User Session ID
	 */
	public String getSession() {
		return session;
	}

	/**
	 * Gets the id of the user logged in. This is passed to TerraSoul scripts
	 * to speed up the login verification process. If the user is not logged in
	 * the function returns -1.
	 *
	 * @return User ID or -1 if not logged in.
	 */
	static public int getUserId() {
		return instance.id;
	}

	/**
	 * This adds a packet to the send queue of the network writer thread.
	 * The packet will be sent at the next available time in the thread's
	 * queue.
	 * 
	 * @param packet Packet to be sent
	 * @throws LoginException If user is not logged in.
	 */
	public void sendPacket(Packet packet) throws LoginException {
		writer.sendPacket(packet);
	}

	/**
	 * This adds a packet to the remove list of the network reader thread.
	 * If a packet is not removed before the next read performed by the reader
	 * thread then the packet will be received and handled again.
	 * 
	 * @param packet Packet to remove
	 */
	public void removePacket(Packet packet) {
		reader.removePacket(packet);
	}

	/**
	 * Gets the password associated with the current login. Will only return
	 * valid data in the process of login. Once a session id has been validated
	 * then the password will become null.
	 * @return
	 */
	public String getPassword() {
		return password;
		
	}
	
	/**
	 * This returns true if the network manager is currently successfully logged
	 * in to the server.
	 * 
	 * @return
	 */
	public boolean isLoggedIn() {
		return loggedIn;
	}

	public void setUID(int id) {
		this.id = id;
		
		writer.sendPacket(new GetDevicesPacket());
	}

	public void login(String user, String pass) {
		writer.sendPacket(new LoginPacket(user, pass));
	}

	public DeviceManager getDeviceManager() {
		return manager;
	}
}
