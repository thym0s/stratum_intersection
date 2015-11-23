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
  
  auto m1 = lift_stratum( b1 );
  auto m2 = lift_stratum( b2 );
  auto m3 = lift_stratum( b3 );
  auto m4 = lift_stratum( b4 );

  stratum_polynomial_t p1 ( m1 );
  stratum_polynomial_t p2 ( m2 );
  stratum_polynomial_t p3 ( m3 );
  stratum_polynomial_t p4 ( m4 );

  stratum_polynomial_t r1 = p1 + p2 + p4 + p4;
  stratum_polynomial_t r2 = p1 * p2;
  stratum_polynomial_t r3 = p1 * p3;
  stratum_polynomial_t r4 = p1 * ( p2 + p4 );

  std::cout << "p1 = " << p1 << '\n';
  std::cout << "p2 = " << p2 << '\n';
  std::cout << "p3 = " << p3 << '\n';
  std::cout << "p4 = " << p4 << '\n';

  std::cout << "p1 + p2 + p4 + p4 = " << r1 << '\n';
  std::cout << "p1 * p2           = " << r2 << '\n';
  std::cout << "p1 * p3           = " << r3 << '\n';
  std::cout << "p1 * ( p2 + p4 )  = " << r4 << '\n';
  return 0;
}

