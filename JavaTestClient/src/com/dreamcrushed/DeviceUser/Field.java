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
