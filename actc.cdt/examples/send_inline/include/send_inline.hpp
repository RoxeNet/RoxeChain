#include <actc/actc.hpp>
using namespace actc;

CONTRACT send_inline : public contract {
   public:
      using contract::contract;

      ACTION test( name user, name inline_code );

      using test_action = action_wrapper<"test"_n, &send_inline::test>;
};
