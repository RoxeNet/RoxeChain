/**
 *  @file
 *  @copyright defined in actc/LICENSE
 */
#pragma once
#include "../../core/actc/time.hpp"
#include "../../core/actc/check.hpp"

namespace actc {
  namespace internal_use_do_not_use {
    extern "C" {
      __attribute__((actc_wasm_import, noreturn))
      void actc_exit( int32_t code );
    }
  }

  /**
   *  @addtogroup system System
   *  @ingroup contracts
   *  @brief Defines time related functions and actc_exit
   */

   /**
    *  This method will abort execution of wasm without failing the contract. This is used to bypass all cleanup / destructors that would normally be called.
    *
    *  @ingroup system
    *  @param code - the exit code
    *  Example:
    *
    *  @code
    *  actc_exit(0);
    *  actc_exit(1);
    *  actc_exit(2);
    *  actc_exit(3);
    *  @endcode
    */
   inline void actc_exit( int32_t code ) {
     internal_use_do_not_use::actc_exit(code);
   }

   /**
   *  Returns the time in microseconds from 1970 of the current block as a time_point
   *
   *  @ingroup system
   *  @return time in microseconds from 1970 of the current block as a time_point
   */
   time_point current_time_point();

   /**
   *  Returns the time in microseconds from 1970 of the current block as a block_timestamp
   *
   *  @ingroup system
   *  @return time in microseconds from 1970 of the current block as a block_timestamp
   */
   block_timestamp current_block_time();
}
