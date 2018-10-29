/**
 *  @file
 *  @copyright defined in dcc/LICENSE.txt
 */

#include <dccio/chain/chain_id_type.hpp>
#include <dccio/chain/exceptions.hpp>

namespace dccio { namespace chain {

   void chain_id_type::reflector_verify()const {
      dcc_ASSERT( *reinterpret_cast<const fc::sha256*>(this) != fc::sha256(), chain_id_type_exception, "chain_id_type cannot be zero" );
   }

} }  // namespace dccio::chain

namespace fc {

   void to_variant(const dccio::chain::chain_id_type& cid, fc::variant& v) {
      to_variant( static_cast<const fc::sha256&>(cid), v);
   }

   void from_variant(const fc::variant& v, dccio::chain::chain_id_type& cid) {
      from_variant( v, static_cast<fc::sha256&>(cid) );
   }

} // fc
