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
