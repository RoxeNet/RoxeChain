#pragma once
#include <roxelib/print.hpp>
#include <roxelib/action.hpp>

#include <boost/fusion/adapted/std_tuple.hpp>
#include <boost/fusion/include/std_tuple.hpp>

#include <boost/mp11/tuple.hpp>

#warning "<roxelib/dispatcher.hpp> is deprecated use <roxe/dispatcher.hpp>"

namespace roxe {

   template<typename Contract, typename FirstAction>
   bool dispatch( uint64_t code, uint64_t act ) {
      if( code == FirstAction::get_account() && FirstAction::get_name() == act ) {
         Contract().on( unpack_action_data<FirstAction>() );
         return true;
      }
      return false;
   }


   /**
    * This method will dynamically dispatch an incoming set of actions to
    *
    * ```
    * static Contract::on( ActionType )
    * ```
    *
    * For this to work the Actions must be derived from roxe::contract
    *
    */
   template<typename Contract, typename FirstAction, typename SecondAction, typename... Actions>
   bool dispatch( uint64_t code, uint64_t act ) {
      if( code == FirstAction::get_account() && FirstAction::get_name() == act ) {
         Contract().on( unpack_action_data<FirstAction>() );
         return true;
      }
      return roxe::dispatch<Contract,SecondAction,Actions...>( code, act );
   }

   /**
    * @addtogroup dispatcher Dispatcher C++ API
    * @ingroup core
    * @brief Defines C++ functions to dispatch action to proper action handler inside a contract
    * @{
    */

   /**
    * Unpack the received action and execute the correponding action handler
    *
    * @tparam T - The contract class that has the correponding action handler, this contract should be derived from roxe::contract
    * @tparam Q - The namespace of the action handler function
    * @tparam Args - The arguments that the action handler accepts, i.e. members of the action
    * @param obj - The contract object that has the correponding action handler
    * @param func - The action handler
    * @return true
    */
   template<typename T, typename... Args>
   bool execute_action( name self, name code, void (T::*func)(Args...)  ) {
      size_t size = action_data_size();

      //using malloc/free here potentially is not exception-safe, although WASM doesn't support exceptions
      constexpr size_t max_stack_buffer_size = 512;
      void* buffer = nullptr;
      if( size > 0 ) {
         buffer = max_stack_buffer_size < size ? malloc(size) : alloca(size);
         read_action_data( buffer, size );
      }

      std::tuple<std::decay_t<Args>...> args;
      datastream<const char*> ds((char*)buffer, size);
      ds >> args;

      T inst(self, code, ds);

      auto f2 = [&]( auto... a ){
         ((&inst)->*func)( a... );
      };

      boost::mp11::tuple_apply( f2, args );
      if ( max_stack_buffer_size < size ) {
         free(buffer);
      }
      return true;
   }

   /// @}

 // Helper macro for ROXE_DISPATCH_INTERNAL
 #define ROXE_DISPATCH_INTERNAL( r, OP, elem ) \
    case roxe::name( BOOST_PP_STRINGIZE(elem) ).value: \
       roxe::execute_action( roxe::name(receiver), roxe::name(code), &OP::elem ); \
       break;

 // Helper macro for ROXE_DISPATCH
 #define ROXE_DISPATCH_HELPER( TYPE,  MEMBERS ) \
    BOOST_PP_SEQ_FOR_EACH( ROXE_DISPATCH_INTERNAL, TYPE, MEMBERS )

/**
 * @addtogroup dispatcher
 * Convenient macro to create contract apply handler
 *
 * @note To be able to use this macro, the contract needs to be derived from roxe::contract
 * @param TYPE - The class name of the contract
 * @param MEMBERS - The sequence of available actions supported by this contract
 *
 * Example:
 * @code
 * ROXE_DISPATCH( roxe::bios, (setpriv)(setalimits)(setglimits)(setprods)(reqauth) )
 * @endcode
 */
#define ROXE_DISPATCH( TYPE, MEMBERS ) \
extern "C" { \
   [[roxe::wasm_entry]] \
   void apply( uint64_t receiver, uint64_t code, uint64_t action ) { \
      if( code == receiver ) { \
         switch( action ) { \
            ROXE_DISPATCH_HELPER( TYPE, MEMBERS ) \
         } \
         /* does not allow destructor of thiscontract to run: roxe_exit(0); */ \
      } \
   } \
} \

}
