package com.dreamcrushed.DeviceUser.Packet;

import com.dreamcrushed.DeviceUser.NetworkManager;
import com.dreamcrushed.DeviceUser.Util;

public class UIDPacket extends Packet {

	private int uid;

	public UIDPacket(int id, String[] params) {
		super(params);
		uid = id;
	}
	
	@Override
	public void handle(NetworkManager networkManager) {
		super.handle(networkManager);
		
		networkManager.setUID(uid);
		System.out.println("Got UID: " + NetworkManager.getUserId());
	}

	@Override
	public String packetString() {
		// Incoming only...
		return Util.concat(new String[] {PacketType.UID.getType() + "", NetworkManager.getUserId() + ""}, ":");
	}

}
