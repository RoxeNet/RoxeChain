#include <dcciolib/dccio.hpp>
#include <dcciolib/print.hpp>
using namespace dccio;

class payloadless : public dccio::contract {
  public:
      using contract::contract;

      void doit() {
         print( "Im a payloadless action" );
      }
};

dccIO_ABI( payloadless, (doit) )
