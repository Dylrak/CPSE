#include "hwlib.hpp"
#include <algorithm>

//sinus
constexpr double pow( double base, int exponent){
    if (exponent == 0) return 1;
    double temp = pow(base, exponent/2);
    if (exponent % 2 == 0)
        return temp * temp; 
    else
        return (base * temp * temp);
}

constexpr double fac( int n ){
   double result = 1;
   while( n > 0 ){
       result *= n;
       --n;
   }
   return result;
}

constexpr double sin( double x ){
    double y = x;
    double s = -1;
    for (int i=3; i<=50; i+=2) {
        y+=s*(pow(x,i)/fac(i));
        s *= -1;
    }  
    return y;
}

constexpr double cos( double x ){
    double y = 1;
    double s = -1;
    for (int i=2; i<=50; i+=2) {
        y+=s*(pow(x,i)/fac(i));
        s *= -1;
    }  
    return y;
}

constexpr double radians_from_degrees( int degrees ){
   return degrees * 3.14 / 180.0;
}

template<typename T, int N>
class lookup{
private:
    T values[N];
public:
    template<typename F>
    constexpr lookup(F function){
        for (int i = 0; i < N; ++i){
            values[i] = function(i);
        }
    }
    constexpr T get(int n) const {
        return values[n];
    }
};

//oled
namespace target = hwlib::target;

namespace hwlib {
   class pin_fixed {
   public:    
      pin_fixed( pin_out & pin, bool v ){
         pin.set( v );
      } 
   };
};

   // The OLED display is connected in a very funny way:
   // the I2C pins are reversed, and two GPIO pins are
   // (mis-) used as ground and power for the display.
   // This works, and makes it very easy to connect the LCD,
   // but don't take this as an advice to connect peripherals is this way
   // unless you know very well what you are doing.
class oled_buffered_d18_d21 {
   target::pin_oc scl, sda;
   hwlib::i2c_bus_bit_banged_scl_sda i2c_bus;
   target::pin_out pin_gnd, pin_vcc;
   hwlib::pin_fixed pin_gnd_fixed, pin_vcc_fixed;
   
public:
   hwlib::glcd_oled_buffered oled;

   oled_buffered_d18_d21():
      scl( target::pins::sda ),
      sda( target::pins::scl ),
      i2c_bus( scl, sda ),
      pin_gnd( target::pins::d18 ),
      pin_vcc( target::pins::d19 ),
      pin_gnd_fixed( pin_gnd, 0 ),
      pin_vcc_fixed( pin_vcc, 1 ),
      oled( i2c_bus, 0x3c )
   {}   
};

namespace hwlib {
   constexpr location operator/( const location & lhs, int rhs ){
      return location( lhs.x / rhs, lhs.y / rhs );
   }
}

constexpr hwlib::location square( const hwlib::location & lhs ){
   auto m = std::min( lhs.x, lhs.y );
   return hwlib::location( m, m );
}

