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
import java.io.BufferedReader;
import java.io.InputStream;
import java.io.InputStreamReader;

import com.dreamcrushed.DeviceUser.Packet.Packet;
import com.dreamcrushed.DeviceUser.Packet.PacketType;


public class ReaderThread extends Thread {
	private InputStream inputStream;
	public boolean mRun;
	private BufferedReader bufferedReader;
	private NetworkManager networkManager;

	public ReaderThread(InputStream inputStream, NetworkManager networkManager) {
		this.inputStream = inputStream;
		this.bufferedReader = new BufferedReader(new InputStreamReader(this.inputStream));
		this.networkManager = networkManager;
		mRun = true;
	}

	public void removePacket(Packet packet) {
		
	}
	
	public void run() {
		System.out.println("Reader Thread Starting Up...");
		while (mRun) {
			try {
				String packet = this.bufferedReader.readLine();
				
				Packet p = Packet.newPacket(packet);
				p.handle(networkManager);
			} catch (Exception e) {
				e.printStackTrace();
			}
		}
	}

}
