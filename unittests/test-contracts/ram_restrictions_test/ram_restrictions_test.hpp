/**
 *  @file
 *  @copyright defined in actc/LICENSE
 */
#pragma once

#include <actc/actc.hpp>

class [[actc::contract]] ram_restrictions_test : public actc::contract {
public:
   struct [[actc::table]] data {
      uint64_t           key;
      std::vector<char>  value;

      uint64_t primary_key() const { return key; }
   };

   typedef actc::multi_index<"tablea"_n, data> tablea;
   typedef actc::multi_index<"tableb"_n, data> tableb;

public:
   using actc::contract::contract;

   [[actc::action]]
   void noop();

   [[actc::action]]
   void setdata( uint32_t len1, uint32_t len2, actc::name payer );

   [[actc::action]]
   void notifysetdat( actc::name acctonotify, uint32_t len1, uint32_t len2, actc::name payer );

   [[actc::on_notify("tester2::notifysetdat")]]
   void on_notify_setdata( actc::name acctonotify, uint32_t len1, uint32_t len2, actc::name payer );

   [[actc::action]]
   void senddefer( uint64_t senderid, actc::name payer );

   [[actc::action]]
   void notifydefer( actc::name acctonotify, uint64_t senderid, actc::name payer );

   [[actc::on_notify("tester2::notifydefer")]]
   void on_notifydefer( actc::name acctonotify, uint64_t senderid, actc::name payer );

};
