/**
 *  @file
 *  @copyright defined in roxe/LICENSE
 */
#pragma once

#include <roxe/roxe.hpp>

namespace roxe {
   namespace internal_use_do_not_use {
      extern "C" {
         __attribute__((roxe_wasm_import))
         uint64_t get_sender();
      }
   }
}

namespace roxe {
   name get_sender() {
      return name( internal_use_do_not_use::get_sender() );
   }
}

class [[roxe::contract]] get_sender_test : public roxe::contract {
public:
   using roxe::contract::contract;

   [[roxe::action]]
   void assertsender( roxe::name expected_sender );
   using assertsender_action = roxe::action_wrapper<"assertsender"_n, &get_sender_test::assertsender>;

   [[roxe::action]]
   void sendinline( roxe::name to, roxe::name expected_sender );

   [[roxe::action]]
   void notify( roxe::name to, roxe::name expected_sender, bool send_inline );

   // roxe.cdt 1.6.1 has a problem with "*::notify" so hardcode to tester1 for now.
   // TODO: Change it back to "*::notify" when the bug is fixed in roxe.cdt.
   [[roxe::on_notify("tester1::notify")]]
   void on_notify( roxe::name to, roxe::name expected_sender, bool send_inline );

};
