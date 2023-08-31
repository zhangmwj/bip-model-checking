# Build the compiler

UPPAAL DBM Library is needed : https://github.com/UPPAALModelChecker/UDBM  

Put all include files in `compiler/Engines/model-checker-engine/UDBM/include` and the library in `compiler/Engines/model-checker-engine/UDBM/lib`  

```
cd distribution
./single-archive-dist.sh
```

# Options added to the executable created by the compiler
`./system -z` compute the zone graph  
`./system --mc [--bfs]` compute the states visited by model checking using bfs  
`./system --mc --dfs` compute the states visited by model checking using dfs  

