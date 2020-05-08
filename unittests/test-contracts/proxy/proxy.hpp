/**
 *  @file
 *  @copyright defined in roxe/LICENSE
 */
#pragma once

#include <roxe/roxe.hpp>
#include <roxe/singleton.hpp>
#include <roxe/asset.hpp>

// Extacted from roxe.token contract:
namespace roxe {
   class [[roxe::contract("roxe.token")]] token : public roxe::contract {
   public:
      using roxe::contract::contract;

      [[roxe::action]]
      void transfer( roxe::name        from,
                     roxe::name        to,
                     roxe::asset       quantity,
                     const std::string& memo );
      using transfer_action = roxe::action_wrapper<"transfer"_n, &token::transfer>;
   };
}

// This contract:
class [[roxe::contract]] proxy : public roxe::contract {
public:
   proxy( roxe::name self, roxe::name first_receiver, roxe::datastream<const char*> ds );

   [[roxe::action]]
   void setowner( roxe::name owner, uint32_t delay );

   [[roxe::on_notify("roxe.token::transfer")]]
   void on_transfer( roxe::name        from,
                     roxe::name        to,
                     roxe::asset       quantity,
                     const std::string& memo );

   [[roxe::on_notify("roxe::onerror")]]
   void on_error( uint128_t sender_id, roxe::ignore<std::vector<char>> sent_trx );

   struct [[roxe::table]] config {
      roxe::name owner;
      uint32_t    delay   = 0;
      uint32_t    next_id = 0;

      ROXELIB_SERIALIZE( config, (owner)(delay)(next_id) )
   };

   using config_singleton = roxe::singleton< "config"_n,  config >;

protected:
   config_singleton _config;
};
