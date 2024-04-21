#include "Math.hpp"

float frand(float min, float max) {
  return (max-min)*rand()/RAND_MAX + min;
}

