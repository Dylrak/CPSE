#include "hwlib.hpp"
#include "message.hpp"

#define CAPS 32

extern "C" void uart_put_char( char c ){
   hwlib::cout << c;
}

extern "C" void print_asciz( const char * s );

extern "C" void application( const char * s );

extern "C" char capsify( char c );

int main( void ){
    
   // kill the watchdog
   WDT->WDT_MR = WDT_MR_WDDIS;
   
   namespace target = hwlib::target;   
    
      // wait for the PC console to start
   hwlib::wait_ms( 500 );

   application( "Hello world, the ANSWER is 42!\n" );
}