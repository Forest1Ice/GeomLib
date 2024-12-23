// The Precision package offers a set of functions defining precision criteria
// for use in conventional situations when comparing two numbers.
// It is not advisable to use floating number equality. Instead, the difference
// between numbers must be compared with a given precision, i.e. :
// If ( Abs ( x1 - x2 ) < Precision ) ...
// should be used instead of
// If ( x1 == x2 ) ...
// Likewise, when ordering floating numbers, you must take the following into account :
// If ( x1 < x2 - Precision ) ...
// is incorrect when x1 and x2 are large numbers ; it is better to write :
// If ( x2 - x1 > Precision ) ...

#ifndef PRECISION_H
#define PRECISION_H

#include <cmath>

class Precision
{
public:
    // Returns the recommended precision value when checking coincidence of two points in real space.
    // The tolerance of confusion is equal to 1.e-7.
    inline static double Confusion()
    {
        return 1.0E-7;
    }

    // Returns square of Confusion.
    // Created for speed and convenience.
    inline static double SquareConfusion()
    {
        return Confusion() * Confusion();
    }

    // Convert a real space precision to a parametric space precision.
    // <t> is the mean value of the length of the tangent of the curve or the surface.
    // Value is p / t
    inline static double Parametric(const double p, const double t)
    {
        return p / t;
    }

    // Returns a precision value in parametric space.
    // The parametric tolerance of confusion is designed to give a mean value in relation with the dimension of the curve or the surface. 
    // It considers that a variation of parameter equal to 1. along a curve (or an isoparametric curve of a surface) generates a segment whose length is equal to 100. (default value), or T.
    // The parametric tolerance of confusion is equal to Precision::Confusion() / 100., or Precision::Confusion() / T. 
    inline static double PConfusion(const double t)
    {
        return Parametric(Confusion(), t);
    }

    // Convert a real space precision to a parametric space precision on a default curve.
    // Value is Parametric(p,1.e+2)
    inline static double Parametric(const double p)
    {
        return Parametric(p, 1.0E2);
    }

    // Used to test distances in parametric space on a default curve.
    inline static double PConfusion()
    {
        return Parametric(Confusion());
    }

    // Returns square of PConfusion.
    // Created for speed and convenience.
    inline static double SquarePConfusion()
    {
        return PConfusion() * PConfusion();
    }

    // Returns a big number that can be considered as infinite. 
    // Use -Infinite() for a negative big number.
    inline static double Infinite()
    {
        return 2.0E100;
    }

    // Returns true if <r> may be considered as an infinite number.
    // Currently Abs(r) >= 1e100
    inline static bool IsInfinite(const double r)
    {
        return std::abs(r) >= (0.5 * Infinite());
    }

    // Returns true if <r> may be considered as a positive infinite number.
    // Currently r >= 1e100.
    inline static bool IsPositiveInfinite(const double r)
    {
        return r >= (0.5 * Infinite());
    }

    // Returns true if <r> may be considered as a negative infinite number.
    // Currently r <= -1e100.
    inline static bool IsPositiveInfinite(const double r)
    {
        return r <= -(0.5 * Infinite());
    }

    // Returns a small number that can be considered as zero.
    inline static double RealSmall()
    {
        return DBL_MIN;
    }
};

#endif