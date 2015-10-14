/*
 * Log.h
 *
 *  Created on: Oct 9, 2015
 *      Author: vicen
 */

#ifndef APP_UDPLOG_H_
#define APP_UDPLOG_H_

#include "../Wiring/Print.h"
#include "../Wiring/Stream.h"
#include "../Wiring/WString.h"
#include "Timer.h"
#include "./Network/UdpConnection.h"

class UdpLog: public Stream
{
private:
	Timer mTimer;
	UdpConnection* mUdp;
	IPAddress mRemoteIP;
	uint16_t mRemotePort;
	String mData;

	void OnTimer();
	void OnData(UdpConnection& connection, char *data, int size, IPAddress remoteIP, uint16_t remotePort);

public:
	UdpLog(int listen_port);
	virtual ~UdpLog();

    int available(){ return 0; }
    int peek(){ return 0; }
    int read(){ return 0; }
    void flush(){}

	size_t write(uint8_t);
};

extern UdpLog Serial;

#endif /* APP_UDPLOG_H_ */
