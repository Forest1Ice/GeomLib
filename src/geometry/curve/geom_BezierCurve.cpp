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
    VALIDATE_ARGUMENT(nbPoles >= 2 && nbPoles <= (MaxDegree() + 1), "poles", "Poles size must be greater than 1 and at most MaxDegree() + 1!");

    // Check weights
    int nbWeights = weights.size();
    VALIDATE_ARGUMENT(nbWeights == nbPoles, "weights", "Weights must have the same size as poles!");

    for (int i = 0; i < nbWeights; ++i)
    {
        VALIDATE_ARGUMENT(weights[i] > gp_Resolution, "weights", "Weights must not be zero!");
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
    m_closed = glm::length(poles[0] - poles[poles.size() - 1]) <= Precision::Confusion();

    // Check rational
    m_rational = !(weights.size() == 0);

    // Copy poles
    m_poles = poles;

    if (m_rational)
    {
        m_weights = weights;
    }
}

