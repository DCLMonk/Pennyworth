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
