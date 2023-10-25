#include "particle_type.hpp"
#include "resonance_type.hpp"
#include <iostream>

int main()
{
	const ParticleType particle{"particella", 2., 3};
	const ResonanceType resonance{"risonanza", 2., 3, 4.};
	particle.Print();
	resonance.Print();
	const ParticleType* pointPart{&particle};
    const ResonanceType* pointRes{&resonance};
    std::array<const ParticleType*, 2> a = {pointPart, pointRes};
    for(int i{}; i<2; ++i) {
        (*a[i]).Print();
    }
}