/**
 *  @file
 *  @copyright defined in actc/LICENSE
 */
#pragma once

#include <actc/actc.hpp>

class [[actc::contract]] restrict_action_test : public actc::contract {
public:
   using actc::contract::contract;

   [[actc::action]]
   void noop( );

   [[actc::action]]
   void sendinline( actc::name authorizer );

   [[actc::action]]
   void senddefer( actc::name authorizer, uint32_t senderid );


   [[actc::action]]
   void notifyinline( actc::name acctonotify, actc::name authorizer );

   [[actc::action]]
   void notifydefer( actc::name acctonotify, actc::name authorizer, uint32_t senderid );

   [[actc::on_notify("testacc::notifyinline")]]
   void on_notify_inline( actc::name acctonotify, actc::name authorizer );

   [[actc::on_notify("testacc::notifydefer")]]
   void on_notify_defer( actc::name acctonotify, actc::name authorizer, uint32_t senderid );
};
