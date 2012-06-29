/*
 * GetDevicesPacket.h
 *
 *  Created on: Jun 28, 2012
 *      Author: jmonk
 */

#ifndef GETDEVICESPACKET_H_
#define GETDEVICESPACKET_H_

#include <CPacket.h>

namespace dvs {

class GetDevicesPacket: public dvs::CPacket {
public:
	GetDevicesPacket(string data);
	virtual ~GetDevicesPacket();
};

} /* namespace dvs */
#endif /* GETDEVICESPACKET_H_ */
