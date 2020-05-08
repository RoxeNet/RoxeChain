/**
 *  @file
 *  @copyright defined in roxe/LICENSE
 */
#pragma once
#include "../../core/roxe/time.hpp"
#include "../../core/roxe/check.hpp"

namespace roxe {
  namespace internal_use_do_not_use {
    extern "C" {
      __attribute__((roxe_wasm_import, noreturn))
      void roxe_exit( int32_t code );
    }
  }

  /**
   *  @addtogroup system System
   *  @ingroup contracts
   *  @brief Defines time related functions and roxe_exit
   */

   /**
    *  This method will abort execution of wasm without failing the contract. This is used to bypass all cleanup / destructors that would normally be called.
    *
    *  @ingroup system
    *  @param code - the exit code
    *  Example:
    *
    *  @code
    *  roxe_exit(0);
    *  roxe_exit(1);
    *  roxe_exit(2);
    *  roxe_exit(3);
    *  @endcode
    */
   inline void roxe_exit( int32_t code ) {
     internal_use_do_not_use::roxe_exit(code);
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
