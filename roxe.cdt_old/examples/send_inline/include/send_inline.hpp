#include <roxe/roxe.hpp>
using namespace roxe;

CONTRACT send_inline : public contract {
   public:
      using contract::contract;

      ACTION test( name user, name inline_code );

      using test_action = action_wrapper<"test"_n, &send_inline::test>;
};
