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
import java.io.OutputStream;
import java.io.PrintStream;

import com.dreamcrushed.DeviceUser.Packet.Packet;


public class WriterThread extends Thread {

	private OutputStream outputStream;
	public boolean mRun;
	private PrintStream printStream;

	public WriterThread(OutputStream outputStream) {
		this.outputStream = outputStream;
		this.printStream = new PrintStream(this.outputStream);
		mRun = true;
	}

	public void sendPacket(Packet packet) {
//		System.out.println("Sending Packet\n");
		String s = packet.packetString();
		printStream.println(s);
	}
	
	@Override
	public void run() {
		while (mRun) {
			// No thread currently
			break;
		}
		mRun = false;
	}

}
