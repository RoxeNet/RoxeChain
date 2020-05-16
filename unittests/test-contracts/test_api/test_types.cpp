/**
 *  @file
 *  @copyright defined in roxe/LICENSE
 */
#include <roxelib/roxe.hpp>

#include "test_api.hpp"

void test_types::types_size() {

   roxe_assert( sizeof(int64_t)   ==  8, "int64_t size != 8"   );
   roxe_assert( sizeof(uint64_t)  ==  8, "uint64_t size != 8"  );
   roxe_assert( sizeof(uint32_t)  ==  4, "uint32_t size != 4"  );
   roxe_assert( sizeof(int32_t)   ==  4, "int32_t size != 4"   );
   roxe_assert( sizeof(uint128_t) == 16, "uint128_t size != 16");
   roxe_assert( sizeof(int128_t)  == 16, "int128_t size != 16" );
   roxe_assert( sizeof(uint8_t)   ==  1, "uint8_t size != 1"   );

   roxe_assert( sizeof(roxe::name) ==  8, "name size !=  8");
}

void test_types::char_to_symbol() {

   roxe_assert( roxe::name::char_to_value('1') ==  1, "roxe::char_to_symbol('1') !=  1" );
   roxe_assert( roxe::name::char_to_value('2') ==  2, "roxe::char_to_symbol('2') !=  2" );
   roxe_assert( roxe::name::char_to_value('3') ==  3, "roxe::char_to_symbol('3') !=  3" );
   roxe_assert( roxe::name::char_to_value('4') ==  4, "roxe::char_to_symbol('4') !=  4" );
   roxe_assert( roxe::name::char_to_value('5') ==  5, "roxe::char_to_symbol('5') !=  5" );
   roxe_assert( roxe::name::char_to_value('a') ==  6, "roxe::char_to_symbol('a') !=  6" );
   roxe_assert( roxe::name::char_to_value('b') ==  7, "roxe::char_to_symbol('b') !=  7" );
   roxe_assert( roxe::name::char_to_value('c') ==  8, "roxe::char_to_symbol('c') !=  8" );
   roxe_assert( roxe::name::char_to_value('d') ==  9, "roxe::char_to_symbol('d') !=  9" );
   roxe_assert( roxe::name::char_to_value('e') == 10, "roxe::char_to_symbol('e') != 10" );
   roxe_assert( roxe::name::char_to_value('f') == 11, "roxe::char_to_symbol('f') != 11" );
   roxe_assert( roxe::name::char_to_value('g') == 12, "roxe::char_to_symbol('g') != 12" );
   roxe_assert( roxe::name::char_to_value('h') == 13, "roxe::char_to_symbol('h') != 13" );
   roxe_assert( roxe::name::char_to_value('i') == 14, "roxe::char_to_symbol('i') != 14" );
   roxe_assert( roxe::name::char_to_value('j') == 15, "roxe::char_to_symbol('j') != 15" );
   roxe_assert( roxe::name::char_to_value('k') == 16, "roxe::char_to_symbol('k') != 16" );
   roxe_assert( roxe::name::char_to_value('l') == 17, "roxe::char_to_symbol('l') != 17" );
   roxe_assert( roxe::name::char_to_value('m') == 18, "roxe::char_to_symbol('m') != 18" );
   roxe_assert( roxe::name::char_to_value('n') == 19, "roxe::char_to_symbol('n') != 19" );
   roxe_assert( roxe::name::char_to_value('o') == 20, "roxe::char_to_symbol('o') != 20" );
   roxe_assert( roxe::name::char_to_value('p') == 21, "roxe::char_to_symbol('p') != 21" );
   roxe_assert( roxe::name::char_to_value('q') == 22, "roxe::char_to_symbol('q') != 22" );
   roxe_assert( roxe::name::char_to_value('r') == 23, "roxe::char_to_symbol('r') != 23" );
   roxe_assert( roxe::name::char_to_value('s') == 24, "roxe::char_to_symbol('s') != 24" );
   roxe_assert( roxe::name::char_to_value('t') == 25, "roxe::char_to_symbol('t') != 25" );
   roxe_assert( roxe::name::char_to_value('u') == 26, "roxe::char_to_symbol('u') != 26" );
   roxe_assert( roxe::name::char_to_value('v') == 27, "roxe::char_to_symbol('v') != 27" );
   roxe_assert( roxe::name::char_to_value('w') == 28, "roxe::char_to_symbol('w') != 28" );
   roxe_assert( roxe::name::char_to_value('x') == 29, "roxe::char_to_symbol('x') != 29" );
   roxe_assert( roxe::name::char_to_value('y') == 30, "roxe::char_to_symbol('y') != 30" );
   roxe_assert( roxe::name::char_to_value('z') == 31, "roxe::char_to_symbol('z') != 31" );

   for(unsigned char i = 0; i<255; i++) {
      if( (i >= 'a' && i <= 'z') || (i >= '1' || i <= '5') ) continue;
      roxe_assert( roxe::name::char_to_value((char)i) == 0, "roxe::char_to_symbol() != 0" );
   }
}

void test_types::string_to_name() {
   return;
   roxe_assert( roxe::name("a") == "a"_n, "roxe::string_to_name(a)" );
   roxe_assert( roxe::name("ba") == "ba"_n, "roxe::string_to_name(ba)" );
   roxe_assert( roxe::name("cba") == "cba"_n, "roxe::string_to_name(cba)" );
   roxe_assert( roxe::name("dcba") == "dcba"_n, "roxe::string_to_name(dcba)" );
   roxe_assert( roxe::name("edcba") == "edcba"_n, "roxe::string_to_name(edcba)" );
   roxe_assert( roxe::name("fedcba") == "fedcba"_n, "roxe::string_to_name(fedcba)" );
   roxe_assert( roxe::name("gfedcba") == "gfedcba"_n, "roxe::string_to_name(gfedcba)" );
   roxe_assert( roxe::name("hgfedcba") == "hgfedcba"_n, "roxe::string_to_name(hgfedcba)" );
   roxe_assert( roxe::name("ihgfedcba") == "ihgfedcba"_n, "roxe::string_to_name(ihgfedcba)" );
   roxe_assert( roxe::name("jihgfedcba") == "jihgfedcba"_n, "roxe::string_to_name(jihgfedcba)" );
   roxe_assert( roxe::name("kjihgfedcba") == "kjihgfedcba"_n, "roxe::string_to_name(kjihgfedcba)" );
   roxe_assert( roxe::name("lkjihgfedcba") == "lkjihgfedcba"_n, "roxe::string_to_name(lkjihgfedcba)" );
   roxe_assert( roxe::name("mlkjihgfedcba") == "mlkjihgfedcba"_n, "roxe::string_to_name(mlkjihgfedcba)" );
}
