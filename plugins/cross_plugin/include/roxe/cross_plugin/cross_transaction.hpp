//
// Created by ShadowBlade on 2020/12/25.
//

#ifndef ROXE_CROSS_TRANSACTION_HPP
#define ROXE_CROSS_TRANSACTION_HPP

#endif //ROXE_CROSS_TRANSACTION_HPP

#include <roxe/chain_plugin/chain_plugin.hpp>

namespace roxe {
    /**
     *
     */
    class cross_transaction
    {
    public:
        cross_transaction();
        virtual ~cross_transaction();

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
