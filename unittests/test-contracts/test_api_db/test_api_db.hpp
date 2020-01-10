/**
 *  @file
 *  @copyright defined in actc/LICENSE
 */
#pragma once

#include <actc/actc.hpp>

class [[actc::contract]] test_api_db : public actc::contract {
public:
   using actc::contract::contract;

   [[actc::action("pg")]]
   void primary_i64_general();

   [[actc::action("pl")]]
   void primary_i64_lowerbound();

   [[actc::action("pu")]]
   void primary_i64_upperbound();

   [[actc::action("s1g")]]
   void idx64_general();

   [[actc::action("s1l")]]
   void idx64_lowerbound();

   [[actc::action("s1u")]]
   void idx64_upperbound();

   [[actc::action("tia")]]
   void test_invalid_access( actc::name code, uint64_t val, uint32_t index, bool store );

   [[actc::action("sdnancreate")]]
   void idx_double_nan_create_fail();

   [[actc::action("sdnanmodify")]]
   void idx_double_nan_modify_fail();

   [[actc::action("sdnanlookup")]]
   void idx_double_nan_lookup_fail( uint32_t lookup_type );

   [[actc::action("sk32align")]]
   void misaligned_secondary_key256_tests();

};
