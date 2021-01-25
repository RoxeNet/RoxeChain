/**
 *  @file
 *  @copyright defined in roxe/LICENSE
 */
#include <roxe/cross_plugin/cross_plugin.hpp>
#include <roxe/cross_plugin/local_endpoint.hpp>
#include <roxe/chain/exceptions.hpp>
#include <roxe/chain/thread_utils.hpp>

#include <fc/network/ip.hpp>
#include <fc/log/logger_config.hpp>
#include <fc/reflect/variant.hpp>
#include <fc/io/json.hpp>
#include <fc/crypto/openssl.hpp>

#include <boost/asio.hpp>
#include <boost/optional.hpp>

#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/config/asio.hpp>
#include <websocketpp/server.hpp>
#include <websocketpp/config/asio_client.hpp>
#include <websocketpp/client.hpp>
#include <websocketpp/logger/stub.hpp>

#include <thread>
#include <memory>
#include <regex>

namespace roxe {

   static appbase::abstract_plugin& _cross_plugin = app().register_plugin<cross_plugin>();

   namespace asio = boost::asio;

   using std::map;
   using std::vector;
   using std::set;
   using std::string;
   using std::regex;
   using boost::optional;
   using boost::asio::ip::tcp;
   using boost::asio::ip::address_v4;
   using boost::asio::ip::address_v6;
   using std::shared_ptr;
   using websocketpp::connection_hdl;

   enum https_ecdh_curve_t {
      SECP384R1,
      PRIME256V1
   };

   static cross_plugin_defaults current_cross_plugin_defaults;

   void cross_plugin::set_defaults(const cross_plugin_defaults config) {
      current_cross_plugin_defaults = config;
   }
   
   static bool verbose_cross_errors = false;
   
   class cross_plugin_impl {
      public:
       ///FIXME for
       chain_plugin*          chain_plug = nullptr;


   };

   template<>
   bool cross_plugin_impl::allow_host<detail::asio_local_with_stub_log>(const detail::asio_local_with_stub_log::request_type& req, websocketpp::server<detail::asio_local_with_stub_log>::connection_ptr con) {
      return true;
   }

   cross_plugin::cross_plugin():my(new cross_plugin_impl()){
      app().register_config_type<https_ecdh_curve_t>();
   }
   cross_plugin::~cross_plugin(){}

   void cross_plugin::set_program_options(options_description&, options_description& cfg) {
      if(current_cross_plugin_defaults.default_unix_socket_path.length())
         cfg.add_options()
            ("unix-socket-path", bpo::value<string>()->default_value(current_cross_plugin_defaults.default_unix_socket_path),
             "The filename (relative to data-dir) to create a unix socket for HTTP RPC; set blank to disable.");

      if(current_cross_plugin_defaults.default_http_port)
         cfg.add_options()
            ("http-server-address", bpo::value<string>()->default_value("127.0.0.1:" + std::to_string(current_cross_plugin_defaults.default_http_port)),
             "The local IP and port to listen for incoming http connections; set blank to disable.");
      else
         cfg.add_options()
            ("http-server-address", bpo::value<string>(),
             "The local IP and port to listen for incoming http connections; leave blank to disable.");

      cfg.add_options()
            ("https-server-address", bpo::value<string>(),
             "The local IP and port to listen for incoming https connections; leave blank to disable.")

            ("https-certificate-chain-file", bpo::value<string>(),
             "Filename with the certificate chain to present on https connections. PEM format. Required for https.")

            ("https-private-key-file", bpo::value<string>(),
             "Filename with https private key in PEM format. Required for https")

            ("access-control-allow-origin", bpo::value<string>()->notifier([this](const string& v) {
                my->access_control_allow_origin = v;
                ilog("configured http with Access-Control-Allow-Origin: ${o}", ("o", my->access_control_allow_origin));
             }),
             "Specify the Access-Control-Allow-Origin to be returned on each request.")

            ("access-control-allow-headers", bpo::value<string>()->notifier([this](const string& v) {
                my->access_control_allow_headers = v;
                ilog("configured http with Access-Control-Allow-Headers : ${o}", ("o", my->access_control_allow_headers));
             }),
             "Specify the Access-Control-Allow-Headers to be returned on each request.")

            ("access-control-allow-credentials",
             bpo::bool_switch()->notifier([this](bool v) {
                my->access_control_allow_credentials = v;
                if (v) ilog("configured http with Access-Control-Allow-Credentials: true");
             })->default_value(false),
             "Specify if Access-Control-Allow-Credentials: true should be returned on each request.")
            ("verbose-cross-errors", bpo::bool_switch()->default_value(false),
             "Append the error log to cross plugin")
            ("http-validate-host", boost::program_options::value<bool>()->default_value(true),
             "If set to false, then any incoming \"Host\" header is considered valid")
            ("http-alias", bpo::value<std::vector<string>>()->composing(),
             "Additionaly acceptable values for the \"Host\" header of incoming HTTP requests, can be specified multiple times.  Includes http/s_server_address by default.")
            ("http-threads", bpo::value<uint16_t>()->default_value( my->thread_pool_size ),
             "Number of worker threads in http thread pool")
            ;
   }

