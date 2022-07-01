/**
 *  @file
 *  @copyright defined in roxe/LICENSE
 */
#pragma once
#include <appbase/application.hpp>
#include <fc/exception/exception.hpp>
#include <fc/reflect/reflect.hpp>

#include <roxe/chain_plugin/chain_plugin.hpp>


namespace roxe {
   using namespace appbase;

    struct cross_plugin_defaults {
        //
        string default_unix_socket_path;
        //
        string default_eth_socket_host;
        //
        uint16_t default_eth_socket_port{0};
    };


   /**
    *  This plugin
    *
    *  The handler will be called from the appbase application io_service
    *  thread.  The callback can be called from any thread and will
    *  automatically propagate the call to the http thread.
    *
    */
   class cross_plugin : public appbase::plugin<cross_plugin>
   {
      public:
        cross_plugin();
        virtual ~cross_plugin();

        //must be called before initialize
        static void set_defaults(const cross_plugin_defaults config);

        APPBASE_PLUGIN_REQUIRES((chain_plugin))
        virtual void set_program_options(options_description&, options_description& cfg) override;

        void plugin_initialize(const variables_map& options);
        void plugin_startup();
        void plugin_shutdown();

        // standard exception handling for api handlers
        static void handle_exception( const char *api_name, const char *call_name, const string& body, url_response_callback cb );

        bool verbose_errors()const;

      private:
        std::unique_ptr<class cross_plugin_impl> my;
   };

   /**
    * @brief Structure used to create JSON error responses
    */
   struct error_results {
      uint16_t code;
      string message;

      struct error_info {
         int64_t code;
         string name;
         string what;

         struct error_detail {
            string message;
            string file;
            uint64_t line_number;
            string method;
         };

         vector<error_detail> details;

         static const uint8_t details_limit = 10;

         error_info() {};

         error_info(const fc::exception& exc, bool include_full_log) {
            code = exc.code();
            name = exc.name();
            what = exc.what();
            uint8_t limit = include_full_log ? details_limit : 1;
            for( auto itr = exc.get_log().begin(); itr != exc.get_log().end(); ++itr ) {
               // Prevent sending trace that are too big
               if( details.size() >= limit ) break;
               // Append error
               error_detail detail = {
                     include_full_log ? itr->get_message() : itr->get_limited_message(),
                     itr->get_context().get_file(),
                     itr->get_context().get_line_number(),
                     itr->get_context().get_method()
               };
               details.emplace_back( detail );
            }
         }
      };

      error_info error;
   };
}

FC_REFLECT(roxe::error_results::error_info::error_detail, (message)(file)(line_number)(method))
FC_REFLECT(roxe::error_results::error_info, (code)(name)(what)(details))
FC_REFLECT(roxe::error_results, (code)(message)(error))
FC_REFLECT(roxe::cross_plugin::get_supported_apis_result, (apis))
