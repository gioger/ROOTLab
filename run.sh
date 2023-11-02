set -e

mkdir -p build
cd src

files="particle_type.cpp resonance_type.cpp particle.cpp main.cpp"

g++ $files $(root-config --glibs --cflags --libs) -Wall -Wextra -o ../build/ROOTLab -O3

cd ..

echo "Running..."

./build/ROOTLab