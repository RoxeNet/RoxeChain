#include <actclib/actc.hpp>
#include <actclib/print.hpp>
using namespace actc;

class payloadless : public actc::contract {
  public:
      using contract::contract;

      void doit() {
         print( "Im a payloadless action" );
      }
};

actc_ABI( payloadless, (doit) )
