# ROOTLab
Here is a repository for UniBo lab2 c++/ROOT labs.

We wrote a C++ code to simulate particle collision events and analyze collected data with ROOT. We were able to correctly determine K*'s mass and width by analyzing its decay products.

You'll find all source code, the ROOT macro (`histos.C`) and the lab report (`RelazioneROOT`, in Italian).


## Compiling and Running
To compile and run the simulation code, just run the following command:
```bash
./run.sh
```
This will compile all cpp files and run the simulation, generating in `build` folder a `histos.root` file containing all histograms.
To fit and generate plots, run the ROOT macro `histos.C`. 
This will generate, inside `build` folder, the folders `pdf`, `C` and `root` containing the plots in the corresponding format.

The ROOT macro `histos.C` must be run from the repository root folder, not from `build` folder nor `src`.
