/**
 *  @file
 *  @copyright defined in actc/LICENSE
 */
#include <actclib/actc.hpp>

#include "test_api.hpp"

void test_types::types_size() {

   actc_assert( sizeof(int64_t)   ==  8, "int64_t size != 8"   );
   actc_assert( sizeof(uint64_t)  ==  8, "uint64_t size != 8"  );
   actc_assert( sizeof(uint32_t)  ==  4, "uint32_t size != 4"  );
   actc_assert( sizeof(int32_t)   ==  4, "int32_t size != 4"   );
   actc_assert( sizeof(uint128_t) == 16, "uint128_t size != 16");
   actc_assert( sizeof(int128_t)  == 16, "int128_t size != 16" );
   actc_assert( sizeof(uint8_t)   ==  1, "uint8_t size != 1"   );

   actc_assert( sizeof(actc::name) ==  8, "name size !=  8");
}

void test_types::char_to_symbol() {

   actc_assert( actc::name::char_to_value('1') ==  1, "actc::char_to_symbol('1') !=  1" );
   actc_assert( actc::name::char_to_value('2') ==  2, "actc::char_to_symbol('2') !=  2" );
   actc_assert( actc::name::char_to_value('3') ==  3, "actc::char_to_symbol('3') !=  3" );
   actc_assert( actc::name::char_to_value('4') ==  4, "actc::char_to_symbol('4') !=  4" );
   actc_assert( actc::name::char_to_value('5') ==  5, "actc::char_to_symbol('5') !=  5" );
   actc_assert( actc::name::char_to_value('a') ==  6, "actc::char_to_symbol('a') !=  6" );
   actc_assert( actc::name::char_to_value('b') ==  7, "actc::char_to_symbol('b') !=  7" );
   actc_assert( actc::name::char_to_value('c') ==  8, "actc::char_to_symbol('c') !=  8" );
   actc_assert( actc::name::char_to_value('d') ==  9, "actc::char_to_symbol('d') !=  9" );
   actc_assert( actc::name::char_to_value('e') == 10, "actc::char_to_symbol('e') != 10" );
   actc_assert( actc::name::char_to_value('f') == 11, "actc::char_to_symbol('f') != 11" );
   actc_assert( actc::name::char_to_value('g') == 12, "actc::char_to_symbol('g') != 12" );
   actc_assert( actc::name::char_to_value('h') == 13, "actc::char_to_symbol('h') != 13" );
   actc_assert( actc::name::char_to_value('i') == 14, "actc::char_to_symbol('i') != 14" );
   actc_assert( actc::name::char_to_value('j') == 15, "actc::char_to_symbol('j') != 15" );
   actc_assert( actc::name::char_to_value('k') == 16, "actc::char_to_symbol('k') != 16" );
   actc_assert( actc::name::char_to_value('l') == 17, "actc::char_to_symbol('l') != 17" );
   actc_assert( actc::name::char_to_value('m') == 18, "actc::char_to_symbol('m') != 18" );
   actc_assert( actc::name::char_to_value('n') == 19, "actc::char_to_symbol('n') != 19" );
   actc_assert( actc::name::char_to_value('o') == 20, "actc::char_to_symbol('o') != 20" );
   actc_assert( actc::name::char_to_value('p') == 21, "actc::char_to_symbol('p') != 21" );
   actc_assert( actc::name::char_to_value('q') == 22, "actc::char_to_symbol('q') != 22" );
   actc_assert( actc::name::char_to_value('r') == 23, "actc::char_to_symbol('r') != 23" );
   actc_assert( actc::name::char_to_value('s') == 24, "actc::char_to_symbol('s') != 24" );
   actc_assert( actc::name::char_to_value('t') == 25, "actc::char_to_symbol('t') != 25" );
   actc_assert( actc::name::char_to_value('u') == 26, "actc::char_to_symbol('u') != 26" );
   actc_assert( actc::name::char_to_value('v') == 27, "actc::char_to_symbol('v') != 27" );
   actc_assert( actc::name::char_to_value('w') == 28, "actc::char_to_symbol('w') != 28" );
   actc_assert( actc::name::char_to_value('x') == 29, "actc::char_to_symbol('x') != 29" );
   actc_assert( actc::name::char_to_value('y') == 30, "actc::char_to_symbol('y') != 30" );
   actc_assert( actc::name::char_to_value('z') == 31, "actc::char_to_symbol('z') != 31" );

   for(unsigned char i = 0; i<255; i++) {
      if( (i >= 'a' && i <= 'z') || (i >= '1' || i <= '5') ) continue;
      actc_assert( actc::name::char_to_value((char)i) == 0, "actc::char_to_symbol() != 0" );
   }
}

void test_types::string_to_name() {
   return;
   actc_assert( actc::name("a") == "a"_n, "actc::string_to_name(a)" );
   actc_assert( actc::name("ba") == "ba"_n, "actc::string_to_name(ba)" );
   actc_assert( actc::name("cba") == "cba"_n, "actc::string_to_name(cba)" );
   actc_assert( actc::name("dcba") == "dcba"_n, "actc::string_to_name(dcba)" );
   actc_assert( actc::name("edcba") == "edcba"_n, "actc::string_to_name(edcba)" );
   actc_assert( actc::name("fedcba") == "fedcba"_n, "actc::string_to_name(fedcba)" );
   actc_assert( actc::name("gfedcba") == "gfedcba"_n, "actc::string_to_name(gfedcba)" );
   actc_assert( actc::name("hgfedcba") == "hgfedcba"_n, "actc::string_to_name(hgfedcba)" );
   actc_assert( actc::name("ihgfedcba") == "ihgfedcba"_n, "actc::string_to_name(ihgfedcba)" );
   actc_assert( actc::name("jihgfedcba") == "jihgfedcba"_n, "actc::string_to_name(jihgfedcba)" );
   actc_assert( actc::name("kjihgfedcba") == "kjihgfedcba"_n, "actc::string_to_name(kjihgfedcba)" );
   actc_assert( actc::name("lkjihgfedcba") == "lkjihgfedcba"_n, "actc::string_to_name(lkjihgfedcba)" );
   actc_assert( actc::name("mlkjihgfedcba") == "mlkjihgfedcba"_n, "actc::string_to_name(mlkjihgfedcba)" );
}
