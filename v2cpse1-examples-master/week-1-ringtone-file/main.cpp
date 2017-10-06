#include "hwlib.hpp"
#include "melody.hpp"

// ===========================================================================
//
// main: play an rtttl string
//
// ===========================================================================   

int main( void ){	
    
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
   namespace target = hwlib::target;
    
      // wait for the PC console to start
   hwlib::wait_ms( 500 );

   auto lsp = target::pin_out( target::pins::d7 );
   auto p = lsp_player( lsp );
	auto pc = pc_melody();
	pc.play( p );
}