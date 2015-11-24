#include "stratum.h"
#include "polynomial.h"

#include <iostream>

void print_help()
{
  std::cout << "Welcome to intersect." << '\n';
  std::cout << "This tool computes the intersection of two strata in the" << '\n';
  std::cout << "moduli space of (non-projective) abelian differentials" << '\n';
  std::cout << "in terms of other strata." << '\n';
  std::cout << '\n';
  std::cout << "How to use this program:" << '\n';
  std::cout << "Enter two partitions that describe two strata," << '\n';
  std::cout << "e.g. \"3 2 1\" for a stratum with a triple and a double zero. "<< '\n';
  std::cout << "Partitions end with the first \"1\"" << '\n';
  std::cout << '\n';
  std::cout << "To exit this program, enter \"0\"" << '\n';
}

int main( int argc, const char ** argv )
{
  unsigned long in;
  std::vector< unsigned long > v1;
  std::vector< unsigned long > v2;
  base_stratum b1;
  base_stratum b2;
  stratum_monomial_t m1;
  stratum_monomial_t m2;
  stratum_polynomial_t p1;
  stratum_polynomial_t p2;
  stratum_polynomial_t r;

  print_help();

  while( true )
  {
    v1.clear();
    v2.clear();
    std::cout << "Enter partition for first stratum (0 to exit):\n";
    while( ( std::cin >> in ) && ( in > 1 ) ) 
    {
      v1.push_back( in );
    }
    if( in == 0 )
    {
      break;
    }

    std::cout << "Enter partition for second stratum (0 to exit):\n";
    while( ( std::cin >> in ) && ( in > 1 ) ) 
    {
      v2.push_back( in );
    }
    if( in == 0 )
    {
      break;
    }

    b1 = base_stratum( v1 );
    b2 = base_stratum( v2 );
  
    m1 = lift_stratum( b1 );
    m2 = lift_stratum( b2 );

    p1 = stratum_polynomial_t( m1 );
    p2 = stratum_polynomial_t( m2 );

    r = p1 * p2;

    std::cout << "     p1 = " << p1 << '\n';
    std::cout << "     p2 = " << p2 << '\n';

    std::cout << "p1 * p2 = " << r << '\n';
  }

  return 0;
}

