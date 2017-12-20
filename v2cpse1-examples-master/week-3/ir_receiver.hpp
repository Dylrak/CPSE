#ifndef IR_RECEIVER_HPP
#define IR_RECEIVER_HPP

#include "hwlib.hpp"

namespace target = hwlib::target;
class ir_receiver
{
private:
	target::pin_in & ir_signal;
public:
	ir_receiver( target::pin_in & ir_signal ):
		ir_signal ( ir_signal )
	{}
	bool get() { //Pull-down
		return !ir_signal.get();
	}
};

#endif // IR_RECEIVER_HPP
