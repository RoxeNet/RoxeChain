/**
 *  @file
 *  @copyright defined in dcc/LICENSE.txt
 */

#include <dcciolib/dccio.hpp>

namespace asserter {
   struct assertdef {
      int8_t      condition;
      std::string message;

      dccLIB_SERIALIZE( assertdef, (condition)(message) )
   };
}
