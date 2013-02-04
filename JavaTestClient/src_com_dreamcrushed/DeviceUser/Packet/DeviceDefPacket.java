/**
 * Pennyworth - A new smarthome protocol.
 * Copyright (C) 2012  Dream-Crusher Labs LLC
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */
package com.dreamcrushed.DeviceUser.Packet;

import com.dreamcrushed.DeviceUser.Device;
import com.dreamcrushed.DeviceUser.NetworkManager;
import com.dreamcrushed.DeviceUser.Util;

public class DeviceDefPacket extends Packet {
    private static DeviceDefListener listener = null;

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
	
        Device newDevice = new Device(id, name, cname, room, icon, x, y);
		networkManager.getDeviceManager().setDevice(id, newDevice);
        if (listener != null) {
            listener.deviceCreated(newDevice);
        }
	}

	@Override
	public String packetString() {
		return Util.concat(new String[] {PacketType.DEVICE_DEF.getType() + "", NetworkManager.getUserId() + ""}, ":");
	}

    public static void setDefListener(DeviceDefListener listener) {
        DeviceDefPacket.listener = listener;
    }

    public interface DeviceDefListener {
        public void deviceCreated(Device device);
    }

}
