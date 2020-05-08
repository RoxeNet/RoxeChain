/**
 *  @file
 *  @copyright defined in roxe/LICENSE
 */

#include <roxe/chain/genesis_state.hpp>

// these are required to serialize a genesis_state
#include <fc/smart_ref_impl.hpp>   // required for gcc in release mode

namespace roxe { namespace chain {

genesis_state::genesis_state() {
    /// TODO genesis time
   initial_timestamp = fc::time_point::from_iso_string( "2020-01-01T12:00:00" );
   initial_key = fc::variant(roxe_root_key).as<public_key_type>();
}

chain::chain_id_type genesis_state::compute_chain_id() const {
   digest_type::encoder enc;
   fc::raw::pack( enc, *this );
   return chain_id_type{enc.result()};
}

} } // namespace roxe::chain
