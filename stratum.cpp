#include "stratum.h"

#include <numeric>
#include <string>
#include <sstream>
#include <cassert>
#include <cmath>

#include "factorial.h" 

/**
  Implementation base_stratum
*/

base_stratum::base_stratum()
  : data_()
{
}

base_stratum::base_stratum( const std::vector< unsigned long > & d )
  : data_()
{
  std::for_each( d.begin(), d.end() ,
    [this]( const unsigned long & n )
    {
      if( n >= 2 )
      {
        unsigned long n_minus_two = n - 2;
        if( n_minus_two >= data_.size() )
        {
          data_.resize( n_minus_two + 1 , 0 );
        }
        data_[ n_minus_two ] += 1;
      }
    }
  );
}

bool operator==( const base_stratum & b1 , const base_stratum & b2 )
{
  bool ret = false;

  if( b1.data_.size() == b2.data_.size() )
  {
    ret = std::equal( b1.data_.begin() , b1.data_.end() , b2.data_.begin() );
  }

  return ret;
}

std::ostream & operator<<( std::ostream & os , const base_stratum & b )
{
  std::string ret;
  std::vector< std::string > equal_number_string( b.data_.size() );
  unsigned long i = 0;
  unsigned long j = 0;

  for( ; j != b.data_.size() ; ++j )
  {
    for( i = 0 ; i != b.data_[j] ; ++i )
    {
      equal_number_string[j] += std::to_string( j + 2 );
      equal_number_string[j] += std::string( "," );
    }
  }

  if( j > 0 )
  {
    ret = std::accumulate( equal_number_string.rbegin() ,
                           equal_number_string.rend() ,
                           ret );
    ret.pop_back();
  }

  os << '[' << ret << ']';

  return os;
}

/**
  Implementation stratum
*/

stratum::stratum()
  : data_()
{
}

bool operator==( const stratum & s1 , const stratum & s2 )
{
  return s1.data_ == s2.data_;
}

std::ostream & operator<<( std::ostream & os , const stratum & b )
{
  os << b.data_;

  return os;
}

unsigned long stabilizer( const base_stratum & b )
{
  unsigned long ret( 1 );
  unsigned long i = 0;
  for( ; i != b.data_.size() ; ++i )
  {
    ret *= pow( factorial< unsigned long >( i + 2 ) , b.data_[i] );
  }
  return ret;
}

unsigned long deck_group( const base_stratum & b )
{
  unsigned long ret( 1 );
  std::for_each( b.data_.begin() , b.data_.end() ,
    [&ret]( const unsigned long & n )
    {
      ret *= factorial< unsigned long >( n );
    }
  );
  return ret;
}

unsigned long deck_group( const stratum & b )
{
  return deck_group( b.data_ );
}

stratum_monomial_t lift_stratum( const base_stratum & b )
{
  stratum s;
  s.data_ = b;

  stratum_monomial_t ret(
    boost::rational< signed long >( 1  ) ,
    s );

  return ret;
}

typedef std::vector< unsigned long > permutation_t;
// Is not a permutation ( only injection );
typedef std::tuple< unsigned long , unsigned long , unsigned long > tuple_t;
// type, open, rep
typedef std::vector< unsigned long > ul_v;
typedef std::vector< tuple_t > tuple_v;
typedef std::vector< std::vector< tuple_t > > tuple_vv;

unsigned long stratum_length( const ul_v & d )
{
  unsigned long ret( 0 );
  unsigned long i;
  for( i = 0 ; i != d.size() ; ++i )
  {
    ret += (i+2)*d[i];
  }
  return ret;
}

void fill_availables(       tuple_vv      & availables , 
                      const ul_v          & d2 ,
                      const unsigned long & d1_length )
{
  unsigned long i , j;
  unsigned long next_rep = 0;

  availables.resize( 2 );
  tuple_v next_av;
  for( i = 0 ; i != d2.size() ; ++i )
  {
    for( j = 0 ; j != d2[i] ; ++j )
    {
      next_av.push_back( std::make_tuple( i + 2 , i + 2 , next_rep ) );
      next_rep += ( i + 2 );
    }
    availables.push_back( next_av );
    next_av.clear();
  }

  for( i = 0 ; i != d1_length ; ++i )
  {
    next_av.push_back( std::make_tuple( 1 , 1 , next_rep ) );
    next_rep += 1;
  }

  availables[1] = next_av;
}

void fill_reps( ul_v & reps, const ul_v & d )
{
  unsigned long i , j , k;
  unsigned long next_rep = 0;

  for( i = 0 ; i != d.size() ; ++i )
  {
    for( j = 0 ; j != d[i] ; ++j )
    {
      for( k = 0 ; k != ( i + 2 ) ; ++k )
      {
        reps.push_back( next_rep );
      }
      next_rep += 1;
    }
  }
}

