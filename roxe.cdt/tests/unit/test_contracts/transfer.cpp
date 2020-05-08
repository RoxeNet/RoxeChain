#include <roxe/roxe.hpp>
#include <roxe/asset.hpp>

using namespace roxe;

CONTRACT transfer_contract : public contract {
   public:
      using contract::contract;

      ACTION transfer(name from, name to, asset quantity, std::string memo) {
         require_recipient(from);
         print_f("transfered : % -> % ? % (%)\n", from, to, quantity, memo);
      }

      ACTION transfer2(name from, name to, asset quantity, std::string memo) {
         require_recipient(from);
         print_f("transfered : % -> % ? % (%)\n", from, to, quantity, memo);
      }

      ACTION transfer3(name from, name to, asset quantity, std::string memo) {
         require_recipient(from);
         print_f("transfered : % -> % ? % (%)\n", from, to, quantity, memo);
      }
};
