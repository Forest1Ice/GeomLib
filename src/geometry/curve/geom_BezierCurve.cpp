#include "geom_BezierCurve.h"
#include "exceptions.h"

// check rationality of an array of weights
static bool Rational(const std_Array1OfReal& weights)
{
    bool rational = false;

    for(int i = 0; i < weights.size() - 1; ++i)
    {
        rational = std::abs(weights[i] - weights[i+1]) > gp_Resolution;
        if (rational)
        {
            break;
        }
    }
    return rational;
}

Geom_BezierCurve::Geom_BezierCurve(const gp_Array1OfPnt& poles)
{
    // Check poles
    int nbPoles = poles.size();
    VALIDATE_ARGUMENT(nbPoles >= 2 && nbPoles <= (MaxDegree() + 1), "poles", "Poles size must be greater than 1 and at most MaxDegree() + 1!");

    // Init non-rational
    Init(poles, std_Array1OfReal());
}

Geom_BezierCurve::Geom_BezierCurve(const gp_Array1OfPnt& poles, const std_Array1OfReal& weights)
{
    // Check poles
    int nbPoles = poles.size();
    VALIDATE_ARGUMENT(nbPoles < 2 || nbPoles <= (MaxDegree() + 1), "poles", "Geom_BezierCurve: Poles size is less than 2 or more than MaxDegree() + 1!");

    // Check weights
    int nbWeights = weights.size();
    VALIDATE_ARGUMENT(nbWeights != nbPoles, "weights", "Geom_BezierCurve: Weights size does not match poles!");

    for (int i = 0; i < nbWeights; ++i)
    {
        VALIDATE_ARGUMENT(weights[i] <= gp_Resolution, "weights", "Geom_BezierCurve: Some weights are near zero!");
    }

    // Check really rational
    bool rational = Rational(weights);

    // Copy weights
    std_Array1OfReal nweights;
    if(rational)
    {
        nweights = weights;
    }

    // Init
    Init(poles, nweights);
}

void Geom_BezierCurve::Init(const gp_Array1OfPnt& poles, const std_Array1OfReal& weights)
{
    // Check closed
    m_closed = glm::distance(poles[0], poles[poles.size() - 1]) <= Precision::Confusion();

    // Check rational
    bool rational = (weights.size() != 0);

    // Copy poles
    m_poles = poles;

    if (rational)
    {
        m_weights = weights;
    }
}



void Geom_BezierCurve::Increase(const double degree)
{
    // Check new degree
    if(degree == Degree())
    {
        return;
    }

    VALIDATE_ARGUMENT(degree < Degree() || degree > MaxDegree(), "degree", "Geom_BezierCurve: New degree is invalid!");

}

void Geom_BezierCurve::Increase(const double degree)
{

}

void Geom_BezierCurve::Segment(const double u1, const double u2)
{

}

void Geom_BezierCurve::SetPole(const int index, const gp_Pnt& p)
{
    // Check index
    VALIDATE_ARGUMENT_RANGE(index, 0, Degree());

    m_poles[index] = p;

    // Update closed
    if (index == 0 || index == Degree())
    {
        m_closed = glm::distance(StartPoint(), EndPoint()) <= Precision::Confusion();
    }
}

void Geom_BezierCurve::SetPole(const int index, const gp_Pnt& p, const double weight)
{
    SetPole(index, p);
    SetWeight(index, weight);
}

void Geom_BezierCurve::SetWeight(const int index, const double weight)
{
    // Check index
    VALIDATE_ARGUMENT_RANGE(index, 0, Degree());

    // Check weight
    VALIDATE_ARGUMENT(weight <= gp_Resolution, "weight", "Geom_BezierCurve: Weight is near zero!");

    // Compute new rationality
    bool rational = IsRational();
    if(!rational)
    {
        // A weight of 1 does not turn to rational
        if(std::abs(weight - 1.0) <= gp_Resolution)
        {
            return;
        }
        // Set weights of 1.
        m_weights = std_Array1OfReal(NbPoles(), 1.0);
    }

    m_weights[index] = weight;

    // Is it turning into non-rational?
    if(rational && !Rational(m_weights))
    {
        m_weights.clear();
    }
}

void Geom_BezierCurve::D0 (const double u, gp_Pnt& p) const
{
    
}

void Geom_BezierCurve::D1 (const double u, gp_Pnt& p, gp_Vec& v1) const
{

}

void Geom_BezierCurve::D2 (const double u, gp_Pnt& p, gp_Vec& v1, gp_Vec& v2) const
{

}

gp_Vec Geom_BezierCurve::DN(const double u, const int n) const
{

}

const gp_Pnt& Geom_BezierCurve::Pole(const int index) const
{
    // Check index
    VALIDATE_ARGUMENT_RANGE(index, 0, Degree());

    return m_poles[index];
}

double Geom_BezierCurve::Weight(const int index) const
{
    // Check index
    VALIDATE_ARGUMENT_RANGE(index, 0, Degree());

    if(IsRational())
    {
        return m_weights[index];
    }
    else
    {
        return 1.0;
    }
}

void Geom_BezierCurve::Weights(std_Array1OfReal& weights) const
{
    if(IsRational())
    {
        weights = m_weights;
    }
    else
    {
        for(int i = 0; i < Degree(); ++i)
        {
            weights[i] = 1.0;
        }
    }
}

std_Array1OfReal Geom_BezierCurve::Weights() const
{
    if(IsRational())
    {
        return m_weights;
    }
    else
    {
        std_Array1OfReal weights(NbPoles());
        for(int i = 0; i < Degree(); ++i)
        {
            weights[i] = 1.0;
        }
        return weights;
    }
}