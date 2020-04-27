/**
 *  @file
 *  @copyright defined in actc/LICENSE
 */
#pragma once

#include <actc/actc.hpp>

class [[actc::contract]] payloadless : public actc::contract {
public:
   using actc::contract::contract;

   [[actc::action]]
   void doit();
};
