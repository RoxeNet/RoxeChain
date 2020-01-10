/**
 *  @file
 *  @copyright defined in actc/LICENSE
 */
#pragma once

#include <actc/actc.hpp>

class [[actc::contract]] asserter : public actc::contract {
public:
   using actc::contract::contract;

   [[actc::action]]
   void procassert( int8_t condition, std::string message );

   [[actc::action]]
   void provereset();
};
