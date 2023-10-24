#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <string>

class ParticleType
{
private:
    std::string m_name{}; // we'll ask if it's ok to use std::string
    double m_mass{};
    int m_charge{};

public:
    ParticleType() = default;
    ParticleType(std::string name, double mass, int charge);

    double GetMass() const { return m_mass; }
    int GetCharge() const { return m_charge; }
    std::string GetName() const { return m_name; }
    void Print() const;
};

#endif // PARTICLE_HPP