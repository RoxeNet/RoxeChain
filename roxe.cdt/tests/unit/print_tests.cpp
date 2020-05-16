#include <roxe/roxe.hpp>
#include <roxe/tester.hpp>

using namespace roxe::native;

ROXE_TEST_BEGIN(print_test)
   CHECK_PRINT("27", [](){ roxe::print((uint8_t)27); });
   CHECK_PRINT("34", [](){ roxe::print((int)34); });
   CHECK_PRINT([](std::string s){return s[0] == 'a';},  [](){ roxe::print((char)'a'); });
   CHECK_PRINT([](std::string s){return s[0] == 'b';},  [](){ roxe::print((int8_t)'b'); });
   CHECK_PRINT("202", [](){ roxe::print((unsigned int)202); });
   CHECK_PRINT("-202", [](){ roxe::print((int)-202); });
   CHECK_PRINT("707", [](){ roxe::print((unsigned long)707); });
   CHECK_PRINT("-707", [](){ roxe::print((long)-707); });
   CHECK_PRINT("909", [](){ roxe::print((unsigned long long)909); });
   CHECK_PRINT("-909", [](){ roxe::print((long long)-909); });
   CHECK_PRINT("404", [](){ roxe::print((uint32_t)404); });
   CHECK_PRINT("-404", [](){ roxe::print((int32_t)-404); });
   CHECK_PRINT("404000000", [](){ roxe::print((uint64_t)404000000); });
   CHECK_PRINT("-404000000", [](){ roxe::print((int64_t)-404000000); });
   CHECK_PRINT("0x0066000000000000", [](){ roxe::print((uint128_t)102); });
   CHECK_PRINT("0xffffff9affffffffffffffffffffffff", [](){ roxe::print((int128_t)-102); });
ROXE_TEST_END

int main(int argc, char** argv) {
   bool verbose = false;
   if( argc >= 2 && std::strcmp( argv[1], "-v" ) == 0 ) {
      verbose = true;
   }
   silence_output(!verbose);

   ROXE_TEST(print_test);
   return has_failed();
}
