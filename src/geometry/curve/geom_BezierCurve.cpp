#include "geom_BezierCurve.h"

Geom_BezierCurve::Geom_BezierCurve(const gp_Array1OfPnt& poles)
{
    int nbPoles = poles.size();

    if(nbPoles < 2 || nbPoles > (MaxDegree() + 1))
    {
        
    }
}