package com.dreamcrushed.DeviceUser.Packet;

import com.dreamcrushed.DeviceUser.Device;
import com.dreamcrushed.DeviceUser.NetworkManager;
import com.dreamcrushed.DeviceUser.Util;

public class DeviceDefPacket extends Packet {

	private int id;
	private String name;
	private String cname;
	private int room;
	private int icon;
	private float x;
	private float y;

	public DeviceDefPacket(int id, String[] params) {
		super(params);
		this.id = Integer.parseInt(params[0]);
		System.out.println("Device Id String: " + params[0] + "  DeviceId: " + this.id);
		name = params[1];
		cname = params[2];
		room = Integer.parseInt(params[3]);
		icon = Integer.parseInt(params[4]);
		x = Float.parseFloat(params[5]);
		y = Float.parseFloat(params[6]);
	}
	
	@Override
	public void handle(NetworkManager networkManager) {
		super.handle(networkManager);
	
		networkManager.getDeviceManager().setDevice(id, new Device(id, name, cname, room, icon, x, y));
	}

	@Override
	public String packetString() {
		return Util.concat(new String[] {PacketType.DEVICE_DEF.getType() + "", NetworkManager.getUserId() + ""}, ":");
	}

}
