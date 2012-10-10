package com.dreamcrushed.DeviceUser.Packet;

import com.dreamcrushed.DeviceUser.Device;
import com.dreamcrushed.DeviceUser.Field;

public interface ChangeListener {
	public void changeOccured(Device device);
	
	public void changeOccured(Device device, Field field);
}
