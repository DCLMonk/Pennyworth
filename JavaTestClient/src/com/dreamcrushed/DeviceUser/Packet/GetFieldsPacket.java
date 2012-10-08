package com.dreamcrushed.DeviceUser.Packet;

import com.dreamcrushed.DeviceUser.NetworkManager;
import com.dreamcrushed.DeviceUser.Util;

public class GetFieldsPacket extends Packet {
	private int device;
	private int field;

	public GetFieldsPacket(int device) {
		super(new String[0]);
		this.device = device;
		this.field = -1;
	}

	public GetFieldsPacket(int device, int field) {
		super(new String[0]);
		this.device = device;
		this.field = field;
	}

	@Override
	public String packetString() {
		if (field != -1) {
			return Util.concat(new String[] {PacketType.GET_FIELDS.getType() + "", NetworkManager.getUserId() + "", device + "", field + ""}, ":");
		} else {
			return Util.concat(new String[] {PacketType.GET_FIELDS.getType() + "", NetworkManager.getUserId() + "", device + ""}, ":");
		}
	}

}
