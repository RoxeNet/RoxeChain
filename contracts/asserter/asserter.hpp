/**
 *  @file
 *  @copyright defined in actc/LICENSE.txt
 */

#include <actclib/actc.hpp>

namespace asserter {
   struct assertdef {
      int8_t      condition;
      std::string message;

      actcLIB_SERIALIZE( assertdef, (condition)(message) )
   };
}
