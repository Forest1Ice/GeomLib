// Describes a rational or non-rational Bezier curve
// - a non-rational Bezier curve is defined by a table of poles (also called control points),
// - a rational Bezier curve is defined by a table of poles with varying weights.
// The weights are defined and used only in the case of a rational curve.

#ifndef GEOM_BEZIERCURVE_H
#define GEOM_BEZIERCURVE_H

#include "geom_BoundedCurve.h"

class Geom_BezierCurve: public Geom_BoundedCurve
{
public:
    // Creates a non rational Bezier curve with a set of poles.
    // The weights are defaulted to all being 1.
    // Raised if the number of poles is greater than MaxDegree + 1
    // or lower than 2.
    Geom_BezierCurve(const gp_Array1OfPnt& poles);

    // Creates a rational Bezier curve with the set of poles and the set of weights.
    // If all the weights are identical the curve is considered as non rational.
    // Raised if the number of poles is greater than MaxDegree + 1
    // or lower than 2 or curvePoles and curveWeights don't have the same length.
    Geom_BezierCurve(const gp_Array1OfPnt& poles, const std_Array1OfReal& weights);

    // Increases the degree of a bezier curve.
    // Raised if new degree is greater than MaxDegree or lower than 2 or lower than the initial degree.
    void Increase(const double degree);

    // Segments the curve between u1 and u2 which must be in the bounds of the curve.
    // The curve is oriented from u1 to u2.
    // Warnings:
    // Even if the curve is not closed it can become closed after the segmentation
    // for example if the curve makes loop.
    void Segment(const double u1, const double u2);

    // Substitutes the pole of range index with p.
    // Raised if the index is not in the range [0, m_NbPoles - 1].
    void SetPole(const int index, const gp_Pnt& p);

    // Substitutes the pole and the weight of range index.
    // Raised if the index is not in the range [0, m_NbPoles - 1].
    // Raised if weight <= Resolution from package goemetry.
    void SetPole(const int index, const gp_Pnt& p, const double weight);

    // Changes the weight of the pole of range Index.
    // Raised if the index is not in the range [0, m_NbPoles - 1].
    // Raised if weight <= Resolution from package goemetry.
    void SetWeight(const int index, const double weight);

    void D0 (const double u, gp_Pnt& p) const override;

    void D1 (const double u, gp_Pnt& p, gp_Vec& v1) const override;

    void D2 (const double u, gp_Pnt& p, gp_Vec& v1, gp_Vec& v2) const override;

    gp_Vec DN(const double u, const int n) const override;

    // Returns true if the distance between the first point
    // and the last point of the curve is not more than the
    // Resolution from package goemetry.
    inline bool IsClosed() const override
    {
        return m_closed;
    }

    // Continuity of the curve, returns true as the continuity of a Bezier curve is infinite.
    inline bool IsCN (const int n) const override
    {
        return true;
    }
    
    // Returns false if all the weights are identical. The tolerance criterion is Resolution from geometry package.
    inline bool IsRational() const
    {
        return (m_weights.size() != 0);
    }

    // a Bezier curve is CN
    Geom_Continuity Continuity() const override
    {
        return Geom_Continuity::Geom_CN;
    }

    // Returns the polynomial degree of the curve.
    inline int Degree() const
    {
        return NbPoles() - 1;
    }

    // Returns Value (u=0), it is the first control point of the curve.
    inline gp_Pnt StartPoint() const override
    {
        return m_poles[0];
    }

    // Returns Value (u=1), it is the last control point of the curve.
    inline gp_Pnt EndPoint() const override
    {
        return m_poles[Degree()];
    }
    
    // This is 0.0, which gives the start point of this Bezier curve.
    inline double FirstParameter() const override
    {
        return 0.0;
    }

    // This is 1.0, which gives the last point of this Bezier curve.
    inline double LastParameter() const override
    {
        return 1.0;
    }

    // Returns the number of poles of this Bezier curve.
    inline int NbPoles() const
    {
        return m_poles.size();
    }

    // Returns the pole of range index.
    // Raised if the index is not in the range [0, m_NbPoles - 1].
    const gp_Pnt& Pole(const int index) const;

    // Returns all the poles of the curve.
    inline void Poles(gp_Array1OfPnt& p) const
    {
        p = m_poles;
    }

    // Returns all the poles of the curve.
    inline const gp_Array1OfPnt& Poles() const
    {
        return m_poles;
    }

    // Returns the weight of range index.
    double Weight(const int index) const;

    // Returns all the weights of the curve.
    void Weights(std_Array1OfReal& weights) const;

    // Returns all the weights of the curve.
    std_Array1OfReal Weights() const;

    // Returns the value of the maximum polynomial degree of
    // any Geom_BezierCurve curve. This value is 25.
    inline static int MaxDegree()
    {
        return 25;
    }

    // Computes for this Bezier curve the parametric tolerance uTolerance for a given 3D tolerance tolerance3D.
    // If f(t) is the equation of this Bezier curve,
    // uTolerance ensures that:
    // |t1-t0| < uTolerance ===> |f(t1)-f(t0)| < tolerance3D
    void Resolution(const double tolerance3D, double& uTolerance);

    // Creates a new object which is a copy of this Bezier curve.
    handle<Geom_Curve> Copy() const override;

private:
    // Set poles and weights. If weights is null the curve is non-rational
    // and weights are assumed to have the first coefficient 1.
    // Update rational and closed.
    void Init(const gp_Array1OfPnt& poles, const std_Array1OfReal& weights);

private:
    bool m_closed;
    gp_Array1OfPnt m_poles;
    std_Array1OfReal m_weights;
};

#endif