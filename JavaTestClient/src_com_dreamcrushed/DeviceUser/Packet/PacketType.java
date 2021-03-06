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


import java.lang.reflect.Constructor;
import java.lang.reflect.InvocationTargetException;
import java.util.HashMap;
import java.util.Map;


/**
 * This enum will contain the type of every packet in existence.
 * It will also contain information like the class, type id, and
 * name.
 * 
 * @author jmonk
 */
public enum PacketType {
	LOGIN(1, LoginPacket.class),
	UID(2, UIDPacket.class),
	LOGIN_FAILED(3, LoginFailedPacket.class),
	GET_DEVICES(4, GetDevicesPacket.class),
	DEVICE_DEF(5, DeviceDefPacket.class),
	GET_FIELDS(6, GetFieldsPacket.class),
	FIELD_INFO(7, FieldInfoPacket.class),
	GET_FIELD(8, GetFieldPacket.class),
	SEND_FIELD(9, SendFieldPacket.class),
	SET_FIELD(10, SetFieldPacket.class),
	COMMAND(11, CommandPacket.class),
	;
	
	private int type;
	private Class<? extends Packet> cl;
	private static Map<Integer, PacketType> types = new HashMap<Integer, PacketType>();

	private PacketType(int type, Class<? extends Packet> cl) {
		this.cl = cl;
		this.type = type;
	}
	
	/**
	 * Getter method used to get the integer type of the PacketType.
	 * 
	 * @return Type Id
	 */
	public int getType() {
		return type;
	}

	/**
	 * Get the PacketType associated with the given type id.
	 * 
	 * @param type Type id of Packet
	 * @return PacketType
	 */
	public static PacketType fromInt(int type) {
		return types.get(type);
	}

	/**
	 * This creates an instance of the PacketType. This will only
	 * work if the packet has a constructor that takes (int, String[]).
	 * Otherwise an exception will be thrown. Any packets designed for
	 * network transfer should have the given constructor.
	 *
	 * @param id Packet id (0 for local)
	 * @param params Any packet specific data
	 * @return new Packet
	 */
	public Packet instance(int id, String[] params) throws SecurityException, NoSuchMethodException, IllegalArgumentException, InstantiationException, IllegalAccessException, InvocationTargetException {
		Constructor<? extends Packet> m = cl.getConstructor(int.class, String[].class);
		
		return m.newInstance(id, params);
	}
	
	static {
		for (PacketType type : values()) {
			types.put(type.type, type);
		}
	}
}
