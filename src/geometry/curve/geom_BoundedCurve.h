// The abstract class BoundedCurve describes the common behavior of bounded curves in 3D space.
// A bounded curve is limited by two finite values of the parameter, termed respectively "first parameter" and "last parameter". 
// The "first parameter" gives the "start point" of the bounded curve, and the "last parameter" gives the "end point" of the bounded curve. 
// The length of a bounded curve is finite.

#ifndef GEOM_BOUNDEDCURVE_H
#define GEOM_BOUNDEDCURVE_H

#include "geom_Curve.h"

class Geom_BoundedCurve: public Geom_Curve
{
public:
    // Returns the start point of the curve.
    virtual gp_Pnt StartPoint() const = 0;

    // Returns the end point of the curve.
    virtual gp_Pnt EndPoint() const = 0;
};

#endif