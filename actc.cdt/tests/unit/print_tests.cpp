#include <actc/actc.hpp>
#include <actc/tester.hpp>

using namespace actc::native;

ACTC_TEST_BEGIN(print_test)
   CHECK_PRINT("27", [](){ actc::print((uint8_t)27); });
   CHECK_PRINT("34", [](){ actc::print((int)34); });
   CHECK_PRINT([](std::string s){return s[0] == 'a';},  [](){ actc::print((char)'a'); });
   CHECK_PRINT([](std::string s){return s[0] == 'b';},  [](){ actc::print((int8_t)'b'); });
   CHECK_PRINT("202", [](){ actc::print((unsigned int)202); });
   CHECK_PRINT("-202", [](){ actc::print((int)-202); });
   CHECK_PRINT("707", [](){ actc::print((unsigned long)707); });
   CHECK_PRINT("-707", [](){ actc::print((long)-707); });
   CHECK_PRINT("909", [](){ actc::print((unsigned long long)909); });
   CHECK_PRINT("-909", [](){ actc::print((long long)-909); });
   CHECK_PRINT("404", [](){ actc::print((uint32_t)404); });
   CHECK_PRINT("-404", [](){ actc::print((int32_t)-404); });
   CHECK_PRINT("404000000", [](){ actc::print((uint64_t)404000000); });
   CHECK_PRINT("-404000000", [](){ actc::print((int64_t)-404000000); });
   CHECK_PRINT("0x0066000000000000", [](){ actc::print((uint128_t)102); });
   CHECK_PRINT("0xffffff9affffffffffffffffffffffff", [](){ actc::print((int128_t)-102); });
ACTC_TEST_END

int main(int argc, char** argv) {
   bool verbose = false;
   if( argc >= 2 && std::strcmp( argv[1], "-v" ) == 0 ) {
      verbose = true;
   }
   silence_output(!verbose);

   ACTC_TEST(print_test);
   return has_failed();
}
