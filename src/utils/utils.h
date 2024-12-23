#ifndef UTILS_H
#define UTILS_H

#include <vector>

// Type Definition
// ---------------

template <typename Class>
using handle = std::shared_ptr<Class>;

using std_Array1OfReal = std::vector<double>;

#endif