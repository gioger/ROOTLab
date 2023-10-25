#ifndef PARTICLE_TYPE_HPP
#define

#include <array>
#include <iostream>
#include <memory>

class Particle {
    public:
    Particle Particle(std::string name, double px, double py, double pz) : fName{name}, fPx{px}, fPy{py}, fpx{pz} {};
    Particle Particle(std::string name) : Particle(name, 0, 0, 0);

    private:
    static constexpr int fMaxNumParticleType = 10;
    static int fNParticleType{};
    int fIndex{};
    static std::array<std::unique_ptr<ParticleType>, fMaxNumParticleType> fParticleType{};
    int FindParticle(std::string nomeParticella);

    double fPx{};
    double fPy{};
    double fPz{};
};

#endif