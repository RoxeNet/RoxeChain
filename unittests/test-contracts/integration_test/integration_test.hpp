/**
 *  @file
 *  @copyright defined in actc/LICENSE
 */
#pragma once

#include <actc/actc.hpp>

class [[actc::contract]] integration_test : public actc::contract {
public:
   using actc::contract::contract;

   [[actc::action]]
   void store( actc::name from, actc::name to, uint64_t num );

   struct [[actc::table("payloads")]] payload {
      uint64_t              key;
      std::vector<uint64_t> data;

      uint64_t primary_key()const { return key; }

      ACTCLIB_SERIALIZE( payload, (key)(data) )
   };

   using payloads_table = actc::multi_index< "payloads"_n,  payload >;

};
