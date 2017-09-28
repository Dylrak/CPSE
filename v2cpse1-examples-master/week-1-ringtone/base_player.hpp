#ifndef BASE_PLAYER_HPP
#define BASE_PLAYER_HPP

#include "note.hpp"

// ===========================================================================
//
// interface for a note player
//
// ===========================================================================

class player {
public:   
   virtual void play( const note & n ) = 0;
};

#endif // BASE_PLAYER_HPP
