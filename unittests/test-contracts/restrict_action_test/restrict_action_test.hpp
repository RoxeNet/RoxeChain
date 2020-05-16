/**
 *  @file
 *  @copyright defined in roxe/LICENSE
 */
#pragma once

#include <roxe/roxe.hpp>

class [[roxe::contract]] restrict_action_test : public roxe::contract {
public:
   using roxe::contract::contract;

   [[roxe::action]]
   void noop( );

   [[roxe::action]]
   void sendinline( roxe::name authorizer );

   [[roxe::action]]
   void senddefer( roxe::name authorizer, uint32_t senderid );


   [[roxe::action]]
   void notifyinline( roxe::name acctonotify, roxe::name authorizer );

   [[roxe::action]]
   void notifydefer( roxe::name acctonotify, roxe::name authorizer, uint32_t senderid );

   [[roxe::on_notify("testacc::notifyinline")]]
   void on_notify_inline( roxe::name acctonotify, roxe::name authorizer );

   [[roxe::on_notify("testacc::notifydefer")]]
   void on_notify_defer( roxe::name acctonotify, roxe::name authorizer, uint32_t senderid );
};
