#include "AmbientLight.hpp"

AmbientLight::AmbientLight(const Color& ac0, const float ap0) {
  ac = ac0;
  ap = ap0;
}

Lightning AmbientLight::light(const Intersection&, const float) {
  return Lightning(ac*ap, Color(), Color());
}