constexpr hwlib::location get_location(int deg, double radius, auto sinusses, auto cosinusses) {
    deg %= 360;
    if (deg >= 0 && deg < 45) {
        return hwlib::location(sinusses.get(deg%45) * radius, -cosinusses.get(deg%45) * radius);
    } else if (deg >= 45 && deg < 90) {
        return hwlib::location(cosinusses.get(44-deg%45) * radius, -sinusses.get(44-deg%45) * radius);
    } else if (deg >= 90 && deg < 135) {
        return hwlib::location(cosinusses.get(deg%45) * radius, sinusses.get(deg%45) * radius);
    } else if (deg >= 135 && deg < 180) {
        return hwlib::location(sinusses.get(44-deg%45) * radius, cosinusses.get(44-deg%45) * radius);
    } else if (deg >= 180 && deg < 225) {
        return hwlib::location(-sinusses.get(deg%45) * radius, cosinusses.get(deg%45) * radius);
    } else if (deg >= 225 && deg < 270) {
        return hwlib::location(-cosinusses.get(44-deg%45) * radius, sinusses.get(44-deg%45) * radius);
    } else if (deg >= 270 && deg < 315) {
        return hwlib::location(-cosinusses.get(deg%45) * radius, -sinusses.get(deg%45) * radius);
    } else if (deg >= 315 && deg < 360) {
        return hwlib::location(-sinusses.get(44 - deg%45) * radius, -cosinusses.get(44 - deg%45) * radius);
    }
    return hwlib::location(0, 0);
}
/*
constexpr hwlib::line make_line(int deg, double radius, hwlib::location middle, auto sinusses, auto cosinusses) {
    deg %= 360;
    if (deg >= 0 && deg < 45) {
        return hwlib::line(middle, middle - hwlib::location(-sinusses.get(deg%45) * radius, cosinusses.get(deg%45) * radius));
    } else if (deg >= 45 && deg < 90) {
        return hwlib::line(middle, middle - hwlib::location(-cosinusses.get(44-deg%45) * radius, sinusses.get(44-deg%45) * radius));
    } else if (deg >= 90 && deg < 135) {
        return hwlib::line(middle, middle + hwlib::location(cosinusses.get(deg%45) * radius, sinusses.get(deg%45) * radius));
    } else if (deg >= 135 && deg < 180) {
        return hwlib::line(middle, middle + hwlib::location(sinusses.get(44-deg%45) * radius, cosinusses.get(44-deg%45) * radius));
    } else if (deg >= 180 && deg < 225) {
        return hwlib::line(middle, middle + hwlib::location(-sinusses.get(deg%45) * radius, cosinusses.get(deg%45) * radius));
    } else if (deg >= 225 && deg < 270) {
        return hwlib::line(middle, middle + hwlib::location(-cosinusses.get(44-deg%45) * radius, sinusses.get(44-deg%45) * radius));
    } else if (deg >= 270 && deg < 315) {
        return hwlib::line(middle, middle - hwlib::location(cosinusses.get(deg%45) * radius, sinusses.get(deg%45) * radius));
    } else if (deg >= 315 && deg < 360) {
        return hwlib::line(middle, middle - hwlib::location(sinusses.get(44 - deg%45) * radius, cosinusses.get(44 - deg%45) * radius));
    }
    return hwlib::line(middle, middle);
}
*/
int main( void ){	
   WDT->WDT_MR = WDT_MR_WDDIS;
   namespace target = hwlib::target;   
   hwlib::wait_ms( 500 );
   
   auto hw     = oled_buffered_d18_d21();
   auto & oled = hw.oled;
   double radius = square( oled.size ).x / 2 - 5;
   hwlib::location middle = oled.size / 2;
   auto sinusses = lookup<double, 45>(
    [](int x)-> double {return sin( radians_from_degrees( x )); }
   );
   auto cosinusses = lookup<double, 45>(
    [](int x)-> double {return cos( radians_from_degrees( x )); }
   );
   int second = 0;
   int minute = 0;
   int hour = 0;
   auto const usecond = 1'000'000;
   auto correction_time = hwlib::now_us();
   for (;;) {
       if (second >= 60) {
           second = 0;
           minute++;
           if (minute >= 60) {
               minute = 0;
               hour++;
               if (hour >= 12) {
                   hour = 0;
               }
           }
       }
       oled.clear();
       //make_line(second * 6, radius, middle, sinusses, cosinusses).draw(oled);
       hwlib::line(middle, middle + get_location(second * 6, radius*0.5, sinusses, cosinusses)).draw(oled);
       hwlib::line(middle, middle + get_location(minute * 6, radius*0.95, sinusses, cosinusses)).draw(oled);
       hwlib::line(middle, middle + get_location((hour + minute/60.0) * 30, radius*0.75, sinusses, cosinusses)).draw(oled);
       for (int i = 0; i < 360; i += 30) {
           hwlib::circle( middle + get_location(i, radius, sinusses, cosinusses), 2 ).draw( oled );
       }
       oled.flush();
       if (correction_time + usecond <= hwlib::now_us()) {
           correction_time = hwlib::now_us() + (hwlib::now_us() - usecond - correction_time);
           second++;
       }
   }
}
