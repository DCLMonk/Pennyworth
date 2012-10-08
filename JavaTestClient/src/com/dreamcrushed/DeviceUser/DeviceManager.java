package com.dreamcrushed.DeviceUser;

import java.util.HashMap;
import java.util.Map;

import com.dreamcrushed.DeviceUser.Packet.GetFieldsPacket;

public class DeviceManager {
	private Map<Integer, Device> devices;
	
	public DeviceManager() {
		devices = new HashMap<Integer, Device>();
	}

	public void setDevice(int id, Device device) {
		devices.put(id, device);
		
		try {
			NetworkManager.instance.sendPacket(new GetFieldsPacket(id));
		} catch (LoginException e) {
			e.printStackTrace();
		}
	}
	
	public Device getDevice(int id) {
		return devices.get(id);
	}

}
