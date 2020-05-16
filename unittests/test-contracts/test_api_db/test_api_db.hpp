/**
 *  @file
 *  @copyright defined in roxe/LICENSE
 */
#pragma once

#include <roxe/roxe.hpp>

class [[roxe::contract]] test_api_db : public roxe::contract {
public:
   using roxe::contract::contract;

   [[roxe::action("pg")]]
   void primary_i64_general();

   [[roxe::action("pl")]]
   void primary_i64_lowerbound();

   [[roxe::action("pu")]]
   void primary_i64_upperbound();

   [[roxe::action("s1g")]]
   void idx64_general();

   [[roxe::action("s1l")]]
   void idx64_lowerbound();

   [[roxe::action("s1u")]]
   void idx64_upperbound();

   [[roxe::action("tia")]]
   void test_invalid_access( roxe::name code, uint64_t val, uint32_t index, bool store );

   [[roxe::action("sdnancreate")]]
   void idx_double_nan_create_fail();

   [[roxe::action("sdnanmodify")]]
   void idx_double_nan_modify_fail();

   [[roxe::action("sdnanlookup")]]
   void idx_double_nan_lookup_fail( uint32_t lookup_type );

   [[roxe::action("sk32align")]]
   void misaligned_secondary_key256_tests();

};
