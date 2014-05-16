Steiner-algorithm
=================

Implementations 2 approximation algorithm for the generalized steiner netwerk problem. In this document, the contents, instalation guide and user guide for the code is given.

## Contents

Source for executable files
* src/final_complete_main.cxx
* src/final_incomplete_main.cxx
* src/final_petersen_main.cxx

Header files
* include/AssignConnectivityRequirement.h
* include/AssignEdgeCost.h
* include/CheckSolVal.h
* include/CreateSolveLP.h
* include/GenerateGraph.h
* include/IterativeRounding.h
* include/RequirementFunction.h
* include/SourceTargetArc.h

Source code files
* src/AssignConnectivityRequirement.cpp
* src/AssignEdgeCost.cpp
* src/CheckSolVal.cpp
* src/CreateSolveLP.cpp
* src/GenerateGraph.cpp
* src/IterativeRounding.cpp
* src/SourceTargetArc.cpp


## Requirements

The Make file assumes gcc, which is installed on most linux and mac machines. 

## Instalation
I spell out all the commands needed in order to execute a version of the program. 
I will assume that the reader can open a terminal, navigate through directries using the command line and untar/zip files.
The installation and execution has been tested for mac and linux. 
The instalation guide has not been tested using microsoft. 

Note: on a mac, .tar.gz files are automatically unzipped so in the commands below .gz can be ommited, as indicated with the parenthesized (.gz).

### Install glpk

Move the glpk-4.35.tar(.gz) to a directory of your choice, go to this directory. Then execute

* tar xvf(z) glpk-4.35.tar(.gz)
* cd glpk-4.35
* ./configure
* make
* sudo make install 

### Install lemon

Move the lemon-1.2.4.tar(.gz) to a directory of your choice, go to this directory. Then execute

* tar xvf(z) lemon-1.2.4.tar(.gz)
* cd lemon-1.2.4
* ./configure
* make
* sudo make install 

### Install 

* git clone git@github.com:jhdvries/steiner-algorithm
* cd steiner-algorithm
* make

##Execution

After compiling the code, the executables are in the bin directory, run them by typing:

* ./bin/final_complete_main    
Solves the generalized steiner network on a complete graph with 10 nodes, cost 1 for all edges and connectivity requirement 1 for all nodepairs. 

* ./bin/final_incomplete_main    
Solves the generalized steiner network on a incomplete graph with 10 nodes, cost 1 for all edges and connectivity requirement 1 for all nodepairs.

* ./bin/final_petersen_main    
Solves the generalized steiner network on the petersen graph with 10 nodes, cost 1 for all edges and connectivity requirement 1 for all nodepairs.

Note that the instance on the incomplete graph, which is randomly generated for final_incomplete_main.cxx, might not have a feasible solution. If so, simply execute the programm again. 

The output is the solution to the LP relaxation and it's value and the approximated solution and it's value.

## Adjustment options

There are several options for adjusting the instances that are solved by the algorithm. 

### Adjusting the size of the graph, not possible for petersen graph.

Open final_complete_main.cxx, on line 16, there is function generate_complete_graph(&g,10) adjust the size of the graph by changing 10 to the desired number of nodes. final_incomplete_main.cxx can be adjusted in the same way. Note that instances with more then 15 nodes might not be executable.

### Adjusting the cost function

Open final_complete_main.cxx, on line 20, there is function fill_cost_constant(&c, &g, 1); There are two ways to adjust the cost assignment to the node edges. 

1. replace the 1 with a desired edge costs m for all edges

2. replace constant with random, and change 1 to a desired edge cost upperbound m. The costs will now be randomly assigned integers ranging from 1 to m.  

### Adjusting the requirement function 
Open final_complete_main.cxx, on line 24, there is function assign_connectivity_constant(&r,&g,1). There are two ways to adjust the requirement on the node pairs. 

1. replace the 1 with a desired connectivity requirement m for all nodepairs

2. replace constant with random, and change 1 to a desired connectivity requirement upperbound m. The requirements will now be randomly assigned integers ranging from 1 to m.  

The same can be done for either final_incomplete_main.cxx and final_petersen_main.cxx. Note that having m>3 is always infeasible for the petersen graph as all nodes have 3 outgoing edges.

After any adjustments, compile the code again and execute the adjusted file.
