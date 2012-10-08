package com.dreamcrushed.DeviceUser;

public class Device {

	private int id;
	private String name;
	private String cname;
	private int room;
	private int icon;
	private float x;
	private float y;

	public Device(int id, String name, String cname, int room, int icon,
			float x, float y) {
		this.id = id;
		this.name = name;
		this.cname = cname;
		this.room = room;
		this.icon = icon;
		this.x = x;
		this.y = y;
		System.out.println("Created Device: " + name);
		System.out.println("Common Name: " + cname);
		System.out.println("Id: " + id + " Room: " + room + " X-Y:" + x + "-" + y + "\n");
	}

	public void setField(int id, String name, FieldType type, boolean writable,
			boolean vol) {
		System.out.println("Field Defined for " + this.name);
		System.out.println("Id: " + id + "\t Name: " + name);
		System.out.println("Type: " + type + " Writable: " + writable + " Volatile: " + vol + "\n");
	}

}
