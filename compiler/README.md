# BIP compiler

BIP documentation : https://www-verimag.imag.fr/New-BIP-tools.html  

## Build the compiler

The packages `default-jre`, `g++` and `cmake` need to be installed.  

UPPAAL DBM Library is needed : https://github.com/UPPAALModelChecker/UDBM  

Put all include folders in `Engines/model-checker-engine/UDBM/include` and the library in `Engines/model-checker-engine/UDBM/lib`  

```
cd distribution
./single-archive-dist.sh
source build/bip-full/setup.sh
```

## Options added to the executable created by the compiler
`./system -z` compute the zone graph  
`./system --mc [--bfs]` compute the states visited by model checking using bfs  
`./system --mc --dfs` compute the states visited by model checking using dfs  

