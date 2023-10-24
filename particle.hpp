#ifndef PARTICLE_HPP
#define PARTICLE_HPP

#include <string>

class ParticleType
{
private:
    std::string Name{}; // we'll ask if it's ok to use std::string
    double fMass{};
    int fCharge{};

public:
    ParticleType() = default;
    ParticleType(std::string name, double mass, int charge);

    double GetMass() const { return fMass; }
    int GetCharge() const { return fCharge; }
    std::string GetName() const { return Name; }
    void Print() const;
};

#endif // PARTICLE_HPP