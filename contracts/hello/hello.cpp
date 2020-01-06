#include <actclib/actc.hpp>
using namespace actc;

class hello : public actc::contract {
  public:
      using contract::contract;

      /// @abi action 
      void hi( account_name user ) {
         print( "Hello, ", name{user} );
      }
};

actc_ABI( hello, (hi) )
