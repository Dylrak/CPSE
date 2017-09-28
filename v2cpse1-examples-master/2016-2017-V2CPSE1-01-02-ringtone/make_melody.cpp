#include <iostream>
#include "player.hpp"

using namespace std;

class pc_player : public player {
private:
	string note_code;
public:
	pc_player () {}
	void play( const note & n ) override {
		note_code.append("	p.play( note{ " + to_string(n.frequency) + ",  " + to_string(n.duration) + " } );\n");
	}
	string get_code () {
		return note_code;
	}
};

int main( int argc, char **argv ){
	auto pc = pc_player();
	play( pc, argv[ 1 ]);
	std::cout
		<< "#include \"melody.hpp\"\n"
		<< "class pc_melody : public melody {\n"
		<< "public:\n"
		<< "	void play( player & p ) {\n"
		<< pc.get_code()
		<< "	}\n};";
}