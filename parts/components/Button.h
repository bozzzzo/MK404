/*
	Button.h - simple button for SimAVR

	Original Copyright 2008, 2009 Michel Pollet <buserror@gmail.com>

	Rewritten/converted to c++ in 2020 by VintagePC <https://github.com/vintagepc/>

 	This file is part of MK3SIM.

	MK3SIM is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	MK3SIM is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with MK3SIM.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once

#include <stdint.h>            // for uint32_t
#include <string>              // for string
#include <vector>              // for vector
#include "BasePeripheral.h"    // for BasePeripheral, MAKE_C_TIMER_CALLBACK
#include "IScriptable.h"       // for IScriptable::LineStatus
#include "Scriptable.h"        // for Scriptable
#include "sim_avr.h"           // for avr_t
#include "sim_avr_types.h"     // for avr_cycle_count_t
#include "sim_cycle_timers.h"  // for avr_cycle_timer_t

class Button:public BasePeripheral, public Scriptable
{
	public:
	#define IRQPAIRS _IRQ(BUTTON_OUT,">button.out")
	#include "IRQHelper.h"

	// Creates a new button with name strName
	Button(std::string strName = "Button");

	// Initializes the button on "avr"
	void Init(struct avr_t * avr);

	// Presses the button for a given duration (us, default 1000)
	void Press(uint32_t uiUSec = 1000);

	protected:
		LineStatus ProcessAction(unsigned int iAction, const vector<string> &vArgs) override;

	private:
		avr_cycle_count_t AutoRelease(avr_t *avr, avr_cycle_count_t uiWhen);

		avr_cycle_timer_t m_fcnRelease = MAKE_C_TIMER_CALLBACK(Button,AutoRelease);

		std::string m_strName;

		enum Actions
		{
			ActPress,
			ActRelease,
			ActPressAndRelease
		};

};
