#ifndef MSG_LOGGER_HPP
#define MSG_LOGGER_HPP

#include "msg_decoder.hpp"

class msg_logger : public rtos::task<>, public msg_listener {
private:
	rtos::channel< message, 10 > messages;
	void main() {
		for (;;) {
			message msg = messages.read();
			msg.print();
		}
	}
public:
	msg_logger():
		messages ( this, "messages")
	{}
	void msg_received(message msg) override {
		messages.write( msg );
	}
}

#endif //MSG_LOGGER_HPP