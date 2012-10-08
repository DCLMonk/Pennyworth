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
