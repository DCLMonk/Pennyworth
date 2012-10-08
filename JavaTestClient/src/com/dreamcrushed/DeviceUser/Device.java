package com.dreamcrushed.DeviceUser;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.dreamcrushed.DeviceUser.Packet.ChangeListener;

public class Device {

	private int id;
	private String name;
	private String cname;
	private int room;
	private int icon;
	private float x;
	private float y;
	private Map<Integer, Field> fields;
	
	protected List<ChangeListener> changeListeners;

	public Device(int id, String name, String cname, int room, int icon,
			float x, float y) {
		this.id = id;
		this.name = name;
		this.cname = cname;
		this.room = room;
		this.icon = icon;
		this.x = x;
		this.y = y;
		this.fields = new HashMap<Integer, Field>();
		this.changeListeners = new ArrayList<ChangeListener>();
		
		System.out.println("Created Device: " + name);
		System.out.println("Common Name: " + cname);
		System.out.println("Id: " + id + " Room: " + room + " X-Y:" + x + "-" + y + "\n");
	}

	public void setField(int id, String name, FieldType type, boolean writable,
			boolean vol) {
		if (fields.get(id) != null) {
			fields.get(id).setVals(name, type, writable, vol);
		} else {
			fields.put(id, new Field(this, name, type, writable, vol, id));
		}
		System.out.println("Field Defined for " + this.name);
		System.out.println("Id: " + id + "\t Name: " + name);
		System.out.println("Type: " + type + " Writable: " + writable + " Volatile: " + vol + "\n");
	}
	
	public Field getField(int fid) {
		return fields.get(fid);
	}
	
	public void change() {
		for (ChangeListener listener : changeListeners) {
			listener.changeOccured(this);
		}
	}
	
	public void addListener(ChangeListener listener) {
		changeListeners.add(listener);
	}
	
	public void remListener(ChangeListener listener) {
		changeListeners.remove(listener);
	}

	public int getId() {
		return id;
	}

	public String getName() {
		return name;
	}

	public String getCname() {
		return cname;
	}

	public int getRoom() {
		return room;
	}

	public int getIcon() {
		return icon;
	}

	public float getX() {
		return x;
	}

	public float getY() {
		return y;
	}

}
