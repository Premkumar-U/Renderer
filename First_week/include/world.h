#ifndef WORLD_H
#define WORLD_H

#include <memory>
#include <vector>

#include "ray_traceable.h"

using World = std::vector<std::unique_ptr<ray_traceable>>;

#endif