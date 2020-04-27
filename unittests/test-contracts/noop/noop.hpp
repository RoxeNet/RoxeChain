/**
 *  @file
 *  @copyright defined in actc/LICENSE
 */
#pragma once

#include <actc/actc.hpp>

class [[actc::contract]] noop : public actc::contract {
public:
   using actc::contract::contract;

   [[actc::action]]
   void anyaction( actc::name                       from,
                   const actc::ignore<std::string>& type,
                   const actc::ignore<std::string>& data );
};
