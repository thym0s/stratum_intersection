#pragma once

#include <vector>
#include <ostream>
#include <boost/rational.hpp>
#include "polynomial.h"

class base_stratum;
class stratum;

typedef monomial< typename boost::rational< signed long > , stratum >
  stratum_monomial_t;
typedef polynomial< typename boost::rational< signed long > , stratum >
  stratum_polynomial_t;

class base_stratum
{
 public:
  base_stratum();
  base_stratum( const std::vector< unsigned long > & );
  base_stratum( const base_stratum &  ) = default;
  base_stratum(       base_stratum && ) = default;
  ~base_stratum()                       = default;
  base_stratum &
    operator= ( const base_stratum &  ) = default;
  base_stratum &
    operator= (       base_stratum && ) = default;

  friend bool operator==( const base_stratum & , const base_stratum & );
  friend std::ostream & operator<<( std::ostream & , const base_stratum & );
  friend stratum_monomial_t lift_stratum( const base_stratum & );
  friend stratum_polynomial_t operator*( const stratum & , const stratum & );

  friend unsigned long stabilizer( const base_stratum & );
  friend unsigned long deck_group( const base_stratum & );

protected:
  /**
    internal data representation is as follows:
    A vector (a,b,c,...) means:
    a double zeroes, b triple zeroes ...

    the last entry has to be nonzero
  */
  typedef std::vector< unsigned long > data_t;
  
  data_t data_;
};

class stratum
{
 public:
  stratum();
  stratum    ( const stratum &  ) = default;
  stratum    (       stratum && ) = default;
  ~stratum()                      = default;
  stratum &
    operator=( const stratum &  ) = default;
  stratum &
    operator=(       stratum && ) = default;

  friend bool operator==( const stratum & , const stratum & );
  friend std::ostream & operator<<( std::ostream & , const stratum & );
  friend stratum_monomial_t lift_stratum( const base_stratum & );
  friend stratum_polynomial_t operator*( const stratum & , const stratum & );

 protected:
  base_stratum data_;
};

bool operator==( const base_stratum & , const base_stratum & );
bool operator==( const stratum & , const stratum & );

std::ostream & operator<<( std::ostream & , const base_stratum & );
std::ostream & operator<<( std::ostream & , const stratum & );

unsigned long stabilizer( const stratum & );
unsigned long deck_group( const stratum & );

stratum_monomial_t lift_stratum( const base_stratum & );
stratum_polynomial_t operator*( const stratum & , const stratum & );

