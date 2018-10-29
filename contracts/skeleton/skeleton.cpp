#include <dcciolib/dccio.hpp>

using namespace dccio;

class hello : public dccio::contract {
  public:
      using contract::contract;

      /// @abi action 
      void hi( account_name user ) {
         print( "Hello, ", name{user} );
      }
};

dccIO_ABI( hello, (hi) )
