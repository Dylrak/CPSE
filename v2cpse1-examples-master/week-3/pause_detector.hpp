#ifndef PAUSE_DETECTOR_H
#define PAUSE_DETECTOR_H

#include "rtos.hpp"
#include "ir_receiver.hpp"

class pause_listener
{
public:
	virtual void pause_detected( uint_fast64_t & length ) = 0;
};

class pause_detector : public rtos::task<>
{
private:
	ir_receiver & ir_signal;
	pause_listener & pl;
	uint_fast64_t length;
	uint_fast64_t start;
	enum class states { idle, ir_signal };
	states state;
	rtos::clock polling_clock;

	void main() {
		length = 0;
		state = states::idle;
		for (;;) {
			wait ( polling_clock );
			switch (state) {
				case states::idle:
					length += polling_clock.interval();
					if ( ir_signal.get() ) { //If we are receiving signal, flush length to pause listener channel.
						pl.pause_detected( length );
						state = states::ir_signal;
					}
					break;
				case states::ir_signal:
					if ( !ir_signal.get() ) { //If we aren't receiving signal, return to idle state and reset pause length.
						state = states::idle;
						length = 0;
					}
					break;
			}
		}
	}

public:
	pause_detector( ir_receiver & irr, pause_listener & pl ):
		task( "pause detector" ),
		ir_signal ( irr ),
		pl ( pl ),
		polling_clock ( this, 100, "IR receiver polling clock")
	{}
};

#endif // PAUSE_DETECTOR_H
