/**
 *  @file
 *  @copyright defined in actc/LICENSE
 */
#include "core/actc/crypto.hpp"
#include "core/actc/datastream.hpp"

extern "C" {
   struct __attribute__((aligned (16))) capi_checksum160 { uint8_t hash[20]; };
   struct __attribute__((aligned (16))) capi_checksum256 { uint8_t hash[32]; };
   struct __attribute__((aligned (16))) capi_checksum512 { uint8_t hash[64]; };
   __attribute__((actc_wasm_import))
   void assert_sha256( const char* data, uint32_t length, const capi_checksum256* hash );

   __attribute__((actc_wasm_import))
   void assert_sha1( const char* data, uint32_t length, const capi_checksum160* hash );
   
   __attribute__((actc_wasm_import))
   void assert_sha512( const char* data, uint32_t length, const capi_checksum512* hash );

   __attribute__((actc_wasm_import))
   void assert_ripemd160( const char* data, uint32_t length, const capi_checksum160* hash );

   __attribute__((actc_wasm_import))
   void sha256( const char* data, uint32_t length, capi_checksum256* hash );

   __attribute__((actc_wasm_import))
   void sha1( const char* data, uint32_t length, capi_checksum160* hash );

   __attribute__((actc_wasm_import))
   void sha512( const char* data, uint32_t length, capi_checksum512* hash );

   __attribute__((actc_wasm_import))
   void ripemd160( const char* data, uint32_t length, capi_checksum160* hash );

   __attribute__((actc_wasm_import))
   int recover_key( const capi_checksum256* digest, const char* sig, 
                    size_t siglen, char* pub, size_t publen );

   __attribute__((actc_wasm_import))
   void assert_recover_key( const capi_checksum256* digest, const char* sig, 
                            size_t siglen, const char* pub, size_t publen );

}

namespace actc {

   void assert_sha256( const char* data, uint32_t length, const actc::checksum256& hash ) {
      auto hash_data = hash.extract_as_byte_array();
      ::assert_sha256( data, length, reinterpret_cast<const ::capi_checksum256*>(hash_data.data()) );
   }

   void assert_sha1( const char* data, uint32_t length, const actc::checksum160& hash ) {
      auto hash_data = hash.extract_as_byte_array();
      ::assert_sha1( data, length, reinterpret_cast<const ::capi_checksum160*>(hash_data.data()) );
   }

   void assert_sha512( const char* data, uint32_t length, const actc::checksum512& hash ) {
      auto hash_data = hash.extract_as_byte_array();
      ::assert_sha512( data, length, reinterpret_cast<const ::capi_checksum512*>(hash_data.data()) );
   }

   void assert_ripemd160( const char* data, uint32_t length, const actc::checksum160& hash ) {
      auto hash_data = hash.extract_as_byte_array();
      ::assert_ripemd160( data, length, reinterpret_cast<const ::capi_checksum160*>(hash_data.data()) );
   }

   actc::checksum256 sha256( const char* data, uint32_t length ) {
      ::capi_checksum256 hash;
      ::sha256( data, length, &hash );
      return {hash.hash};
   }

   actc::checksum160 sha1( const char* data, uint32_t length ) {
      ::capi_checksum160 hash;
      ::sha1( data, length, &hash );
      return {hash.hash};
   }

   actc::checksum512 sha512( const char* data, uint32_t length ) {
      ::capi_checksum512 hash;
      ::sha512( data, length, &hash );
      return {hash.hash};
   }

   actc::checksum160 ripemd160( const char* data, uint32_t length ) {
      ::capi_checksum160 hash;
      ::ripemd160( data, length, &hash );
      return {hash.hash};
   }

   actc::public_key recover_key( const actc::checksum256& digest, const actc::signature& sig ) {
      auto digest_data = digest.extract_as_byte_array();

      char sig_data[70];
      actc::datastream<char*> sig_ds( sig_data, sizeof(sig_data) );
      auto sig_begin = sig_ds.pos();
      sig_ds << sig;

      char pubkey_data[38];
      size_t pubkey_size = ::recover_key( reinterpret_cast<const capi_checksum256*>(digest_data.data()),
                                          sig_begin, (sig_ds.pos() - sig_begin),
                                          pubkey_data, sizeof(pubkey_data) );
      actc::datastream<char*> pubkey_ds( pubkey_data, pubkey_size );
      actc::public_key pubkey;
      pubkey_ds >> pubkey;
      return pubkey;
   }

   void assert_recover_key( const actc::checksum256& digest, const actc::signature& sig, const actc::public_key& pubkey ) {
      auto digest_data = digest.extract_as_byte_array();

      char sig_data[70];
      actc::datastream<char*> sig_ds( sig_data, sizeof(sig_data) );
      auto sig_begin = sig_ds.pos();
      sig_ds << sig;

      char pubkey_data[38];
      actc::datastream<char*> pubkey_ds( pubkey_data, sizeof(pubkey_data) );
      auto pubkey_begin = pubkey_ds.pos();
      pubkey_ds << pubkey;

      ::assert_recover_key( reinterpret_cast<const capi_checksum256*>(digest_data.data()),
                            sig_begin, (sig_ds.pos() - sig_begin),
                            pubkey_begin, (pubkey_ds.pos() - pubkey_begin) );
   }

}
