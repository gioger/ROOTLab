mkdir -p build
g++ *.cpp $(root-config --glibs --cflags --libs) -Wall -Wextra -o build/ROOTLabch