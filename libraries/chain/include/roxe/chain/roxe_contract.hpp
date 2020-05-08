/**
 *  @file
 *  @copyright defined in roxe/LICENSE
 */
#pragma once

#include <roxe/chain/types.hpp>
#include <roxe/chain/contract_types.hpp>

namespace roxe { namespace chain {

   class apply_context;

   /**
    * @defgroup native_action_handlers Native Action Handlers
    */
   ///@{
   void apply_roxe_newaccount(apply_context&);
   void apply_roxe_updateauth(apply_context&);
   void apply_roxe_deleteauth(apply_context&);
   void apply_roxe_linkauth(apply_context&);
   void apply_roxe_unlinkauth(apply_context&);

   /*
   void apply_roxe_postrecovery(apply_context&);
   void apply_roxe_passrecovery(apply_context&);
   void apply_roxe_vetorecovery(apply_context&);
   */

   void apply_roxe_setcode(apply_context&);
   void apply_roxe_setabi(apply_context&);

   void apply_roxe_canceldelay(apply_context&);
   ///@}  end action handlers

} } /// namespace roxe::chain
