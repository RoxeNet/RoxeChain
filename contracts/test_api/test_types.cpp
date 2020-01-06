/**
 *  @file
 *  @copyright defined in actc/LICENSE.txt
 */
#include <actclib/actc.hpp>

#include "test_api.hpp"

void test_types::types_size() {

   actc_assert( sizeof(int64_t) == 8, "int64_t size != 8");
   actc_assert( sizeof(uint64_t) ==  8, "uint64_t size != 8");
   actc_assert( sizeof(uint32_t) ==  4, "uint32_t size != 4");
   actc_assert( sizeof(int32_t) ==  4, "int32_t size != 4");
   actc_assert( sizeof(uint128_t) == 16, "uint128_t size != 16");
   actc_assert( sizeof(int128_t) == 16, "int128_t size != 16");
   actc_assert( sizeof(uint8_t) ==  1, "uint8_t size != 1");

   actc_assert( sizeof(account_name) ==  8, "account_name size !=  8");
   actc_assert( sizeof(table_name) ==  8, "table_name size !=  8");
   actc_assert( sizeof(time) ==  4, "time size !=  4");
   actc_assert( sizeof(actc::key256) == 32, "key256 size != 32" );
}

void test_types::char_to_symbol() {

   actc_assert( actc::char_to_symbol('1') ==  1, "actc::char_to_symbol('1') !=  1");
   actc_assert( actc::char_to_symbol('2') ==  2, "actc::char_to_symbol('2') !=  2");
   actc_assert( actc::char_to_symbol('3') ==  3, "actc::char_to_symbol('3') !=  3");
   actc_assert( actc::char_to_symbol('4') ==  4, "actc::char_to_symbol('4') !=  4");
   actc_assert( actc::char_to_symbol('5') ==  5, "actc::char_to_symbol('5') !=  5");
   actc_assert( actc::char_to_symbol('a') ==  6, "actc::char_to_symbol('a') !=  6");
   actc_assert( actc::char_to_symbol('b') ==  7, "actc::char_to_symbol('b') !=  7");
   actc_assert( actc::char_to_symbol('c') ==  8, "actc::char_to_symbol('c') !=  8");
   actc_assert( actc::char_to_symbol('d') ==  9, "actc::char_to_symbol('d') !=  9");
   actc_assert( actc::char_to_symbol('e') == 10, "actc::char_to_symbol('e') != 10");
   actc_assert( actc::char_to_symbol('f') == 11, "actc::char_to_symbol('f') != 11");
   actc_assert( actc::char_to_symbol('g') == 12, "actc::char_to_symbol('g') != 12");
   actc_assert( actc::char_to_symbol('h') == 13, "actc::char_to_symbol('h') != 13");
   actc_assert( actc::char_to_symbol('i') == 14, "actc::char_to_symbol('i') != 14");
   actc_assert( actc::char_to_symbol('j') == 15, "actc::char_to_symbol('j') != 15");
   actc_assert( actc::char_to_symbol('k') == 16, "actc::char_to_symbol('k') != 16");
   actc_assert( actc::char_to_symbol('l') == 17, "actc::char_to_symbol('l') != 17");
   actc_assert( actc::char_to_symbol('m') == 18, "actc::char_to_symbol('m') != 18");
   actc_assert( actc::char_to_symbol('n') == 19, "actc::char_to_symbol('n') != 19");
   actc_assert( actc::char_to_symbol('o') == 20, "actc::char_to_symbol('o') != 20");
   actc_assert( actc::char_to_symbol('p') == 21, "actc::char_to_symbol('p') != 21");
   actc_assert( actc::char_to_symbol('q') == 22, "actc::char_to_symbol('q') != 22");
   actc_assert( actc::char_to_symbol('r') == 23, "actc::char_to_symbol('r') != 23");
   actc_assert( actc::char_to_symbol('s') == 24, "actc::char_to_symbol('s') != 24");
   actc_assert( actc::char_to_symbol('t') == 25, "actc::char_to_symbol('t') != 25");
   actc_assert( actc::char_to_symbol('u') == 26, "actc::char_to_symbol('u') != 26");
   actc_assert( actc::char_to_symbol('v') == 27, "actc::char_to_symbol('v') != 27");
   actc_assert( actc::char_to_symbol('w') == 28, "actc::char_to_symbol('w') != 28");
   actc_assert( actc::char_to_symbol('x') == 29, "actc::char_to_symbol('x') != 29");
   actc_assert( actc::char_to_symbol('y') == 30, "actc::char_to_symbol('y') != 30");
   actc_assert( actc::char_to_symbol('z') == 31, "actc::char_to_symbol('z') != 31");

   for(unsigned char i = 0; i<255; i++) {
      if((i >= 'a' && i <= 'z') || (i >= '1' || i <= '5')) continue;
      actc_assert( actc::char_to_symbol((char)i) == 0, "actc::char_to_symbol() != 0");
   }
}

