/**
 *  @file
 *  @copyright defined in actc/LICENSE
 */
#pragma once

#include <actc/actc.hpp>

class [[actc::contract]] test_api_multi_index : public actc::contract {
public:
   using actc::contract::contract;

   [[actc::action("s1g")]]
   void idx64_general();

   [[actc::action("s1store")]]
   void idx64_store_only();

   [[actc::action("s1check")]]
   void idx64_check_without_storing();

   [[actc::action("s1findfail1")]]
   void idx64_require_find_fail();

   [[actc::action("s1findfail2")]]
   void idx64_require_find_fail_with_msg();

   [[actc::action("s1findfail3")]]
   void idx64_require_find_sk_fail();

   [[actc::action("s1findfail4")]]
   void idx64_require_find_sk_fail_with_msg();

   [[actc::action("s1pkend")]]
   void idx64_pk_iterator_exceed_end();

   [[actc::action("s1skend")]]
   void idx64_sk_iterator_exceed_end();

   [[actc::action("s1pkbegin")]]
   void idx64_pk_iterator_exceed_begin();

   [[actc::action("s1skbegin")]]
   void idx64_sk_iterator_exceed_begin();

   [[actc::action("s1pkref")]]
   void idx64_pass_pk_ref_to_other_table();

   [[actc::action("s1skref")]]
   void idx64_pass_sk_ref_to_other_table();

   [[actc::action("s1pkitrto")]]
   void idx64_pass_pk_end_itr_to_iterator_to();

   [[actc::action("s1pkmodify")]]
   void idx64_pass_pk_end_itr_to_modify();

   [[actc::action("s1pkerase")]]
   void idx64_pass_pk_end_itr_to_erase();

   [[actc::action("s1skitrto")]]
   void idx64_pass_sk_end_itr_to_iterator_to();

   [[actc::action("s1skmodify")]]
   void idx64_pass_sk_end_itr_to_modify();

   [[actc::action("s1skerase")]]
   void idx64_pass_sk_end_itr_to_erase();

   [[actc::action("s1modpk")]]
   void idx64_modify_primary_key();

   [[actc::action("s1exhaustpk")]]
   void idx64_run_out_of_avl_pk();

   [[actc::action("s1skcache")]]
   void idx64_sk_cache_pk_lookup();

   [[actc::action("s1pkcache")]]
   void idx64_pk_cache_sk_lookup();

   [[actc::action("s2g")]]
   void idx128_general();

   [[actc::action("s2store")]]
   void idx128_store_only();

   [[actc::action("s2check")]]
   void idx128_check_without_storing();

   [[actc::action("s2autoinc")]]
   void idx128_autoincrement_test();

   [[actc::action("s2autoinc1")]]
   void idx128_autoincrement_test_part1();

   [[actc::action("s2autoinc2")]]
   void idx128_autoincrement_test_part2();

   [[actc::action("s3g")]]
   void idx256_general();

   [[actc::action("sdg")]]
   void idx_double_general();

   [[actc::action("sldg")]]
   void idx_long_double_general();

};
