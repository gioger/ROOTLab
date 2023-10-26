set -e

mkdir -p build
cd src

files="particle_type.cpp resonance_type.cpp particle.cpp test.cpp"

g++ $files $(root-config --glibs --cflags --libs) -Wall -Wextra -o ../build/ROOTLab

cd ..
./build/ROOTLab