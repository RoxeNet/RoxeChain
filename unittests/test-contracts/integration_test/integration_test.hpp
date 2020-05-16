/**
 *  @file
 *  @copyright defined in roxe/LICENSE
 */
#pragma once

#include <roxe/roxe.hpp>

class [[roxe::contract]] integration_test : public roxe::contract {
public:
   using roxe::contract::contract;

   [[roxe::action]]
   void store( roxe::name from, roxe::name to, uint64_t num );

   struct [[roxe::table("payloads")]] payload {
      uint64_t              key;
      std::vector<uint64_t> data;

      uint64_t primary_key()const { return key; }

      ROXELIB_SERIALIZE( payload, (key)(data) )
   };

   using payloads_table = roxe::multi_index< "payloads"_n,  payload >;

};
