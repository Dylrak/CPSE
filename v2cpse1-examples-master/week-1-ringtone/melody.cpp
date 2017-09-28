#include "melody.hpp"

class pc_melody : public melody {
public:
	void play( player & p ) {
		p.play( note{ note::E5,  note::dQ } );
	}
};