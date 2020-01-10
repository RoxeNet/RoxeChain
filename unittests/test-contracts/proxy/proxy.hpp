/**
 *  @file
 *  @copyright defined in actc/LICENSE
 */
#pragma once

#include <actc/actc.hpp>
#include <actc/singleton.hpp>
#include <actc/asset.hpp>

// Extacted from actc.token contract:
namespace actc {
   class [[actc::contract("actc.token")]] token : public actc::contract {
   public:
      using actc::contract::contract;

      [[actc::action]]
      void transfer( actc::name        from,
                     actc::name        to,
                     actc::asset       quantity,
                     const std::string& memo );
      using transfer_action = actc::action_wrapper<"transfer"_n, &token::transfer>;
   };
}

// This contract:
class [[actc::contract]] proxy : public actc::contract {
public:
   proxy( actc::name self, actc::name first_receiver, actc::datastream<const char*> ds );

   [[actc::action]]
   void setowner( actc::name owner, uint32_t delay );

   [[actc::on_notify("actc.token::transfer")]]
   void on_transfer( actc::name        from,
                     actc::name        to,
                     actc::asset       quantity,
                     const std::string& memo );

   [[actc::on_notify("actc::onerror")]]
   void on_error( uint128_t sender_id, actc::ignore<std::vector<char>> sent_trx );

   struct [[actc::table]] config {
      actc::name owner;
      uint32_t    delay   = 0;
      uint32_t    next_id = 0;

      ACTCLIB_SERIALIZE( config, (owner)(delay)(next_id) )
   };

   using config_singleton = actc::singleton< "config"_n,  config >;

protected:
   config_singleton _config;
};
