//==========================================================================
//* class Simulation
//* Authors: Grant Szajda, Alex Cheatham
//* Written: 10/06/2022
//==========================================================================

Assembler that converts MIPS instructions into binary.

The first pass is completed, it takes the MIPS instructions,
strips off the comments and lines we can ignore, as well 
as stores the labels in a map with their respective line numbers and 
removes the original labels from the code. 