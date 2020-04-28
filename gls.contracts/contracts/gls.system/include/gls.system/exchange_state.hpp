#pragma once

#include <actc/asset.hpp>
#include <actc/multi_index.hpp>

namespace actcsystem {

   using actc::asset;
   using actc::symbol;

   /**
    * @addtogroup actcsystem
    * @{
    */

   /**
    * Uses Bancor math to create a 50/50 relay between two asset types.
    *
    * @details The state of the bancor exchange is entirely contained within this struct.
    * There are no external side effects associated with using this API.
    */
   struct [[actc::table, actc::contract("gls.system")]] exchange_state {
      asset    supply;

      struct connector {
         asset balance;
         double weight = .5;

         ACTCLIB_SERIALIZE( connector, (balance)(weight) )
      };

      connector base;
      connector quote;

      uint64_t primary_key()const { return supply.symbol.raw(); }

      asset convert_to_exchange( connector& reserve, const asset& payment );
      asset convert_from_exchange( connector& reserve, const asset& tokens );
      asset convert( const asset& from, const symbol& to );
      asset direct_convert( const asset& from, const symbol& to );

      static int64_t get_bancor_output( int64_t inp_reserve,
                                        int64_t out_reserve,
                                        int64_t inp );
      static int64_t get_bancor_input( int64_t out_reserve,
                                       int64_t inp_reserve,
                                       int64_t out );

      ACTCLIB_SERIALIZE( exchange_state, (supply)(base)(quote) )
   };

   typedef actc::multi_index< "rammarket"_n, exchange_state > rammarket;
   /** @}*/ // enf of @addtogroup actcsystem
} /// namespace actcsystem
