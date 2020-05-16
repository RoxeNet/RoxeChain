/**
 *  @file
 *  @copyright defined in roxe/LICENSE
 */
#include "noop.hpp"

using namespace roxe;

void noop::anyaction( name                       from,
                      const ignore<std::string>& type,
                      const ignore<std::string>& data )
{
   require_auth( from );
}
