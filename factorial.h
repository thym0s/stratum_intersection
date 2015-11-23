template< class IntegerType >
  IntegerType factorial( IntegerType n )
  {
    IntegerType ret = 1;
    while( n > 1 )
    {
      ret *= n;
      --n;
    }
    return ret;
  }

