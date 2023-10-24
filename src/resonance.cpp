#include "resonance.hpp"

#include <iostream>

ResonanceType::ResonanceType(std::string name, double mass, int charge, double width)
    : ParticleType{std::move(name), mass, charge}, m_width{width}
{
    if (m_width < 0.)
    {
        std::cerr << "ResonanceType::ResonanceType: "
                  << "invalid width value: " << m_width << '\n';
        std::exit(EXIT_FAILURE);
    }
}

void ResonanceType::Print() const
{
    ParticleType::Print();
    std::cout << "Width: " << m_width << " MeV/c^2\n"; // check units
}
