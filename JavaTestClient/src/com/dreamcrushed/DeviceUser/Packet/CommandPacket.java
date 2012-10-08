package com.dreamcrushed.DeviceUser.Packet;

import com.dreamcrushed.DeviceUser.NetworkManager;
import com.dreamcrushed.DeviceUser.Util;

public class CommandPacket extends Packet {
	private String command;
	private String output;

	public CommandPacket(String command) {
		super(new String[0]);
		this.command = command.replaceAll(":", ";");
	}

	public CommandPacket(int id, String[] params) {
		super(params);
		if (params.length > 0) {
			output = params[0].replaceAll("\f", "\n").replaceAll(";", ":");
		} else {
			output = "No Output from Server";
		}
	}
	
	@Override
	public void handle(NetworkManager networkManager) {
		super.handle(networkManager);
		System.out.print(output);
	}

	@Override
	public String packetString() {
		return Util.concat(new String[] {PacketType.COMMAND.getType() + "", NetworkManager.getUserId() + "", command}, ":");
	}

}
