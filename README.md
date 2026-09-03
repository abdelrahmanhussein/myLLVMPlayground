# LLVM Playground
I am learning LLVM for my research. My motivation is several published papers that I recently read which combine security and computer architecture.

This workspace is pretty simple. It contains the passes I develop as part of my learning experience and the tests cases I am using to test my passes.

## Infrastructure
I am using a VM for my learning journey.
- OS: Ubuntu 24.04.4 LTS
- CPU: 11th Gen Intel(R) Core(TM) i7-1185G7 @ 3.00GHz
- #Cores: 4
- Memory: 8 GB
- LLVM Version: 22.1.8

## Build Instructions
The test cases use simple `make` to build. This will do the following:
1. Build the pass.
2. Generate the unmodified IR representation of the code.
3. Run the pass on IR to generate the modified IR.
4. Compile the modified IR to generate the excutable.
5. Run a few test cases.

Simply, just run the following:
```bash
cd tests/<test_case>
make all PASS=<the Pass that you want to use - Default: instructionModifier>
```

## Learning Resources
1. [Cornell CS 6120 - Adrian Sampson](https://www.cs.cornell.edu/courses/cs6120/2020fa/lesson/)
2. [2019 LLVM Developers’ Meeting: J. Paquette & F. Hahn “Getting Started With LLVM: Basics”](https://youtu.be/3QQuhL-dSys?si=oJCIhsIg7urtSJxc)
3. [LLVM IR Quick Reference, 1st Edition, March 2025](https://simplifycpp.org/books/LLVM_IR_Quick_Reference.pdf)
4. and, of course, the [LLVM Official Documentation](https://llvm.org/docs/index.html)