void recursive_resolve_nt( ul_v & non_transversals , 
                           ul_v & sizes ,
                           stratum_polynomial_t & ret ,
                           const boost::rational< signed long > & factor )
{
  unsigned long i = 0,
                j = 0;
  for( ; i != non_transversals.size() ; ++i )
  {
    if( non_transversals[i] != 0 )
    {
      break;
    }
  }

  if( i == non_transversals.size() )
  {
    base_stratum b( sizes );
    auto m = lift_stratum( sizes );
    m = factor * m;
    stratum_polynomial_t p( m );
    ret = ret + p;
  } else {
    for( ; j != sizes.size() ; ++j )
    {
      if( ( sizes[j] > 1 ) && ( j != i ) )
      {
        ul_v next_t = non_transversals;
        ul_v next_s = sizes;
        boost::rational< signed long > next_f = factor;

        next_t[i] += next_t[j];
        next_t[i] -= 1;
        next_t[j] = 0;
        next_s[i] += next_s[j];
        next_s[j] = 0;
        next_f *= boost::rational< signed long >( -sizes[j] , sizes[i] + 1 );
        recursive_resolve_nt( next_t , next_s , ret , next_f );
      }
    }
    {
      ul_v next_t = non_transversals;
      ul_v next_s = sizes;
      boost::rational< signed long > next_f = factor;

      next_t[i] -= 1;
      next_s[i] += 1;
      next_f *= boost::rational< signed long >( -1 , sizes[i] + 1 );
      recursive_resolve_nt( next_t , next_s , ret , next_f );
    }
  }
}

stratum_polynomial_t intersect( const ul_v          & d1 ,
                                const ul_v          & d2 ,
                                const permutation_t & p )
{
  ul_v rep1, rep2;
  fill_reps( rep1 , d1 );
  fill_reps( rep2 , d2 );
  unsigned long l2 = rep2.size();
  rep2.resize( rep2.size() + rep1.size() , 0 );
  std::iota( rep2.begin() + l2 , rep2.end() , l2 );
  ul_v non_transversals( rep2.size() , 0 );;
  ul_v sizes( rep2.size() , 0 );

  stratum_polynomial_t ret;
  
  unsigned long i = 0;

  //Then Intersect: First as many transversal as possible

  for( ; ( i + 1 ) < rep1.size() ; ++i )
  {
    if( rep1[i] == rep1[i+1] ) //collapes
    {
      unsigned long r1 = rep2[p[i]],
                    r2 = rep2[p[i+1]];
      if( r1 == r2 ) //not transversal
      {
        non_transversals[r1] += 1;
      } else { //replace r2 by r1
        std::replace( rep2.begin() , rep2.end() , r2 , r1 );
        non_transversals[r1] += non_transversals[r2];
        non_transversals[r2] = 0;
      }
    }
  }

  for( i = 0 ; i != rep2.size() ; ++i )
  {
    sizes[i] = std::count( rep2.begin() , rep2.end() , i );
  }

  recursive_resolve_nt( non_transversals , sizes , ret , 1 );
  
  return ret;
}

void recurse( tuple_vv & availables ,
              tuple_v & used ,
              permutation_t & p , // changed, but changed back
              unsigned long & choices_left , //same
              const unsigned long & multiplicity , 
              const ul_v & d1 ,
              const ul_v & d2 ,
              stratum_polynomial_t & ret )
{
  if( choices_left == 0 )
  {
    ret = ret 
        + boost::rational< signed long>( multiplicity )
          * intersect( d1 , d2 , p );
  } else {
    --choices_left;
    unsigned long new_multiplicity;
    unsigned long i ;
    for( i = 0 ; i != used.size() ; ++i )
    {
      if( 0 != std::get<1>( used[i] ) )
      {
        p.push_back( std::get<2>( used[i] ) );
        new_multiplicity = multiplicity * std::get<1>( used[i] );
        std::get<2>( used[i] ) += 1;
        std::get<1>( used[i] ) -= 1;
        
        recurse( availables , used ,
                 p , choices_left , new_multiplicity ,
                 d1 , d2 , ret );

        std::get<2>( used[i] ) -= 1;
        std::get<1>( used[i] ) += 1;
        p.pop_back();
      }
    }
    for( i = 0 ; i != availables.size() ; ++i )
    {
      if( 0 != availables[i].size() ) {
        tuple_t taken = *( availables[i].rbegin() );
        availables[i].pop_back();
        assert( std::get<1>( taken ) == i );

        tuple_t changed = taken;
        p.push_back( std::get<2>( changed ) );
        std::get<2>( changed ) += 1;
        std::get<1>( changed ) -= 1;
        used.push_back( changed );

        new_multiplicity = multiplicity * i;
        if( i > 1 )
        {
          new_multiplicity *= ( availables[i].size() + 1 );
        }
        
        recurse( availables , used ,
                 p , choices_left , new_multiplicity ,
                 d1 , d2 , ret );

        used.pop_back();
        availables[i].push_back( taken );
        p.pop_back();
      }
    }

    ++choices_left;
  }
}

void fix_coefficients( stratum_polynomial_t & p , 
                       const unsigned long & w1 ,
                       const unsigned long & w2 )
{
  boost::rational< signed long > w1w2( 1 , w1 * w2 );
  for_each( p.data_.begin() , p.data_.end() ,
    [w1w2]( stratum_monomial_t & m )
    {
      m.coefficient() *= w1w2;
      m.coefficient() 
        *= boost::rational< signed long >( deck_group( m.base() ) );
    }
  );
}
              
stratum_polynomial_t operator*( const stratum & s1 , const stratum & s2 )
{
  stratum_polynomial_t ret;
  const base_stratum::data_t & d1 = s1.data_.data_ ,
                               d2 = s2.data_.data_ ;

  tuple_vv availables;
  tuple_v used;
  /**
    This stores representatives of places;
    availables[i] : tuples with i free choices
    used[i] : tuples with i free choices
  */

  unsigned long d1_length = stratum_length( d1 );
  permutation_t p;
  unsigned long multiplicity = 1;

  fill_availables( availables , d2 , d1_length );

  recurse( availables, used ,
           p , d1_length , multiplicity ,
           d1 , d2 , ret );
  
  fix_coefficients( ret , deck_group( s1 ) , deck_group( s2 ) );
  return ret;
}

