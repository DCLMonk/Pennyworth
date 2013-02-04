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
