#pragma once

/**
 * Define specific things for the actc system
 */

extern "C" {
   void actc_assert(unsigned int, const char*);
   void __cxa_pure_virtual() { actc_assert(false, "pure virtual method called"); }
}
