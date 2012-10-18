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
package com.dreamcrushed.DeviceUser;

import java.util.HashMap;
import java.util.Map;

public enum FieldType {
	BOOL(0),
	INTEGER(1),
	FLOAT(2),
	FIXED(3),
	STRING(4);
	
	private int id;
	private static Map<Integer, FieldType> types = new HashMap<Integer, FieldType>();

	private FieldType(int id) {
		this.id = id;
	}
	
	public static FieldType getType(int id) {
		return types.get(id);
	}
	
	static {
		for (FieldType type : values()) {
			types.put(type.id, type);
		}
	}
}
