#ifndef MELODY_HPP
#define MELODY_HPP

#include "player.hpp"

class melody {
public:
   virtual void play( player & p );
};

class fur_elise : public melody {
public:
   void play( player & p ){
      p.play( note{ note::E5,  note::dQ } );
      p.play( note{ note::D5s, note::dQ } );
      p.play( note{ note::E5,  note::dQ } ); 
      p.play( note{ note::D5s, note::dQ } ); 
      p.play( note{ note::E5,  note::dQ } );
      p.play( note{ note::B4,  note::dQ } );
      p.play( note{ note::D5,  note::dQ } );
      p.play( note{ note::C5,  note::dQ } );
      p.play( note{ note::A4,  note::dH } );
    }
};

class pc_melody : public melody {
public:
	void play (player & p);
};

#endif // MELODY_HPP
