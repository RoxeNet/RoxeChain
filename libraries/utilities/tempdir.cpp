/**
 *  @file
 *  @copyright defined in dcc/LICENSE.txt
 */

#include <dccio/utilities/tempdir.hpp>

#include <cstdlib>

namespace dccio { namespace utilities {

fc::path temp_directory_path()
{
   const char* dcc_tempdir = getenv("dcc_TEMPDIR");
   if( dcc_tempdir != nullptr )
      return fc::path( dcc_tempdir );
   return fc::temp_directory_path() / "dcc-tmp";
}

} } // dccio::utilities
