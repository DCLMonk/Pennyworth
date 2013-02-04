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


import java.lang.reflect.InvocationTargetException;

import com.dreamcrushed.DeviceUser.InvalidPacketException;
import com.dreamcrushed.DeviceUser.NetworkManager;

/**
 * This is the basic unit of communication between the TerraSoul
 * server and client. Classes extend packet and are designed to
 * be self handling through the handle method. They also have
 * unique states where they are transferred to a string and back
 * for network transfer implemented using the packetString and
 * newPacket methods.
 * 
 * @author jmonk
 */
public abstract class Packet {

	public Packet(String[] params) {
	}

	/**
	 * Creates an instance of a packet based on the type contained in the
	 * packet string.
	 * 
	 * @param s Packet String
	 * @return Packet
	 */
	public static Packet newPacket(String s) throws InvalidPacketException {
		String[] split = s.split(":");
		PacketType type = PacketType.fromInt(Integer.parseInt(split[0]));
		if (type == null) {
			throw new InvalidPacketException();
		}
		String[] params = new String[split.length - 2];
		for (int i = 2; i < split.length; i++) {
			params[i - 2] = split[i];
		}
		try {
			return type.instance(Integer.parseInt(split[1]), params);
		} catch (NumberFormatException e) {
			throw new InvalidPacketException();
		} catch (SecurityException e) {
			throw new InvalidPacketException();
		} catch (NoSuchMethodException e) {
			throw new InvalidPacketException();
		} catch (IllegalArgumentException e) {
			throw new InvalidPacketException();
		} catch (InstantiationException e) {
			throw new InvalidPacketException();
		} catch (IllegalAccessException e) {
			throw new InvalidPacketException();
		} catch (InvocationTargetException e) {
			e.getTargetException().printStackTrace();
			throw new InvalidPacketException();
		}
	}

	/**
	 * Handles any client side parsing required by this packet. Could be anything
	 * from sending the user a message to modifying health of a character on screen.
	 * Should be overloaded in any packet which is to do anything.
	 *
	 * @param networkManager
	 */
	public void handle(NetworkManager networkManager) {
		networkManager.removePacket(this);
	}

	/**
	 * Turn this packet into a string that can be transferred over the network.
	 * 
	 * @return Packet String
	 */
	public abstract String packetString();

}
