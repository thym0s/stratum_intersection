#pragma once

#include <vector>
#include <utility>
#include <algorithm>
#include <functional>
#include <ostream>
#include <sstream>
#include <string>


template<
  class CoefficientType,
  class BaseType 
>
class graded_algebra
{
 public:
  class monomial;
  class element;
  typedef CoefficientType coef_type;
  typedef        BaseType base_type;

  class monomial
  {
   public:
    typedef                   CoefficientType     coefficient_type;
    typedef                          BaseType            base_type;
    typedef graded_algebra  graded_algebra_type;
    typedef         graded_algebra_type::element         element_type;

                monomial    (                   );
                monomial    ( const   coef_type &  ,
                              const   base_type &  );
                monomial    ( const monomial &  ) = default;
                monomial    (       monomial && ) = default;
               ~monomial    (                   ) = default;
    monomial  & operator=   ( const monomial &  ) = default;
    monomial  & operator=   (       monomial && ) = default;

    coefficient_type      coefficient (                   ) const;
    coefficient_type    & coefficient (                   );
    base_type      base        (                   ) const;
    base_type    & base        (                   );

    element_type   el          (                   ) const;
    monomial  & operator*=  ( const   coef_type &  );

   protected:
    typedef std::pair< coefficient_type , base_type > data_type;
    data_type data_;
  };
  
  class element
  {
   public:
    typedef                   CoefficientType            coef_type;
    typedef                          BaseType            base_type;
    typedef graded_algebra  graded_algebra_type;
    typedef        graded_algebra_type::monomial        monomial_type;

    typedef         std::vector< monomial_type >            data_type;
    typedef       data_type::iterator               iterator  ;
    typedef       data_type::const_iterator               const_iterator  ;
    typedef       data_type::reverse_iterator               reverse_iterator  ;
    typedef       data_type::const_reverse_iterator  const_reverse_iterator;
    typedef data_type::size_type size_type;

                element    (                     );
                element    ( const monomial_type &  );
                element    ( const element    &  ) = default;
                element    (       element    && ) = default;
               ~element    (                     ) = default;
    element  & operator=   ( const element    &  ) = default;
    element  & operator=   (       element    && ) = default;

    element  & operator+=  ( const  element &  );
    element  & operator-=  ( const element &  );
    element  & operator*=  ( const element &  );
    element  & operator*=  ( const   coef_type &  );
  
//begin, end, rbegin, rend, size               
   protected:
    data_type data_;
   private:
    void make_monomials_unique();
  }
  //This class has no instances
  ~graded_algebra() = delete; 
};

template<
  class CoefficientType,
  class BaseType 
>
  class monomial
  {
   public:
    monomial();
    monomial( const CoefficientType & , const BaseType & );
    monomial   ( const monomial &  ) = default;
    monomial   (       monomial && ) = default;
    ~monomial  ()                    = default;
    monomial &
      operator=( const monomial &  ) = default;
    monomial &
      operator=(       monomial && ) = default;
  
    CoefficientType   coefficient() const;
    CoefficientType & coefficient();
    BaseType          base() const;
    BaseType &        base();

   protected:
    typedef std::pair< CoefficientType , BaseType > data_t;
    data_t data_;
  };
 
template<
  class CoefficientType,
  class BaseType
>
  class polynomial
  {
   public:
    typedef monomial< CoefficientType , BaseType > monomial_t;

    polynomial();
    polynomial( const monomial_t & );
    polynomial ( const polynomial &  ) = default;
    polynomial (       polynomial && ) = default;
    ~polynomial()                      = default;
    polynomial &
      operator=( const polynomial &  ) = default;
    polynomial &
      operator=(       polynomial && ) = default;

    typedef std::vector< monomial_t > data_t;
    data_t data_;

    void make_monomials_unique();
  };

template< class C , class B >
  bool operator==( const monomial<C,B> & , const monomial<C,B> & );
