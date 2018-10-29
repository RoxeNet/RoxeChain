/**
 *  @file
 *  @copyright defined in dcc/LICENSE.txt
 */
#include <dcciolib/dccio.hpp>

#include "test_api.hpp"

void test_types::types_size() {

   dccio_assert( sizeof(int64_t) == 8, "int64_t size != 8");
   dccio_assert( sizeof(uint64_t) ==  8, "uint64_t size != 8");
   dccio_assert( sizeof(uint32_t) ==  4, "uint32_t size != 4");
   dccio_assert( sizeof(int32_t) ==  4, "int32_t size != 4");
   dccio_assert( sizeof(uint128_t) == 16, "uint128_t size != 16");
   dccio_assert( sizeof(int128_t) == 16, "int128_t size != 16");
   dccio_assert( sizeof(uint8_t) ==  1, "uint8_t size != 1");

   dccio_assert( sizeof(account_name) ==  8, "account_name size !=  8");
   dccio_assert( sizeof(table_name) ==  8, "table_name size !=  8");
   dccio_assert( sizeof(time) ==  4, "time size !=  4");
   dccio_assert( sizeof(dccio::key256) == 32, "key256 size != 32" );
}

void test_types::char_to_symbol() {

   dccio_assert( dccio::char_to_symbol('1') ==  1, "dccio::char_to_symbol('1') !=  1");
   dccio_assert( dccio::char_to_symbol('2') ==  2, "dccio::char_to_symbol('2') !=  2");
   dccio_assert( dccio::char_to_symbol('3') ==  3, "dccio::char_to_symbol('3') !=  3");
   dccio_assert( dccio::char_to_symbol('4') ==  4, "dccio::char_to_symbol('4') !=  4");
   dccio_assert( dccio::char_to_symbol('5') ==  5, "dccio::char_to_symbol('5') !=  5");
   dccio_assert( dccio::char_to_symbol('a') ==  6, "dccio::char_to_symbol('a') !=  6");
   dccio_assert( dccio::char_to_symbol('b') ==  7, "dccio::char_to_symbol('b') !=  7");
   dccio_assert( dccio::char_to_symbol('c') ==  8, "dccio::char_to_symbol('c') !=  8");
   dccio_assert( dccio::char_to_symbol('d') ==  9, "dccio::char_to_symbol('d') !=  9");
   dccio_assert( dccio::char_to_symbol('e') == 10, "dccio::char_to_symbol('e') != 10");
   dccio_assert( dccio::char_to_symbol('f') == 11, "dccio::char_to_symbol('f') != 11");
   dccio_assert( dccio::char_to_symbol('g') == 12, "dccio::char_to_symbol('g') != 12");
   dccio_assert( dccio::char_to_symbol('h') == 13, "dccio::char_to_symbol('h') != 13");
   dccio_assert( dccio::char_to_symbol('i') == 14, "dccio::char_to_symbol('i') != 14");
   dccio_assert( dccio::char_to_symbol('j') == 15, "dccio::char_to_symbol('j') != 15");
   dccio_assert( dccio::char_to_symbol('k') == 16, "dccio::char_to_symbol('k') != 16");
   dccio_assert( dccio::char_to_symbol('l') == 17, "dccio::char_to_symbol('l') != 17");
   dccio_assert( dccio::char_to_symbol('m') == 18, "dccio::char_to_symbol('m') != 18");
   dccio_assert( dccio::char_to_symbol('n') == 19, "dccio::char_to_symbol('n') != 19");
   dccio_assert( dccio::char_to_symbol('o') == 20, "dccio::char_to_symbol('o') != 20");
   dccio_assert( dccio::char_to_symbol('p') == 21, "dccio::char_to_symbol('p') != 21");
   dccio_assert( dccio::char_to_symbol('q') == 22, "dccio::char_to_symbol('q') != 22");
   dccio_assert( dccio::char_to_symbol('r') == 23, "dccio::char_to_symbol('r') != 23");
   dccio_assert( dccio::char_to_symbol('s') == 24, "dccio::char_to_symbol('s') != 24");
   dccio_assert( dccio::char_to_symbol('t') == 25, "dccio::char_to_symbol('t') != 25");
   dccio_assert( dccio::char_to_symbol('u') == 26, "dccio::char_to_symbol('u') != 26");
   dccio_assert( dccio::char_to_symbol('v') == 27, "dccio::char_to_symbol('v') != 27");
   dccio_assert( dccio::char_to_symbol('w') == 28, "dccio::char_to_symbol('w') != 28");
   dccio_assert( dccio::char_to_symbol('x') == 29, "dccio::char_to_symbol('x') != 29");
   dccio_assert( dccio::char_to_symbol('y') == 30, "dccio::char_to_symbol('y') != 30");
   dccio_assert( dccio::char_to_symbol('z') == 31, "dccio::char_to_symbol('z') != 31");

   for(unsigned char i = 0; i<255; i++) {
      if((i >= 'a' && i <= 'z') || (i >= '1' || i <= '5')) continue;
      dccio_assert( dccio::char_to_symbol((char)i) == 0, "dccio::char_to_symbol() != 0");
   }
}

