// The geometry package provides an implementation of entities used  :
// . for algebraic calculation such as "XYZ" coordinates, "Mat"
// matrix
// . for basis analytic geometry such as Transformations, point,
// vector, line, plane, axis placement, conics, and elementary
// surfaces.


#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <glm/glm.hpp>
#include <vector>

#include "precision.h"

// Defines some geometry objects.
// -----------------------------

// Defines a 3D cartesian point. 
using gp_Pnt = glm::vec<3, double>;

// Defines a 2D cartesian point.
using gp_Pnt2d = glm::vec<2, double>;

// Defines a non-persistent vector in 3D space.
using gp_Vec = glm::vec<3, double>;

// Defines a non-persistent vector in 2D space.
using gp_Vec2d = glm::vec<2, double>;

// Defines a 3D cartesian point sequence.
using gp_Array1OfPnt = std::vector<gp_Pnt>;


// Defines some constants for geometric computations.
// -------------------------------------------------

// Defines the tolerance criterion used to determine when two numbers can be considered equal.
const double gp_Resolution = Precision::RealSmall();

// Provides information about the continuity of a curve.
enum Geom_Continuity 
{
  Geom_C0, Geom_G1, Geom_C1, Geom_G2,
  Geom_C2, Geom_C3, Geom_CN
};

#endif