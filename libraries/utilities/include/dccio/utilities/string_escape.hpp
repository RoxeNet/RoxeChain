/**
 *  @file
 *  @copyright defined in dcc/LICENSE.txt
 */
#pragma once

#include <string>

namespace dccio { namespace utilities {

  std::string escape_string_for_c_source_code(const std::string& input);

} } // end namespace dccio::utilities
