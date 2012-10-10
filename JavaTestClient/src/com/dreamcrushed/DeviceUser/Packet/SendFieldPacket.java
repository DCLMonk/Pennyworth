package com.dreamcrushed.DeviceUser.Packet;

import com.dreamcrushed.DeviceUser.NetworkManager;
import com.dreamcrushed.DeviceUser.Util;

public class SendFieldPacket extends Packet {
	private int device;
	private int field;
	private String value;

	public SendFieldPacket(int id, String[] params) {
		super(params);
		this.device = Integer.parseInt(params[0]);
		this.field = Integer.parseInt(params[1]);
		this.value = params[2];
	}
	
	@Override
	public void handle(NetworkManager networkManager) {
		super.handle(networkManager);
		
		networkManager.getDeviceManager().getDevice(device).getField(field).setValue(value);
	}

	@Override
	public String packetString() {
		return Util.concat(new String[] {PacketType.SEND_FIELD.getType() + "", NetworkManager.getUserId() + "", device + "", field + "", value + ""}, ":");
	}

}
