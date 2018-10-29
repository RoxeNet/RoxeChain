/**
 *  @file
 *  @copyright defined in dcc/LICENSE.txt
 */
#pragma once

#include <dcciolib/dccio.hpp>
#include <dcciolib/token.hpp>
#include <dcciolib/reflect.hpp>
#include <dcciolib/generic_currency.hpp>

#include <bancor/converter.hpp>
#include <currency/currency.hpp>

namespace bancor {
   typedef dccio::generic_currency< dccio::token<N(other),S(4,OTHER)> >  other_currency;
   typedef dccio::generic_currency< dccio::token<N(bancor),S(4,RELAY)> > relay_currency;
   typedef dccio::generic_currency< dccio::token<N(currency),S(4,CUR)> > cur_currency;

   typedef converter<relay_currency, other_currency, cur_currency > example_converter;
} /// bancor

