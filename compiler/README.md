# Build the compiler

UPPAAL DBM Library is needed : https://github.com/UPPAALModelChecker/UDBM  

Put all include files in `compiler/Engines/model-checker-engine/UDBM/include` and the library in `compiler/Engines/model-checker-engine/UDBM/lib`  

```
cd distribution
./single-archive-dist.sh
```