template< class C , class B >
  bool is_zero( const monomial<C,B> & );
template< class C , class B >
  monomial<C,B> operator*( const C & , const monomial<C,B> & ); 
template< class C , class B >
  polynomial<C,B> operator*( const monomial<C,B> & ,
                             const monomial<C,B> & );

template< class C , class B >
  bool operator==( const polynomial<C,B> & , const polynomial<C,B> & );
template< class C , class B >
  polynomial<C,B> operator*( const C & , const polynomial<C,B> & ); 
template< class C , class B >
  polynomial<C,B> operator+( const polynomial<C,B> & ,
                             const polynomial<C,B> & );
template< class C , class B >
  polynomial<C,B> operator-( const polynomial<C,B> & ,
                             const polynomial<C,B> & );
template< class C , class B >
  polynomial<C,B> operator*( const polynomial<C,B> & ,
                             const polynomial<C,B> & );

template< class C , class B >
  std::ostream & operator<<( std::ostream & , const monomial<C,B> );
template< class C , class B >
  std::ostream & operator<<( std::ostream & , const polynomial<C,B> );

/**
  More graded_algebra::monomial interface
*/

template< class C , class B >
  graded_algebra<C,B>::monomial & make_monomial
  (
    const C & ,
    const B &
  );

template< class C , class B >
  graded_algebra<C,B>::monomial & operator+
  (
    const graded_algebra<C,B>::monomial &
  );

template< class C , class B >
  graded_algebra<C,B>::monomial & operator-
  (
    const graded_algebra<C,B>::monomial &
  );

template< class C , class B >
  graded_algebra<C,B>::monomial & operator*
  (
    const                             C & ,
    const graded_algebra<C,B>::monomial &
  );

template< class C , class B >
  graded_algebra<C,B>::monomial & operator*
  (
    const graded_algebra<C,B>::monomial & ,
    const                             C &
  );

template< class C , class B >
  bool operator==
  (
    const graded_algebra<C,B>::monomial & ,
    const graded_algebra<C,B>::monomial &
  );

template< class C , class B >
  bool operator!=
  (
    const graded_algebra<C,B>::monomial & ,
    const graded_algebra<C,B>::monomial &
  );

template< class C , class B >
  bool evaluate_equal
  (
    const graded_algebra<C,B>::monomial & ,
    const graded_algebra<C,B>::monomial & 
  );

template< class C , class B >
  bool evaluate_not_equal
  (
    const graded_algebra<C,B>::monomial & ,
    const graded_algebra<C,B>::monomial & 
  );

template< class C , class B >
  std::ostream & operator<<
  (
                           std::ostream & ,
    const graded_algebra<C,B>::monomial &
  );

/**
  More graded_algebra::element interface
*/
 //sort, u* u- + - * * *, == !=, <<

/**
  Implementation monomial
*/ 

template< class C , class B >
  monomial<C,B>::monomial()
    : data_()
  {
  }

template< class C , class B >
  monomial<C,B>::monomial( const C & c , const B & b )
    : data_( c , b )
  {
  }

template< class C , class B >
  C monomial<C,B>::coefficient() const
  {
    return data_.first;
  }

template< class C , class B >
  C & monomial<C,B>::coefficient()
  {
    return data_.first;
  }

template< class C , class B >
  B monomial<C,B>::base() const
  {
    return data_.second;
  }

template< class C , class B >
  B & monomial<C,B>::base()
  {
    return data_.second;
  }

template< class C , class B >
  bool operator==( const monomial<C,B> & a , const monomial<C,B> & b )
  {
    bool ret = true;
    const C c1 = a.coefficient();
    const C c2 = b.coefficient();
    if( ( C( 0 ) != c1 ) && ( c1 == c2 ) )
    {
      ret = ( a.base() == b.base() );
    }
    return ret;
  } 

template< class C , class B >
  bool is_zero( const monomial<C,B> & m )
  {
    return m.coefficient() == C( 0 );
  }

