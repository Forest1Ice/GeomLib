// The abstract class Curve describes the common behavior of curves in 3D space. 

#ifndef GEOM_CURVE_H
#define GEOM_CURVE_H

#include "geometry.h"
#include "utils.h"

class Geom_Curve
{
public:
    // Returns the value of the first parameter.
    virtual double FirstParameter() const = 0;

    // Returns the value of the last parameter.
    virtual double LastParameter() const = 0;

    // Returns true if the curve is closed.
    virtual bool IsClosed() const = 0;

    // Returns the global continuity of the curve.
    virtual Geom_Continuity Continuity() const = 0;

    // Returns in p the point of parameter u.
    virtual void D0 (const double u, gp_Pnt& p) const = 0;

    // Returns the point p of parameter u and the first derivative v1.
    // Raised if the continuity of the curve is not C1.
    virtual void D1 (const double u, gp_Pnt& p, gp_Vec& v1) const = 0;

    // Returns the point p of parameter u, the first and second derivatives v1 and v2.
    // Raised if the continuity of the curve is not C2.
    virtual void D2 (const double u, gp_Pnt& p, gp_Vec& v1, gp_Vec& v2) const = 0;

    // The returned vector gives the value of the derivative for the order of derivation n.
    // Raised if the continuity of the curve is not CN.
    virtual gp_Vec DN(const double u, const int n) const = 0;

    // Returns true if the degree of continuity of this curve is at least N.
    virtual bool IsCN(const int n) const = 0;

    // Creates a new object which is a copy of this curve.
    virtual handle<Geom_Curve> Copy() const = 0;

    // Computes the point of parameter u.
    gp_Pnt Value(const double u) const;
};

#endif