package com.dreamcrushed.DeviceUser;

import java.util.ArrayList;
import java.util.List;

import com.dreamcrushed.DeviceUser.Packet.ChangeListener;

public class Field {
	protected String name;
	protected FieldType type;
	protected boolean writable;
	protected boolean vol;
	protected int id;
	
	protected Device owner;
	
	protected List<ChangeListener> changeListeners;

	public Field(Device owner, String name, FieldType type, boolean writable, boolean vol,
			int id) {
		this.id = id;
		this.owner = owner;
		setVals(name, type, writable, vol);
		this.changeListeners = new ArrayList<ChangeListener>();
	}

	public void setVals(String name, FieldType type, boolean writable,
			boolean vol) {
		this.name = name;
		this.type = type;
		this.writable = writable;
		this.vol = vol;
	}
	
	public void change() {
		for (ChangeListener listener : changeListeners) {
			listener.changeOccured(owner, this);
		}
	}
	
	public void addListener(ChangeListener listener) {
		changeListeners.add(listener);
	}
	
	public void remListener(ChangeListener listener) {
		changeListeners.remove(listener);
	}

	public void setValue(String value) {
		change();
	}
	
	public String getValue() {
		return "";
	}

}
