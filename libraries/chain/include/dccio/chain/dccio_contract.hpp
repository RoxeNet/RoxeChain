/**
 *  @file
 *  @copyright defined in dcc/LICENSE.txt
 */
#pragma once

#include <dccio/chain/types.hpp>
#include <dccio/chain/contract_types.hpp>

namespace dccio { namespace chain {

   class apply_context;

   /**
    * @defgroup native_action_handlers Native Action Handlers
    */
   ///@{
   void apply_dccio_newaccount(apply_context&);
   void apply_dccio_updateauth(apply_context&);
   void apply_dccio_deleteauth(apply_context&);
   void apply_dccio_linkauth(apply_context&);
   void apply_dccio_unlinkauth(apply_context&);

   /*
   void apply_dccio_postrecovery(apply_context&);
   void apply_dccio_passrecovery(apply_context&);
   void apply_dccio_vetorecovery(apply_context&);
   */

   void apply_dccio_setcode(apply_context&);
   void apply_dccio_setabi(apply_context&);

   void apply_dccio_canceldelay(apply_context&);
   ///@}  end action handlers

} } /// namespace dccio::chain