   void cross_plugin::plugin_initialize(const variables_map& options) {
      try {
          my->chain_plug = app().find_plugin<chain_plugin>();

      } FC_LOG_AND_RETHROW()
   }

   void cross_plugin::plugin_startup() {

   }

   void cross_plugin::plugin_shutdown() {

   }

   void cross_plugin::handle_exception( const char *api_name, const char *call_name, const string& body, url_response_callback cb ) {
      try {
         try {
            throw;
         } catch (chain::unknown_block_exception& e) {
            error_results results{400, "Unknown Block", error_results::error_info(e, verbose_cross_errors)};
            cb( 400, fc::variant( results ));
         } catch (chain::unsatisfied_authorization& e) {
            error_results results{401, "UnAuthorized", error_results::error_info(e, verbose_cross_errors)};
            cb( 401, fc::variant( results ));
         } catch (chain::tx_duplicate& e) {
            error_results results{409, "Conflict", error_results::error_info(e, verbose_cross_errors)};
            cb( 409, fc::variant( results ));
         } catch (fc::eof_exception& e) {
            error_results results{422, "Unprocessable Entity", error_results::error_info(e, verbose_cross_errors)};
            cb( 422, fc::variant( results ));
            elog( "Unable to parse arguments to ${api}.${call}", ("api", api_name)( "call", call_name ));
            dlog("Bad arguments: ${args}", ("args", body));
         } catch (fc::exception& e) {
            error_results results{500, "Internal Service Error", error_results::error_info(e, verbose_cross_errors)};
            cb( 500, fc::variant( results ));
            if (e.code() != chain::greylist_net_usage_exceeded::code_value && e.code() != chain::greylist_cpu_usage_exceeded::code_value) {
               elog( "FC Exception encountered while processing ${api}.${call}",
                     ("api", api_name)( "call", call_name ));
               dlog( "Exception Details: ${e}", ("e", e.to_detail_string()));
            }
         } catch (std::exception& e) {
            error_results results{500, "Internal Service Error", error_results::error_info(fc::exception( FC_LOG_MESSAGE( error, e.what())), verbose_cross_errors)};
            cb( 500, fc::variant( results ));
            elog( "STD Exception encountered while processing ${api}.${call}",
                  ("api", api_name)( "call", call_name ));
            dlog( "Exception Details: ${e}", ("e", e.what()));
         } catch (...) {
            error_results results{500, "Internal Service Error",
               error_results::error_info(fc::exception( FC_LOG_MESSAGE( error, "Unknown Exception" )), verbose_cross_errors)};
            cb( 500, fc::variant( results ));
            elog( "Unknown Exception encountered while processing ${api}.${call}",
                  ("api", api_name)( "call", call_name ));
         }
      } catch (...) {
         std::cerr << "Exception attempting to handle exception for " << api_name << "." << call_name << std::endl;
      }
   }


   bool cross_plugin::verbose_errors()const {
      return verbose_cross_errors;
   }


}
