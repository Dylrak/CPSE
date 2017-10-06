#include <iostream>
#include <string>
#include <stdio.h>
#include <fstream>
#include "base_player.hpp"

class pc_player : public player {
private:
	std::string note_code;
public:
	pc_player () {}
	void play( const note & n ) override {
		std::string note_line = "	p.play( note{ " + std::to_string(n.frequency) + ", " + std::to_string(n.duration) + " } );\n";
		note_code.append(note_line);
	}
	std::string get_code () {
		return note_code;
	}
};

int main( int argc, char **argv ){

	auto pc = pc_player();
	play( pc, argv[ 1 ]);

	std::cout
		<< "#include \"melody.hpp\"\n"
		<< "void pc_melody::play( player & p ) {\n"
		<< pc.get_code()
		<< "}\n";
}