package com.dreamcrushed.DeviceUser.Packet;

import com.dreamcrushed.DeviceUser.NetworkManager;
import com.dreamcrushed.DeviceUser.Util;

public class GetFieldPacket extends Packet {
	private int device;
	private int field;

	public GetFieldPacket(int device, int field) {
		super(new String[0]);
		this.device = device;
		this.field = field;
	}

	@Override
	public String packetString() {
		return Util.concat(new String[] {PacketType.GET_FIELD.getType() + "", NetworkManager.getUserId() + "", device + "", field + ""}, ":");
	}

}
