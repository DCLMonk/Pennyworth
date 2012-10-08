package com.dreamcrushed.DeviceUser.Packet;

import com.dreamcrushed.DeviceUser.NetworkManager;
import com.dreamcrushed.DeviceUser.Util;

public class GetDevicesPacket extends Packet {
	private int device = -1;

	public GetDevicesPacket() {
		super(new String[0]);
	}

	public GetDevicesPacket(int device) {
		super(new String[0]);
		this.device = device;
	}

	@Override
	public String packetString() {
		if (device != -1) {
			return Util.concat(new String[] {PacketType.GET_DEVICES.getType() + "", NetworkManager.getUserId() + "", device + ""}, ":");
		} else {
			return Util.concat(new String[] {PacketType.GET_DEVICES.getType() + "", NetworkManager.getUserId() + ""}, ":");
		}
	}

}
