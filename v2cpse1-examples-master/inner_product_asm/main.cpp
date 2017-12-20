#include <stdio.h>

float inner_product( float a[], float b[], int length ){
   float sum = 0;
   for( int i = 0; i < length ){
      sum += a[ i ] * b[ i ];
   }
   return sum;
}

extern "C" float inner_product_asm ( float a[], float b[], int length );

extern "C" float float_zero = 0.0;
extern "C" float float_multiply ( float a, float b ){ return a * b; }
extern "C" float float_add( float a, float b ){ return a + b; }

int main(int argc, char **argv)
{
	float x[] = { 3.0, 3.0, 3.0 };
	float y[] = { 1.0, 2.0, 3.0 };

	std::cout << inner_product(x, y, 3) << '\n';
	std::cout << inner_product_asm(x, y, 3);
}