template< class C , class B >
  monomial<C,B> operator*( const C & a , const monomial<C,B> & b )
  {
    monomial<C,B> ret( b );
    ret.coefficient() *= a;
    return ret;
  }

template< class C , class B >
  polynomial<C,B> operator*( const monomial<C,B> & a ,
                             const monomial<C,B> & b )
  {
    return ( a.coefficient() * b.coefficient() ) * ( a.base() * b.base() );
  }

template< class C , class B >
  std::ostream & operator<<( std::ostream & os , const monomial<C,B> m )
  {
    os << m.coefficient() << ' ' << m.base();
    return os;
  }

/**
  Implementation polynomial
*/

template< class C , class B >
  polynomial<C,B>::polynomial()
    : data_()
  {
  }

template< class C , class B >
  polynomial<C,B>::polynomial( const monomial_t & m )
    : data_()
  {
    data_.push_back( m );
  }

template< class C , class B >
  void polynomial<C,B>::make_monomials_unique()
  {
    typename data_t::iterator       i = data_.begin(),
                                    j = data_.begin();
    typename data_t::iterator const e = data_.end();

    // Accumulate all coefficients on first occurence of base
    for( ; i != e ; ++i )
    {
      for( j = data_.begin() ; j != i ; ++j ) 
      {
        if( i->base() == j->base() )
        {
          j->coefficient() += i->coefficient();
          i->coefficient() = 0;
          break;
        }
      }
    }

    // Delete all zero monomials
    
    i = data_.begin();
    j = std::remove_if( i , e , 
      []( const monomial_t & m )
      {
        return is_zero( m );
      }
    );
    data_.erase( j , e );
  }

template< class C , class B >
  polynomial<C,B> operator*( const C & a , const polynomial<C,B> & b )
  {
    polynomial<C,B> ret;
  
    if( C( 0 ) != a )
    {
      ret = b;
      std::for_each( ret.data_.begin() , ret.data_.end() ,
        [a]( typename polynomial<C,B>::monomial_t & m )
        {
          m = a * m;
        }
      );
    }

    return ret;
  }

template< class C , class B >
  polynomial<C,B> operator+( const polynomial<C,B> & a ,
                             const polynomial<C,B> & b )
  {
    polynomial<C,B> ret( a );
    ret.data_.insert( ret.data_.end() , b.data_.begin() , b.data_.end() );
    ret.make_monomials_unique();
    return ret;
  }

template< class C , class B >
  polynomial<C,B> operator-( const polynomial<C,B> & a ,
                             const polynomial<C,B> & b )
  {
    return a + ( (-1) * b );
  }

template< class C , class B >
  polynomial<C,B> operator*( const polynomial<C,B> & a ,
                             const polynomial<C,B> & b )
  {
    polynomial<C,B> ret;
    typename polynomial<C,B>::data_t::const_iterator i1 = a.data_.begin(),
                                                     i2 = b.data_.begin(),
                                                     e1 = a.data_.end(),
                                                     e2 = b.data_.end();
    polynomial<C,B> p;

    for( ; i1 != e1 ; ++i1 )
    {
      for( ; i2 != e2 ; ++i2 )
      {
        p = *i1 * *i2;
        ret.data_.insert( ret.data_.end() , 
                            p.data_.begin() ,
                            p.data_.end() );
      }
    }

    ret.make_monomials_unique();
    return ret;
  }

template< class C , class B >
  std::ostream & operator<<( std::ostream & os , const polynomial<C,B> p )
  {
    std::string ret;
    std::stringstream ret_stream;

    std::for_each( p.data_.begin() , p.data_.end() ,
      [&ret_stream]( const monomial<C,B> & m )
      {
        ret_stream << m << " + ";
      }
    );

    ret = ret_stream.str();

    if( 0 != ret.size() )
    {
      ret.erase( ret.size() - 3 );
    }

    os << ret;

    return os;
  }

