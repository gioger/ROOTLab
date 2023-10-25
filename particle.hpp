#include <array>
#include <iostream>
#include <memory>

class Particle {
    public:


    private:
    static constexpr int fMaxNumParticleType = 10;
    static std::array<std::unique_ptr<ParticleType>, fMaxNumParticleType> fParticleType{};
};