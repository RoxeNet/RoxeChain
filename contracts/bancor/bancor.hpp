/**
 *  @file
 *  @copyright defined in actc/LICENSE.txt
 */
#pragma once

#include <actclib/actc.hpp>
#include <actclib/token.hpp>
#include <actclib/reflect.hpp>
#include <actclib/generic_currency.hpp>

#include <bancor/converter.hpp>
#include <currency/currency.hpp>

namespace bancor {
   typedef actc::generic_currency< actc::token<N(other),S(4,OTHER)> >  other_currency;
   typedef actc::generic_currency< actc::token<N(bancor),S(4,RELAY)> > relay_currency;
   typedef actc::generic_currency< actc::token<N(currency),S(4,CUR)> > cur_currency;

   typedef converter<relay_currency, other_currency, cur_currency > example_converter;
} /// bancor

