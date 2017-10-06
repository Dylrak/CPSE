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

bool is_digit(char c);
bool is_lowercase(char c);

void play(player & lsp, const char *s );

#endif // BASE_PLAYER_HPP
