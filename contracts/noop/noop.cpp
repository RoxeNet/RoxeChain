/**
 *  @file
 *  @copyright defined in dcc/LICENSE.txt
 */

#include <dcciolib/dccio.hpp>

namespace dccio {

   class noop: public contract {
      public:
         noop( account_name self ): contract( self ) { }
         void anyaction( account_name from,
                         const std::string& /*type*/,
                         const std::string& /*data*/ )
         {
            require_auth( from );
         }
   };

   dccIO_ABI( noop, ( anyaction ) )

} /// dccio     
