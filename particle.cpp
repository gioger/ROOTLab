#include "particle.hpp"

#include <iostream>

ParticleType::ParticleType(std::string name, double mass, int charge)
    : m_name{std::move(name)}, m_mass{mass}, m_charge{charge}
{
    if (m_mass < 0.0)
    {
        std::cerr << "ParticleType::ParticleType: "
                  << "invalid mass value: " << m_mass << '\n';
        std::exit(EXIT_FAILURE);
    }
}