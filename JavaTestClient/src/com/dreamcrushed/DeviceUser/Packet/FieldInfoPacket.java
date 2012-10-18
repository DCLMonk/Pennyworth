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

import com.dreamcrushed.DeviceUser.FieldType;
import com.dreamcrushed.DeviceUser.NetworkManager;
import com.dreamcrushed.DeviceUser.Util;

public class FieldInfoPacket extends Packet {

	private int did;
	private int id;
	private String name;
	private FieldType type;
	private boolean writable;
	private boolean vol;

	public FieldInfoPacket(int id, String[] params) {
		super(params);
		did = Integer.parseInt(params[0]);
		id = Integer.parseInt(params[1]);
		name = params[2];
		type = FieldType.getType(Integer.parseInt(params[3]));
		writable = Integer.parseInt(params[4]) > 0;
		vol = Integer.parseInt(params[5]) > 0;
	}
	
	@Override
	public void handle(NetworkManager networkManager) {
		super.handle(networkManager);
		
		networkManager.getDeviceManager().getDevice(did).setField(id, name, type, writable, vol);
	}

	@Override
	public String packetString() {
		return Util.concat(new String[] {PacketType.FIELD_INFO.getType() + "", NetworkManager.getUserId() + ""}, ":");
	}

}
