/**
 *  @file
 *  @copyright defined in roxe/LICENSE
 */
#pragma once

#include <roxe/roxe.hpp>

class [[roxe::contract]] ram_restrictions_test : public roxe::contract {
public:
   struct [[roxe::table]] data {
      uint64_t           key;
      std::vector<char>  value;

      uint64_t primary_key() const { return key; }
   };

   typedef roxe::multi_index<"tablea"_n, data> tablea;
   typedef roxe::multi_index<"tableb"_n, data> tableb;

public:
   using roxe::contract::contract;

   [[roxe::action]]
   void noop();

   [[roxe::action]]
   void setdata( uint32_t len1, uint32_t len2, roxe::name payer );

   [[roxe::action]]
   void notifysetdat( roxe::name acctonotify, uint32_t len1, uint32_t len2, roxe::name payer );

   [[roxe::on_notify("tester2::notifysetdat")]]
   void on_notify_setdata( roxe::name acctonotify, uint32_t len1, uint32_t len2, roxe::name payer );

   [[roxe::action]]
   void senddefer( uint64_t senderid, roxe::name payer );

   [[roxe::action]]
   void notifydefer( roxe::name acctonotify, uint64_t senderid, roxe::name payer );

   [[roxe::on_notify("tester2::notifydefer")]]
   void on_notifydefer( roxe::name acctonotify, uint64_t senderid, roxe::name payer );

};