void test_types::string_to_name() {

   dccio_assert( dccio::string_to_name("a") == N(a) , "dccio::string_to_name(a)" );
   dccio_assert( dccio::string_to_name("ba") == N(ba) , "dccio::string_to_name(ba)" );
   dccio_assert( dccio::string_to_name("cba") == N(cba) , "dccio::string_to_name(cba)" );
   dccio_assert( dccio::string_to_name("dcba") == N(dcba) , "dccio::string_to_name(dcba)" );
   dccio_assert( dccio::string_to_name("edcba") == N(edcba) , "dccio::string_to_name(edcba)" );
   dccio_assert( dccio::string_to_name("fedcba") == N(fedcba) , "dccio::string_to_name(fedcba)" );
   dccio_assert( dccio::string_to_name("gfedcba") == N(gfedcba) , "dccio::string_to_name(gfedcba)" );
   dccio_assert( dccio::string_to_name("hgfedcba") == N(hgfedcba) , "dccio::string_to_name(hgfedcba)" );
   dccio_assert( dccio::string_to_name("ihgfedcba") == N(ihgfedcba) , "dccio::string_to_name(ihgfedcba)" );
   dccio_assert( dccio::string_to_name("jihgfedcba") == N(jihgfedcba) , "dccio::string_to_name(jihgfedcba)" );
   dccio_assert( dccio::string_to_name("kjihgfedcba") == N(kjihgfedcba) , "dccio::string_to_name(kjihgfedcba)" );
   dccio_assert( dccio::string_to_name("lkjihgfedcba") == N(lkjihgfedcba) , "dccio::string_to_name(lkjihgfedcba)" );
   dccio_assert( dccio::string_to_name("mlkjihgfedcba") == N(mlkjihgfedcba) , "dccio::string_to_name(mlkjihgfedcba)" );
   dccio_assert( dccio::string_to_name("mlkjihgfedcba1") == N(mlkjihgfedcba2) , "dccio::string_to_name(mlkjihgfedcba2)" );
   dccio_assert( dccio::string_to_name("mlkjihgfedcba55") == N(mlkjihgfedcba14) , "dccio::string_to_name(mlkjihgfedcba14)" );

   dccio_assert( dccio::string_to_name("azAA34") == N(azBB34) , "dccio::string_to_name N(azBB34)" );
   dccio_assert( dccio::string_to_name("AZaz12Bc34") == N(AZaz12Bc34) , "dccio::string_to_name AZaz12Bc34" );
   dccio_assert( dccio::string_to_name("AAAAAAAAAAAAAAA") == dccio::string_to_name("BBBBBBBBBBBBBDDDDDFFFGG") , "dccio::string_to_name BBBBBBBBBBBBBDDDDDFFFGG" );
}

void test_types::name_class() {

   dccio_assert( dccio::name{dccio::string_to_name("azAA34")}.value == N(azAA34), "dccio::name != N(azAA34)" );
   dccio_assert( dccio::name{dccio::string_to_name("AABBCC")}.value == 0, "dccio::name != N(0)" );
   dccio_assert( dccio::name{dccio::string_to_name("AA11")}.value == N(AA11), "dccio::name != N(AA11)" );
   dccio_assert( dccio::name{dccio::string_to_name("11AA")}.value == N(11), "dccio::name != N(11)" );
   dccio_assert( dccio::name{dccio::string_to_name("22BBCCXXAA")}.value == N(22), "dccio::name != N(22)" );
   dccio_assert( dccio::name{dccio::string_to_name("AAAbbcccdd")} == dccio::name{dccio::string_to_name("AAAbbcccdd")}, "dccio::name == dccio::name" );

   uint64_t tmp = dccio::name{dccio::string_to_name("11bbcccdd")};
   dccio_assert(N(11bbcccdd) == tmp, "N(11bbcccdd) == tmp");
}
