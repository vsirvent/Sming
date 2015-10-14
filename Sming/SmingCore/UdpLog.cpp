/*
 * Log.cpp
 *
 *  Created on: Oct 9, 2015
 *      Author: vicen
 */

#include "UdpLog.h"
#include "HardwareSerial.h"

#define START_LOG "log on"
#define STOP_LOG "log off"
#define MAX_DATA_LEN 256

UdpLog Serial(6667);

UdpLog::UdpLog(int listen_port)
{
	mRemoteIP = INADDR_NONE;
	mRemotePort = 0;
	mUdp = new UdpConnection(UdpConnectionDataDelegate(&UdpLog::OnData, this));
	mUdp->listen(listen_port);
	mTimer.initializeMs(100, TimerDelegate( &UdpLog::OnTimer, this));

}

UdpLog::~UdpLog()
{
	mUdp->close();
}

void
UdpLog::OnTimer() {
	if (mData.length() > 0) {
		mUdp->sendTo(mRemoteIP, mRemotePort, (const char*)mData.c_str(), mData.length());
		mData = "";
	}
}

size_t
UdpLog::write(uint8_t c) {
	if (mRemoteIP[0] != 0 && mRemotePort != 0) {
		mData += (char)c;
		if (c == 0x0A || mData.length() == (MAX_DATA_LEN - 1)) {
			mTimer.startOnce();
		}
	}
	return HWSerial.write(c);
}

void
UdpLog::OnData(UdpConnection& connection, char *data, int size, IPAddress remoteIP, uint16_t remotePort)
{
	if (strstr(data, START_LOG) != NULL) {
		mRemoteIP = remoteIP;
		mRemotePort = remotePort;
	}else if (strstr(data, STOP_LOG) != NULL) {
		mRemoteIP = INADDR_NONE;
		mRemotePort = 0;
	}else{
		mUdp->sendStringTo(remoteIP, remotePort, "Usage: log on/off\n");
	}
}
