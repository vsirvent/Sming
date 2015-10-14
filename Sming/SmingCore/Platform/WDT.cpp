/*
 * WDT.cpp
 *
 *  Created on: 06 ���. 2015 �.
 *      Author: Anakod
 */

#include "WDT.h"
#include <user_interface.h>
WDTClass WDT;

WDTClass::WDTClass()
{
	//enabled = true;
}

void WDTClass::enable(bool enableWatchDog)
{
	enabled = enableWatchDog;
	if (System.isReady())
		internalApplyEnabled();
	else
		System.onReady(this);
}

void WDTClass::alive()
{
	WRITE_PERI_REG(0x60000914, 0x73);
	system_soft_wdt_feed();
}

void WDTClass::onSystemReady()
{
	internalApplyEnabled();
}

void WDTClass::internalApplyEnabled()
{
	if (enabled)
		ets_wdt_enable();
	else
		ets_wdt_disable();
}
