#include <iostream>
#include "../include/particle.hpp"
#include "../include/resonance.hpp"

int main() {
    ParticleType const particle{"particella", 2., 3};
    ResonanceType const resonance{"risonanza", 2., 3, 4.};
    particle.Print();
    resonance.Print();
    }