#pragma once

#include <dcciolib/dccio.hpp>

namespace dccio {

   class sudo : public contract {
      public:
         sudo( account_name self ):contract(self){}

         void exec();

   };

} /// namespace dccio
