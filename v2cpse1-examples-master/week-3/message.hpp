#ifndef MESSAGE_HPP
#define MESSAGE_HPP

#include <bitset>
#include "command.hpp"

class message {
public:
	const static uint_fast8_t size = 16;
	uint16_t bits;
	message() {}
	message( uint8_t player_number, uint8_t cmd )
	{ 
		bits = 1 << 15;
		bits |= player_number << 10;
		bits |= cmd << 5;
		add_checksum();
	}
	bool get_bit (uint8_t n) {
		return 1 == ( (bits >> (15 - n)) & 1);
	}
	uint16_t id_number () {
		return (bits & 0b0111110000000000) >> 10;
	}
	uint16_t command () {
		return (bits & 0b0000001111100000) >> 5;
	}
	bool operator==(const message &other) const{
		return bits == other.bits;
	}
	void print () {
		hwlib::cout << hwlib::bin << bits << hwlib::dec << '\n';
	}
private:
	void add_checksum () {
		uint8_t checksum = 0;
		for (uint8_t i = 1; i < 6; i++) {
			checksum <<= 1;
			checksum += (get_bit(i) ^ get_bit (i + 5));
		}
		bits += checksum;
	}
};

#endif // MESSAGE_HPP
