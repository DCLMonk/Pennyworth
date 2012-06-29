/*
 * DeviceDefPacket.h
 *
 *  Created on: Jun 28, 2012
 *      Author: jmonk
 */

#ifndef DEVICEDEFPACKET_H_
#define DEVICEDEFPACKET_H_

#include <CPacket.h>
#include "Device.h"
#include "User.h"

namespace dvs {

class DeviceDefPacket: public dvs::CPacket {
public:
	DeviceDefPacket(Device* device, User* user);
	virtual ~DeviceDefPacket();

	void streamData(stringstream& data);

private:
	Device* device;
};

} /* namespace dvs */
#endif /* DEVICEDEFPACKET_H_ */
