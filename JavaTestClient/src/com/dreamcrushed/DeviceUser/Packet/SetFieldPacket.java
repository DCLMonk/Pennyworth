package com.dreamcrushed.DeviceUser.Packet;

import com.dreamcrushed.DeviceUser.NetworkManager;
import com.dreamcrushed.DeviceUser.Util;

public class SetFieldPacket extends Packet {
	private int device;
	private int field;
	private String value;

	public SetFieldPacket(int device, int field, String value) {
		super(new String[0]);
		this.device = device;
		this.field = field;
		this.value = value;
	}

	@Override
	public String packetString() {
		return Util.concat(new String[] {PacketType.SET_FIELD.getType() + "", NetworkManager.getUserId() + "", device + "", field + "", value}, ":");
	}

}
