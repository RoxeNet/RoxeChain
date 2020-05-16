/**
 *  @file
 *  @copyright defined in roxe/LICENSE
 */
#pragma once

#include <roxe/roxe.hpp>

class [[roxe::contract]] noop : public roxe::contract {
public:
   using roxe::contract::contract;

   [[roxe::action]]
   void anyaction( roxe::name                       from,
                   const roxe::ignore<std::string>& type,
                   const roxe::ignore<std::string>& data );
};
