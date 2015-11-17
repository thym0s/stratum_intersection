#include "stratum.h"

#include <numeric>
#include <string>
#include <cassert>

/**
  Implementation base_stratum
*/

base_stratum::base_stratum()
  : data_()
{
}

base_stratum::base_stratum( const data_t & d )
  : data_( d )
{
  sort();
}

void base_stratum::sort()
{
  std::sort( data_.begin() , data_.end() , std::greater< unsigned long >() );
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
  ret.push_back( '(' );

  std::for_each( b.data_.begin() , b.data_.end() ,
    [&ret]( unsigned long n )
    {
      ret.append( std::to_string( n ) );
      ret.push_back( ',' );
    }
  );

  if( 1 != ret.size() )
  {
    ret.pop_back();
  }
  ret.push_back( ')' );

  os << ret;

  return os;
}

/**
  Implementation stratum
*/

stratum::stratum()
  : data_()
{
}

void stratum::apply_permutation( const permutation_t & p )
{
  assert( p.size() == data_.size() );

  data_t new_data;

  std::for_each( p.begin() , p.end() ,
    [&new_data,this]( unsigned long i )
    {
      new_data.push_back( data_[i] );
    }
  );

  data_ = new_data;

  make_representative_canonical();
}

bool stratum::is_trivial() const
{
  bool ret = true;

  unsigned long i = 0;
  const unsigned long s = data_.size();

  for( ; i != s ; ++i )
  {
    ret &= ( i == data_[i] );
  }

  return ret;
}

void stratum::make_representative_canonical()
{
  unsigned long i = 0;
  const unsigned long s = data_.size();
  data_t replace( s , s );

  // find correct representatives
  for( ; i != s ; ++i )
  {
    replace[ data_[i] ] = std::min< unsigned long >( i , replace[ data_[i] ] );
  }

  //replace
  std::transform( data_.begin() , data_.end() , data_.begin() ,
    [replace]( unsigned long n )
    {
      return replace[n];
    }
  );
}

bool operator==( const stratum & s1 , const stratum & s2 )
{
  bool ret = false;

  if( s1.data_.size() == s2.data_.size() )
  {
    ret = std::equal( s1.data_.begin() , s1.data_.end() , s2.data_.begin() );
  }

  return ret;
}

std::ostream & operator<<( std::ostream & os , const stratum & b )
{
  unsigned long i = 0;
  const unsigned long s = b.data_.size();
  std::vector< stratum::data_t > members( s );
  
  for( ; i != s ; ++i )
  {
    members[ b.data_[i] ].push_back( i );
  }
  
  std::string ret;
  ret.push_back( '(' );

  std::for_each( members.begin() , members.end() ,
    [&ret]( const stratum::data_t & d )
    {
      if( 0 != d.size() )
      {
        std::for_each( d.begin() , d.end() ,
          [&ret]( unsigned long n )
          {
            ret.append( std::to_string( n ) );
            ret.push_back( '=' );
          }
        );

        ret.pop_back();
        ret.push_back( ',' );
      }
    }
  );

  if( 1 != ret.size() )
  {
    ret.pop_back();
  }
  ret.push_back( ')' );

  os << ret;

  return os;
}


