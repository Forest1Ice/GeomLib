#include "geom_Curve.h"

gp_Pnt Geom_Curve::Value(const double u) const
{
    gp_Pnt p;
    D0(u, p);
    return p;
}