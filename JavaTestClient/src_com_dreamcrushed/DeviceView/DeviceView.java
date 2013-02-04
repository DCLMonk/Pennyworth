package com.dreamcrushed.DeviceView;

import com.dreamcrushed.DeviceUser.Packet.DeviceDefPacket;
import com.dreamcrushed.DeviceUser.Device;

public class DeviceView extends BasePage {

    public DeviceView() {
        DeviceDefPacket.setDefListener(new DeviceDefPacket.DeviceDefListener() {
            @Override
            public void deviceCreated(Device device) {
                deviceC(device);
            }
        });
    }

    public void deviceC(Device device) {

    }
    
}
