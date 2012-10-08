package com.dreamcrushed.DeviceUser.Packet;

import com.dreamcrushed.DeviceUser.FieldType;
import com.dreamcrushed.DeviceUser.NetworkManager;
import com.dreamcrushed.DeviceUser.Util;

public class FieldInfoPacket extends Packet {

	private int did;
	private int id;
	private String name;
	private FieldType type;
	private boolean writable;
	private boolean vol;

	public FieldInfoPacket(int id, String[] params) {
		super(params);
		did = Integer.parseInt(params[0]);
		id = Integer.parseInt(params[1]);
		name = params[2];
		type = FieldType.getType(Integer.parseInt(params[3]));
		writable = Integer.parseInt(params[4]) > 0;
		vol = Integer.parseInt(params[5]) > 0;
	}
	
	@Override
	public void handle(NetworkManager networkManager) {
		super.handle(networkManager);
		
		networkManager.getDeviceManager().getDevice(did).setField(id, name, type, writable, vol);
	}

	@Override
	public String packetString() {
		return Util.concat(new String[] {PacketType.FIELD_INFO.getType() + "", NetworkManager.getUserId() + ""}, ":");
	}

}
