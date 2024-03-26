## Data Types 
The data types that will be used are 
- Standard C++ Data types like **Double** , **Vector** , **Unsigned**, ... etc. 
- FastJet library core classes (**PseudoJet**, **JetDefinition**, **ClusterSequence**)

### Short-example.cc
I provide this as a sample of the data types that will be used according to the code i provided. There may be more data types arising during the semester. 
**This file will be updated consistently**

**vector<PseudoJet>:** This is a **vector container** from the C++ Standard Template Library (STL) that holds elements of the type PseudoJet.
**PseudoJet** is a **class type** provided by the FastJet library, commonly used for jet clustering in high-energy physics.
It presumably encapsulates information like momentum components (px, py, pz), energy (E), and other relevant properties.
It has methods to access properties such as transverse momentum (pt()), rapidity (rap()), and azimuthal angle (phi()).
**double:** This is a fundamental data type in C++ representing **double-precision floating-point numbers**. It is used to represent the radius R for the jet definition.
**JetDefinition:** This is a **class type** provided by the FastJet library, used to define the parameters of the jet clustering algorithm. In this code, an object of type JetDefinition is created using the antikt_algorithm clustering algorithm and the specified radius R.
**ClusterSequence:** This is a **class type** provided by the FastJet library for performing jet clustering on a set of input particles. An object of type ClusterSequence is created using the input particles and the jet definition.
**std::cout:** This is the **standard output stream object in C++** used for printing output to the console.
**std::endl:** This is an **I/O manipulator in C++** that represents a newline character. It is used to insert a newline and flush the output buffer.
**unsigned:** This is an **unsigned integer data type** in C++ used to represent non-negative integers. It is used for the loop counters in the for loops.


Reference:

1- [FastJet User Manual](https://fastjet.fr/repo/fastjet-doc-3.4.2.pdf)

2- [C++ Variables and types](https://cplusplus.com/doc/tutorial/variables/)
