# Assignment #6, Universal Machine

Collaborators: Jane Trapala and Matthew Lallo
Hours worked: 15

## Overall Architecture

Our universal machine ran midmark with an average of 4.78s

### Universal Machine

This universal machine uses the following borrowed modules:

- Hanson's Seq_t
- Hanson's assert
- Bitpack library provided using -lbitpack

#### Memory

Memory is represented by two Seq_Ts, one is for mapped sequences and the other, unmapped. The program counter is mapped at the beginning, with a sequence id of zero.

The memory structure is freed at the end, regardless if a HALT instruction was called by the .um program. HALT only does an exit(0), and freeing the structure at that moment seg faulted our UM implementation.

#### Registers

The registers are made right before fetching the instructions from the provided file and after the memory structure is made. It is just an array of size 8, to hold the 8 registers of the UM, and is not malloc'd for the sake of speed.

## Interfaces

We use following interfaces in our UM:

- um_main.c
- mem-infra.c
- parse_instr.c
- instrs.c
- in_out.c

The first interface, **um_main**, was the shell, it took in file and analyzed it for instructions, using bitpack to extract the instruction's components. It also set up our UM's important components, the memory and registers. The next most important interface is **mem-infra**, this defines the different actions the UM does with memory, the memory itself, and the sequences that are used to make up the memory. **Parse_instr** takes care of analyzing each opcode in the given instruction and calls **instrs**  to carry out the procedures that are defined by the opcode.
Finally, **in_out** is used but instrs to get 8 byte char inputs and write the a given 32 bit char to stdout. That module makes sure that inputs/outputs are in thr range of 0-255.
