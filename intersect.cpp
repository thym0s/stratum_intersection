#include "stratum.h"
#include "polynomial.h"

#include <iostream>

int main( int argc, const char ** argv )
{
  std::vector< unsigned long > v1 { 1 , 2 , 3 , 1 , 1 };
  std::vector< unsigned long > v2 { 1 , 1 , 1 , 3 , 1 , 1 };
  std::vector< unsigned long > v3 { 3 , 3 , 1 , 1 };
  std::vector< unsigned long > v4 { 3 , 2 , 1 , 1 , 1 };

  base_stratum b1( v1 );
  base_stratum b2( v2 );
  base_stratum b3( v3 );
  base_stratum b4( v4 );
  
  monomial< typename boost::rational< unsigned long > , base_stratum > m1( 2 , b1 );
  monomial< typename boost::rational< unsigned long > , base_stratum > m2( 2 , b2 );
  monomial< typename boost::rational< unsigned long > , base_stratum > m3( 2 , b3 );
  monomial< typename boost::rational< unsigned long > , base_stratum > m4( 2 , b4 );

  polynomial< typename boost::rational< unsigned long > , base_stratum > p1( m1 );
  polynomial< typename boost::rational< unsigned long > , base_stratum > p2( m2 );
  polynomial< typename boost::rational< unsigned long > , base_stratum > p3( m3 );
  polynomial< typename boost::rational< unsigned long > , base_stratum > p4( m4 );

  polynomial< typename boost::rational< unsigned long > , base_stratum > p;
  p = p1 + p4 + p3 + p4;

  std::cout << p << '\n';
  return 0;
}

