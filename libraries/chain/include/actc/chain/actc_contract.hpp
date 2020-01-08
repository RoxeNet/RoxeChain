/**
 *  @file
 *  @copyright defined in actc/LICENSE
 */
#pragma once

#include <actc/chain/types.hpp>
#include <actc/chain/contract_types.hpp>

namespace actc { namespace chain {

   class apply_context;

   /**
    * @defgroup native_action_handlers Native Action Handlers
    */
   ///@{
   void apply_actc_newaccount(apply_context&);
   void apply_actc_updateauth(apply_context&);
   void apply_actc_deleteauth(apply_context&);
   void apply_actc_linkauth(apply_context&);
   void apply_actc_unlinkauth(apply_context&);

   /*
   void apply_actc_postrecovery(apply_context&);
   void apply_actc_passrecovery(apply_context&);
   void apply_actc_vetorecovery(apply_context&);
   */

   void apply_actc_setcode(apply_context&);
   void apply_actc_setabi(apply_context&);

   void apply_actc_canceldelay(apply_context&);
   ///@}  end action handlers

} } /// namespace actc::chain
