#pragma once

#include <vector>
#include <ostream>
#include <boost/rational.hpp>
#include "polynomial.h"

typedef std::vector< unsigned long > permutation_t;
typedef std::pair< unsigned long , unsigned long > pairing_t;

class base_stratum
{
 public:
  typedef std::vector< unsigned long > data_t;
  base_stratum();
  base_stratum( const data_t & );
  base_stratum( const base_stratum &  ) = default;
  base_stratum(       base_stratum && ) = default;
  ~base_stratum()                       = default;
  base_stratum &
    operator= ( const base_stratum &  ) = default;
  base_stratum &
    operator= (       base_stratum && ) = default;

  data_t data_;
 private:
  void sort();
};

class stratum
{
 public:
  typedef std::vector< unsigned long > data_t;
  stratum();
  stratum    ( const stratum &  ) = default;
  stratum    (       stratum && ) = default;
  ~stratum()                      = default;
  stratum &
    operator=( const stratum &  ) = default;
  stratum &
    operator=(       stratum && ) = default;
  
  void apply_permutation( const permutation_t & );
  bool is_trivial() const;

  data_t data_;
 private:
  void make_representative_canonical();
};

typedef polynomial< typename boost::rational< unsigned long > , stratum >
  stratum_polynomial_t;

bool operator==( const base_stratum & , const base_stratum & );
bool operator==( const stratum & , const stratum & );

std::ostream & operator<<( std::ostream & , const base_stratum & );
std::ostream & operator<<( std::ostream & , const stratum & );

stratum operator*( const permutation_t & , const stratum & );

pairing_t split_pairing( stratum & );
stratum_polynomial_t collapse_pairing( pairing_t , const stratum & );

stratum_polynomial_t operator*( const stratum_polynomial_t & , 
                                const stratum & );
stratum_polynomial_t operator*( const stratum & , const stratum & );

stratum lift_stratum( const base_stratum & );

