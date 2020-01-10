/**
 *  @file
 *  @copyright defined in actc/LICENSE
 */
#include "noop.hpp"

using namespace actc;

void noop::anyaction( name                       from,
                      const ignore<std::string>& type,
                      const ignore<std::string>& data )
{
   require_auth( from );
}
