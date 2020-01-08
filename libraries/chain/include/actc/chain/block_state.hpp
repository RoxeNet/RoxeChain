/**
 *  @file
 *  @copyright defined in actc/LICENSE
 */
#pragma once

#include <actc/chain/block_header_state.hpp>
#include <actc/chain/block.hpp>
#include <actc/chain/transaction_metadata.hpp>
#include <actc/chain/action_receipt.hpp>

namespace actc { namespace chain {

   struct block_state : public block_header_state {
      block_state( const block_header_state& prev,
                   signed_block_ptr b,
                   const std::function<void( block_timestamp_type,
                                             const flat_set<digest_type>&,
                                             const vector<digest_type>& )>& validator,
                   bool skip_validate_signee
                 );

      block_state( pending_block_header_state&& cur,
                   signed_block_ptr&& b, // unsigned block
                   vector<transaction_metadata_ptr>&& trx_metas,
                   const std::function<void( block_timestamp_type,
                                             const flat_set<digest_type>&,
                                             const vector<digest_type>& )>& validator,
                   const std::function<signature_type(const digest_type&)>& signer
                );

      block_state( pending_block_header_state&& cur,
                   const signed_block_ptr& b, // signed block
                   vector<transaction_metadata_ptr>&& trx_metas,
                   const std::function<void( block_timestamp_type,
                                             const flat_set<digest_type>&,
                                             const vector<digest_type>& )>& validator,
                   bool skip_validate_signee
                 );

      block_state() = default;

      bool is_valid()const { return validated; }


      signed_block_ptr                                    block;
      bool                                                validated = false;

      /// this data is redundant with the data stored in block, but facilitates
      /// recapturing transactions when we pop a block
      vector<transaction_metadata_ptr>                    trxs;
   };

   using block_state_ptr = std::shared_ptr<block_state>;

} } /// namespace actc::chain

FC_REFLECT_DERIVED( actc::chain::block_state, (actc::chain::block_header_state), (block)(validated) )
