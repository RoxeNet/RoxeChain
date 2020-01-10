/**
 *  @file
 *  @copyright defined in actc/LICENSE
 */
#pragma once

#include <actc/actc.hpp>

namespace actc {
   namespace internal_use_do_not_use {
      extern "C" {
         __attribute__((actc_wasm_import))
         uint64_t get_sender();
      }
   }
}

namespace actc {
   name get_sender() {
      return name( internal_use_do_not_use::get_sender() );
   }
}

class [[actc::contract]] get_sender_test : public actc::contract {
public:
   using actc::contract::contract;

   [[actc::action]]
   void assertsender( actc::name expected_sender );
   using assertsender_action = actc::action_wrapper<"assertsender"_n, &get_sender_test::assertsender>;

   [[actc::action]]
   void sendinline( actc::name to, actc::name expected_sender );

   [[actc::action]]
   void notify( actc::name to, actc::name expected_sender, bool send_inline );

   // actc.cdt 1.6.1 has a problem with "*::notify" so hardcode to tester1 for now.
   // TODO: Change it back to "*::notify" when the bug is fixed in actc.cdt.
   [[actc::on_notify("tester1::notify")]]
   void on_notify( actc::name to, actc::name expected_sender, bool send_inline );

};
