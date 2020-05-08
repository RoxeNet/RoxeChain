/**
 *  @file
 *  @copyright defined in roxe/LICENSE
 */
#pragma once

#include <roxe/roxe.hpp>

class [[roxe::contract]] payloadless : public roxe::contract {
public:
   using roxe::contract::contract;

   [[roxe::action]]
   void doit();
};
