#include <dccio/chain/block_state.hpp>
#include <dccio/chain/exceptions.hpp>

namespace dccio { namespace chain {

   block_state::block_state( const block_header_state& prev, block_timestamp_type when )
   :block_header_state( prev.generate_next( when ) ), 
    block( std::make_shared<signed_block>()  )
   {
      static_cast<block_header&>(*block) = header;
   }

   block_state::block_state( const block_header_state& prev, signed_block_ptr b, bool trust )
   :block_header_state( prev.next( *b, trust )), block( move(b) )
   { } 



} } /// dccio::chain
