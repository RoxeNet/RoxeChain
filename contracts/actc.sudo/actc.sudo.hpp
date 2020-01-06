#pragma once

#include <actclib/actc.hpp>

namespace actc {

   class sudo : public contract {
      public:
         sudo( account_name self ):contract(self){}

         void exec();

   };

} /// namespace actc
