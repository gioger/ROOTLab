# ROOTLab
Here is a repository for UniBo lab2 c++/ROOT labs.

## Compiling and Running
To compile and run the simulation code, just run the following command:
```bash
./run.sh
```
This wil compile all cpp files and run the simulation, generating in `build` folder a `histos.root` file containing all histograms.
To fit and generate plots, run the ROOT macro `histos.C`. 
This will generate, inside `build` folder, the folders `pdf`, `C` and `root` containing the plots in the corresponding format.

The ROOT macro `histos.C` must be run from the repository root folder, not from `build` folder nor `src`.