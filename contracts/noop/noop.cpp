/**
 *  @file
 *  @copyright defined in actc/LICENSE.txt
 */

#include <actclib/actc.hpp>

namespace actc {

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

   actc_ABI( noop, ( anyaction ) )

} /// actc
