/**
 *  @file
 *  @copyright defined in roxe/LICENSE
 */
#pragma once

#include <roxe/roxe.hpp>

class [[roxe::contract]] asserter : public roxe::contract {
public:
   using roxe::contract::contract;

   [[roxe::action]]
   void procassert( int8_t condition, std::string message );

   [[roxe::action]]
   void provereset();
};
