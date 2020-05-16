/**
 *  @file
 *  @copyright defined in roxe/LICENSE
 */
#pragma once

#include <roxe/roxe.hpp>
#include <vector>

class [[roxe::contract]] deferred_test : public roxe::contract {
public:
   using roxe::contract::contract;

   [[roxe::action]]
   void defercall( roxe::name payer, uint64_t sender_id, roxe::name contract, uint64_t payload );

   [[roxe::action]]
   void delayedcall( roxe::name payer, uint64_t sender_id, roxe::name contract,
                     uint64_t payload, uint32_t delay_sec, bool replace_existing );

   [[roxe::action]]
   void deferfunc( uint64_t payload );
   using deferfunc_action = roxe::action_wrapper<"deferfunc"_n, &deferred_test::deferfunc>;

   [[roxe::action]]
   void inlinecall( roxe::name contract, roxe::name authorizer, uint64_t payload );

   [[roxe::action]]
   void fail();

   [[roxe::on_notify("roxe::onerror")]]
   void on_error( uint128_t sender_id, roxe::ignore<std::vector<char>> sent_trx );
};
