#pragma once

/**
 * Define specific things for the roxe system
 */

extern "C" {
   void roxe_assert(unsigned int, const char*);
   void __cxa_pure_virtual() { roxe_assert(false, "pure virtual method called"); }
}
