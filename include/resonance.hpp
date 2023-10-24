#ifndef RESONANCE_HPP
#define RESONANCE_HPP

#include "particle.hpp"

class ResonanceType : ParticleType
{
private:
    double m_width{};

public:
    ResonanceType(std::string name, double mass, int charge, double width);

    double GetWidth() const { return m_width; }
    void Print() const override;
};

#endif // RESONANCE_HPP