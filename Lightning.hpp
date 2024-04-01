#ifndef LIGHTNING_HPP
#define LIGHTNING_HPP

#include "Color.hpp"

struct Lightning {
  Color a;
  Color d;
  Color s;

  Lightning(const Color& a0, const Color& d0, const Color& s0);
};

#endif
