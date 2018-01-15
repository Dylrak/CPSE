#ifndef MSG_DECODER_HPP
#define MSG_DECODER_HPP

#include "pause_detector.hpp"
#include "message.hpp"

#define CONTROLBIT 11
#define MARGIN 200
#define BREAK 3000
#define TIMEOUT 4000
#define THRESHOLD 1200

class msg_listener
{
public:
	virtual void msg_received( message msg ) = 0;
};

namespace target = hwlib::target;

class msg_decoder : public rtos::task<>, public pause_listener
{
private:
	enum class states { idle, read_message };
	states state;

	message prev_msg;
	message msg;
	uint_fast8_t bit_counter;
	msg_listener & ml;

	rtos::channel< uint_least16_t, 10 > pauses;

	void reset() {
		msg.bits = 0;
		prev_msg.bits = 0;
		bit_counter = 0;
	}

//	void authenticate() { //Authenticates the current message and compares to prev_message if available.
//		//If message is authenticated it is sent to the channel via message interface.
//		uint_fast8_t bit_1 = 1, bit_2 = 6;
//		bool correct = true;
//		for (uint_fast8_t i = CONTROLBIT; i < msg.size; i++) {
//			if (msg.get_bit(i) != (msg.get_bit(bit_1++) ^ msg.get_bit(bit_2++))) { //If bit 1 & 6 are NOT the XOR of bit 11, the message is incorrect. Repeat for 2, 7 & 12 etc.
//				correct = false;
//				break;
//			}
//		}
//		if (correct) {
//			if (prev_msg.get_bit(0) == 1) { //If prev_msg is full (indicated by prev_msg[0] == 1) compare both messages.
//				if (msg.bits == prev_msg.bits) { //If they match, send message to message listener channel.
//					ml.msg_received(msg);
//				}
//				reset();
//			} //Else, wait for break between messages to flush msg to prev_msg
//		} else {
//			reset();
//		}
//	}

	void main() {
		for (;;) {
			wait (pauses);
			auto pause_length = pauses.read();
			if (pause_length >= BREAK - MARGIN ) {
				if (pause_length >= TIMEOUT - MARGIN) {
					reset();
				} else { //if the pause length is between 3000-4000 us, we are having a break between two messages. Flush msg to prev_msg and reset bit_counter.
					prev_msg.bits = msg.bits;
					bit_counter = 0;
				}
			} else {
				bool bit = pause_length < THRESHOLD;
				if (bit_counter == 0) {
					if (bit == 1) { msg.bits = bit; bit_counter++; }
				} else {
					msg.bits <<= 1;
					msg.bits += bit;
					if (++bit_counter > 15) {
//						authenticate();
						ml.msg_received(msg);
					}
				}
			}
		}
	}

public:
	msg_decoder( msg_listener & ml ):
		task ("msg decoder"),
		ml ( ml ),
		pauses ( this, "pauses" )
	{
		msg = message();
		prev_msg = message();
	}
	
	void pause_detected( uint_fast64_t & length ) override {
		pauses.write ( length );
	}
};

#endif // MSG_DECODER_HPP
