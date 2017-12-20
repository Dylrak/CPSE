#include <iostream>
#include <fstream>

template< int N >
class lz_decompressor {
private:
    char buffer[N];
    int used;

    // read the input using read() until it returns '\0'
   template< typename F >
   void read_compressed_buffer( F read ){
      used = 0;
      int compressed_offset = -1;
      int compressed_length = -1;
      int compressed_pos = -1;
      bool compressed_char = false;
      for(;;){
         auto c = read();
         //std::cout << used << "[" << (char) c <<  "]\n";
         if( used == N ){
            std::cerr << "read compressed buffer overflow";
            break;
         } else if( c == '\0' ){
            break;
         } else if (compressed_char && compressed_offset == -1) {
             compressed_offset = c - ' ';
             compressed_pos = used - 1;
         } else if (compressed_char && compressed_offset != -1) {
             compressed_length = c - ' ';
             for (int i = 0; i < compressed_length; ++i) {
                 buffer[used] = buffer[compressed_pos - compressed_offset + i];
                 used++;
             }
             compressed_offset = -1;
             compressed_length = -1;
             compressed_pos = -1;
             compressed_char = false;
         } else if( c == '@' ){
            compressed_char = true;
         }  else if (!compressed_char) {
             buffer[ used++ ] = c;
         }
      }         
   }
   
   template< typename F >
   void write_decompressed_buffer( F write ){
      for( int i = 0; i < used; ){
         write( buffer[ i++ ] );
      }
   }
   
public: 
   template< typename D, typename S >
   void decompress( D write, S read ){
      read_compressed_buffer( read );
      write_decompressed_buffer( write ); 
   }
};

// a match found in the previously processed characters:
// the start offset (negative), and the number of characters
struct match {
   
   int offset;
   int length;
   
   match( int offset = 0, int length = 0 ): 
      offset( offset ), length( length ) {}
      
   friend std::ostream & operator<<( std::ostream & lhs, const match & m ){
      return lhs << "[" << m.offset << ";" << m.length << "]";
   }
   
   bool operator<( const match & rhs ) const {
      return length < rhs.length;
   }
};

// A LZ compressor 
// A buffer is used that holds the total message,
// which must be smaller than N
template< int N > 
class lz_compressor {
private:   
   char buffer[ N ];
   int used;
   
   // read the input using read() until it returns '\0'
   template< typename F >
   void read_buffer( F read ){
      used = 0;
      for(;;){
         auto c = read();
         //std::cout << used << "[" << (char) c <<  "]\n";
         if( used == N ){
            std::cerr << "buffer overflow";
            break;
         }
         if( c == '@' ){
            std::cerr << "text contains @";
            break;
         }
         if( c == '\0' ){
            break;
         }
         buffer[ used++ ] = c;
      }         
   }
   
   // return the lenth of the longest identical prefix of s and p
   int count_identical_prefix_length( const char * s, const char * p ){
      return (( *s == '\0' ) || ( *s != *p ))
         ? 0 
         : 1 + count_identical_prefix_length( s + 1, p + 1 );
   }   
   
   // find the best match in the buffer (80 positions back, upto index) 
   // for the string starting at index
   match find( int index ){
      auto best = match( 0 );
      for( int i = std::max( 0, index - 80 ); i < index - 1; ++i ){
         int length = std::min( 
            80, 
            count_identical_prefix_length( buffer + i, buffer + index ));
         best = std::max( best, match( index - i - 1, length ) );
      }
      return best;
   }
   
   template< typename F >
   void write_compressed_buffer( F write ){
      for( int i = 0; i < used; ){
         auto match = find( i );
         if( match.length > 2 ){
            //std::cout << "\ni=" << i << " m=" << match << " ";            
            write( '@' );
            write( ' ' + match.offset );
            write( ' ' + match.length );
            i += match.length;
         } else {
            //std::cout << "\n" << i << " c=[" << buffer[ i ] << "]";
            write( buffer[ i++ ] );
         }
      }
   }
   
public: 
   template< typename D, typename S >
   void compress( D write, S read ){
      read_buffer( read );
      write_compressed_buffer( write ); 
   }
};

int main( void ){	
   lz_compressor< 4096 > compressor;
   lz_decompressor<8192> decompressor;
 
   std::ifstream f1;
   f1.open( "../input.txt" );
   if( ! f1.is_open()){
      std::cerr << "input file not opened";
      return -1;      
   }
   
   std::ofstream f2;
   f2.open( "../compressed.txt" );
   if( ! f2.is_open()){
      std::cerr << "output file not opened";
      return -1;      
   }
   
   compressor.compress( 
      [ &f2 ]( char c ){ f2.put( c ); }, 
      [ &f1 ]()-> int { auto c = f1.get(); return f1.eof() ? '\0' : c; }
   );
   
   f1.close();
   f2.close();
   
   f1.open( "../compressed.txt" );
   if( ! f1.is_open()){
      std::cerr << "input file not opened";
      return -1;      
   }
   
   f2.open( "../output.txt" );
   if( ! f2.is_open()){
      std::cerr << "output file not opened";
      return -1;      
   }
   
   decompressor.decompress( 
      [ &f2 ]( char c ){ f2.put( c ); }, 
      [ &f1 ]()-> int { auto c = f1.get(); return f1.eof() ? '\0' : c; }
   );
   
   f1.close();
   f2.close();
}