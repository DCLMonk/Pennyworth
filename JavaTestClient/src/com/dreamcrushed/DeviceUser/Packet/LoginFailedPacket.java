package com.dreamcrushed.DeviceUser.Packet;

import com.dreamcrushed.DeviceUser.NetworkManager;
import com.dreamcrushed.DeviceUser.Util;

public class LoginFailedPacket extends Packet {

	private String error;

	public LoginFailedPacket(int id, String[] params) {
		super(params);
		this.error = params[0];
	}
	
	@Override
	public void handle(NetworkManager networkManager) {
		super.handle(networkManager);
		System.out.println("Error: " + this.error);
		// TODO: Handle Error Here
	}

	@Override
	public String packetString() {
		// Incoming only...
		return Util.concat(new String[] {PacketType.LOGIN.getType() + "", NetworkManager.getUserId() + ""}, ":");
	}

}
