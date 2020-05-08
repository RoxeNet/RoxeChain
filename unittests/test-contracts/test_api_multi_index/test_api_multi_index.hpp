/**
 *  @file
 *  @copyright defined in roxe/LICENSE
 */
#pragma once

#include <roxe/roxe.hpp>

class [[roxe::contract]] test_api_multi_index : public roxe::contract {
public:
   using roxe::contract::contract;

   [[roxe::action("s1g")]]
   void idx64_general();

   [[roxe::action("s1store")]]
   void idx64_store_only();

   [[roxe::action("s1check")]]
   void idx64_check_without_storing();

   [[roxe::action("s1findfail1")]]
   void idx64_require_find_fail();

   [[roxe::action("s1findfail2")]]
   void idx64_require_find_fail_with_msg();

   [[roxe::action("s1findfail3")]]
   void idx64_require_find_sk_fail();

   [[roxe::action("s1findfail4")]]
   void idx64_require_find_sk_fail_with_msg();

   [[roxe::action("s1pkend")]]
   void idx64_pk_iterator_exceed_end();

   [[roxe::action("s1skend")]]
   void idx64_sk_iterator_exceed_end();

   [[roxe::action("s1pkbegin")]]
   void idx64_pk_iterator_exceed_begin();

   [[roxe::action("s1skbegin")]]
   void idx64_sk_iterator_exceed_begin();

   [[roxe::action("s1pkref")]]
   void idx64_pass_pk_ref_to_other_table();

   [[roxe::action("s1skref")]]
   void idx64_pass_sk_ref_to_other_table();

   [[roxe::action("s1pkitrto")]]
   void idx64_pass_pk_end_itr_to_iterator_to();

   [[roxe::action("s1pkmodify")]]
   void idx64_pass_pk_end_itr_to_modify();

   [[roxe::action("s1pkerase")]]
   void idx64_pass_pk_end_itr_to_erase();

   [[roxe::action("s1skitrto")]]
   void idx64_pass_sk_end_itr_to_iterator_to();

   [[roxe::action("s1skmodify")]]
   void idx64_pass_sk_end_itr_to_modify();

   [[roxe::action("s1skerase")]]
   void idx64_pass_sk_end_itr_to_erase();

   [[roxe::action("s1modpk")]]
   void idx64_modify_primary_key();

   [[roxe::action("s1exhaustpk")]]
   void idx64_run_out_of_avl_pk();

   [[roxe::action("s1skcache")]]
   void idx64_sk_cache_pk_lookup();

   [[roxe::action("s1pkcache")]]
   void idx64_pk_cache_sk_lookup();

   [[roxe::action("s2g")]]
   void idx128_general();

   [[roxe::action("s2store")]]
   void idx128_store_only();

   [[roxe::action("s2check")]]
   void idx128_check_without_storing();

   [[roxe::action("s2autoinc")]]
   void idx128_autoincrement_test();

   [[roxe::action("s2autoinc1")]]
   void idx128_autoincrement_test_part1();

   [[roxe::action("s2autoinc2")]]
   void idx128_autoincrement_test_part2();

   [[roxe::action("s3g")]]
   void idx256_general();

   [[roxe::action("sdg")]]
   void idx_double_general();

   [[roxe::action("sldg")]]
   void idx_long_double_general();

};
