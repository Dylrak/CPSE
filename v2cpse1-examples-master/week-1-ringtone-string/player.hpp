#include "base_player.hpp"
#include "hwlib.hpp"

// ===========================================================================
//
// simple note player for a speaker connected to a GPIO pin
//
// ===========================================================================

class lsp_player : public player {
private:   
   hwlib::pin_out & lsp;
public: 
   lsp_player( hwlib::pin_out & lsp ):
      lsp( lsp )
   {}
   
   void play( const note & n ) override {
      if( n.frequency == 0 ){
         hwlib::wait_us( n.duration );
      } else {
         auto end = hwlib::now_us() + n.duration;
         auto half_period = 1'000'000 / ( 2 * n.frequency );    
         while( end > hwlib::now_us() ){
            lsp.set( 1 );
            hwlib::wait_us( half_period );
            lsp.set( 0 );
            hwlib::wait_us( half_period );
         }
      }     
   }
};