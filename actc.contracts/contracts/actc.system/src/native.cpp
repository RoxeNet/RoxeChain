#include <actc.system/native.hpp>

#include <actc/check.hpp>

namespace actc {
   bool is_feature_activated( const actc::checksum256& feature_digest ) {
      auto feature_digest_data = feature_digest.extract_as_byte_array();
      return internal_use_do_not_use::is_feature_activated(
         reinterpret_cast<const ::capi_checksum256*>( feature_digest_data.data() )
      );
   }

   void preactivate_feature( const actc::checksum256& feature_digest ) {
      auto feature_digest_data = feature_digest.extract_as_byte_array();
      internal_use_do_not_use::preactivate_feature(
         reinterpret_cast<const ::capi_checksum256*>( feature_digest_data.data() )
      );
   }
}

namespace actcsystem {

   void native::onerror( ignore<uint128_t>, ignore<std::vector<char>> ) {
      actc::check( false, "the onerror action cannot be called directly" );
   }

}