void test_types::string_to_name() {

   actc_assert( actc::string_to_name("a") == N(a) , "actc::string_to_name(a)" );
   actc_assert( actc::string_to_name("ba") == N(ba) , "actc::string_to_name(ba)" );
   actc_assert( actc::string_to_name("cba") == N(cba) , "actc::string_to_name(cba)" );
   actc_assert( actc::string_to_name("dcba") == N(dcba) , "actc::string_to_name(dcba)" );
   actc_assert( actc::string_to_name("edcba") == N(edcba) , "actc::string_to_name(edcba)" );
   actc_assert( actc::string_to_name("fedcba") == N(fedcba) , "actc::string_to_name(fedcba)" );
   actc_assert( actc::string_to_name("gfedcba") == N(gfedcba) , "actc::string_to_name(gfedcba)" );
   actc_assert( actc::string_to_name("hgfedcba") == N(hgfedcba) , "actc::string_to_name(hgfedcba)" );
   actc_assert( actc::string_to_name("ihgfedcba") == N(ihgfedcba) , "actc::string_to_name(ihgfedcba)" );
   actc_assert( actc::string_to_name("jihgfedcba") == N(jihgfedcba) , "actc::string_to_name(jihgfedcba)" );
   actc_assert( actc::string_to_name("kjihgfedcba") == N(kjihgfedcba) , "actc::string_to_name(kjihgfedcba)" );
   actc_assert( actc::string_to_name("lkjihgfedcba") == N(lkjihgfedcba) , "actc::string_to_name(lkjihgfedcba)" );
   actc_assert( actc::string_to_name("mlkjihgfedcba") == N(mlkjihgfedcba) , "actc::string_to_name(mlkjihgfedcba)" );
   actc_assert( actc::string_to_name("mlkjihgfedcba1") == N(mlkjihgfedcba2) , "actc::string_to_name(mlkjihgfedcba2)" );
   actc_assert( actc::string_to_name("mlkjihgfedcba55") == N(mlkjihgfedcba14) , "actc::string_to_name(mlkjihgfedcba14)" );

   actc_assert( actc::string_to_name("azAA34") == N(azBB34) , "actc::string_to_name N(azBB34)" );
   actc_assert( actc::string_to_name("AZaz12Bc34") == N(AZaz12Bc34) , "actc::string_to_name AZaz12Bc34" );
   actc_assert( actc::string_to_name("AAAAAAAAAAAAAAA") == actc::string_to_name("BBBBBBBBBBBBBDDDDDFFFGG") , "actc::string_to_name BBBBBBBBBBBBBDDDDDFFFGG" );
}

void test_types::name_class() {

   actc_assert( actc::name{actc::string_to_name("azAA34")}.value == N(azAA34), "actc::name != N(azAA34)" );
   actc_assert( actc::name{actc::string_to_name("AABBCC")}.value == 0, "actc::name != N(0)" );
   actc_assert( actc::name{actc::string_to_name("AA11")}.value == N(AA11), "actc::name != N(AA11)" );
   actc_assert( actc::name{actc::string_to_name("11AA")}.value == N(11), "actc::name != N(11)" );
   actc_assert( actc::name{actc::string_to_name("22BBCCXXAA")}.value == N(22), "actc::name != N(22)" );
   actc_assert( actc::name{actc::string_to_name("AAAbbcccdd")} == actc::name{actc::string_to_name("AAAbbcccdd")}, "actc::name == actc::name" );

   uint64_t tmp = actc::name{actc::string_to_name("11bbcccdd")};
   actc_assert(N(11bbcccdd) == tmp, "N(11bbcccdd) == tmp");
}
