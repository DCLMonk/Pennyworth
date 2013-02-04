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

public class Util {

	/**
	 * Used to turn a list into a string with the specified delimiter.
	 * If there are less than 2 items in the list the delimiter will
	 * not appear.
	 * 
	 * @param list List to Serialize
	 * @param delim Delimiting Character
	 * @return Serialized String
	 */
	public static String concat(List<?> list, String delim) {
		String ret = list.get(0) + "";
		for (int i = 1; i < list.size(); i++) {
			ret = ret + delim + list.get(i);
		}
		return ret;
	}

	/**
	 * Used to turn a list into a string with the specified delimiter.
	 * If there are less than 2 items in the list the delimiter will
	 * not appear.
	 * 
	 * @param list List to Serialize
	 * @param delim Delimiting Character
	 * @return Serialized String
	 */
	public static String concat(Object[] list, String delim) {
		String ret = list[0] + "";
		for (int i = 1; i < list.length; i++) {
			ret = ret + delim + list[i];
		}
		return ret;
	}
	
	public static List<Integer> getInts(String list, String delim) {
		String[] slist = list.split(delim);
		List<Integer> ret = new ArrayList<Integer>();
		
		for (int i = 0; i < slist.length; i++) {
			ret.add(Integer.parseInt(slist[i]));
		}
		
		return ret;
	}
	
	public static List<Double> getDoubles(String list, String delim) {
		String[] slist = list.split(delim);
		List<Double> ret = new ArrayList<Double>();
		
		for (int i = 0; i < slist.length; i++) {
			ret.add(Double.parseDouble(slist[i]));
		}
		
		return ret;
	}

	public static List<String> getStrings(String list, String delim) {
		String[] slist = list.split(delim);
		List<String> ret = new ArrayList<String>();
		
		for (int i = 0; i < slist.length; i++) {
			ret.add(slist[i]);
		}
		
		return ret;
	}

}
