/**
 *  @file
 *  @copyright defined in actc/LICENSE
 */
#pragma once

#include <actc/actc.hpp>
#include <vector>

class [[actc::contract]] deferred_test : public actc::contract {
public:
   using actc::contract::contract;

   [[actc::action]]
   void defercall( actc::name payer, uint64_t sender_id, actc::name contract, uint64_t payload );

   [[actc::action]]
   void delayedcall( actc::name payer, uint64_t sender_id, actc::name contract,
                     uint64_t payload, uint32_t delay_sec, bool replace_existing );

   [[actc::action]]
   void deferfunc( uint64_t payload );
   using deferfunc_action = actc::action_wrapper<"deferfunc"_n, &deferred_test::deferfunc>;

   [[actc::action]]
   void inlinecall( actc::name contract, actc::name authorizer, uint64_t payload );

   [[actc::action]]
   void fail();

   [[actc::on_notify("actc::onerror")]]
   void on_error( uint128_t sender_id, actc::ignore<std::vector<char>> sent_trx );
};
