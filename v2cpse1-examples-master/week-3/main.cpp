#include "msg_decoder.hpp"

int main( void ){
	auto signal = target::pin_in( target::pins::d7 );
	auto irr = ir_receiver( signal );

	auto msgl = msg_logger();
	auto msgd = msg_decoder( msgl );
	auto pd = pause_detector ( irr, msgd );

	rtos::run();
}
