/**
 *  @file
 *  @copyright defined in actc/LICENSE.txt
 */

#include <actc/utilities/tempdir.hpp>

#include <cstdlib>

namespace actc { namespace utilities {

fc::path temp_directory_path()
{
   const char* actc_tempdir = getenv("actc_TEMPDIR");
   if( actc_tempdir != nullptr )
      return fc::path( actc_tempdir );
   return fc::temp_directory_path() / "actc-tmp";
}

} } // actc::utilities
