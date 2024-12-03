# Bit Representation

## Goals

Find ways to represent bases, amino acids, strands, and their characteristics to simplify syntax and computation.

1. Allow bitwise determination of an **instruction/amino acid**
2. Allow bitwise determination of a **complement**
3. Allow bitwise determination of **direction**

## Solution

Each base is assigned a 2 bit representation. (Note: Little Endian) By bit shifting the second base left 2 and then ORing them together we get a number from 0 to 15 (8 bits). We can use that as an offset into a 16 element array (potentially a function pointer array?) to get what instruction should be completed. This solves goal 1.

To solve goal 2, the inverse of each 2 bit base will be the bit representation of its complement.

## Tables

### Bases

| Base  | Bits |
| ---   | ---  |
| **A** | 00   |
| **T** | 11   |
| **C** | 01   |
| **G** | 10   |

### Amino Acids

| First Base | Second Base | First Base Bits | Second Base Bits | Combined | Amino Acid | Direction |
| ---------- | ----------- | --------------- | ---------------- | -------- | ---------- | --------- |
|**A**       |**A**        | 00              | 00               | 0000     | pun        | \-        |
|**A**       |**C**        | 00              | 01               | 0100     | cut        | s         |
|**A**       |**G**        | 00              | 10               | 1000     | del        | s         |
|**A**       |**T**        | 00              | 11               | 1100     | swi        | r         |
|**C**       |**A**        | 01              | 00               | 0001     | mvr        | s         |
|**C**       |**C**        | 01              | 01               | 0101     | mvl        | s         |
|**C**       |**G**        | 01              | 10               | 1001     | cop        | r         |
|**C**       |**T**        | 01              | 11               | 1101     | off        | l         |
|**G**       |**A**        | 10              | 00               | 0010     | ina        | s         |
|**G**       |**C**        | 10              | 01               | 0110     | inc        | r         |
|**G**       |**G**        | 10              | 10               | 1010     | ing        | r         |
|**G**       |**T**        | 10              | 11               | 1110     | int        | l         |
|**T**       |**A**        | 11              | 00               | 0011     | rpy        | r         |
|**T**       |**C**        | 11              | 01               | 0111     | rpu        | l         |
|**T**       |**G**        | 11              | 10               | 1011     | lpy        | l         |
|**T**       |**T**        | 11              | 11               | 1111     | lpu        | l         |

It is *almost* the case that each direction corresponds to a different number of bits, but this breaks down for CC.