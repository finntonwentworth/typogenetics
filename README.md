# Typogenetics

From Godel, Escher, Bach: An Eternal Golden Braid. Attempted in C

Typogenetics is a simplified model of genetics that demonstrates information storage and expansion. It involves typographical manipulation of sequences of the letters A, C, G, and T.  [Finn Please make this description better lol]

## Definitions

- **Base:** One of the letters A, C, G, and T
    - Pyrimidines: C and T
    - Purines: A and G
- **Complementary Base:** The pyrimidine that maps to its purine and vise versa
    - A <=> T
    - G <=> C
- **Duplet:** An adjacent pairs of bases in a single strand. There are 16 possible duplets.
- **Unit:** A single position occupied by a base.
- **Strand:** A sequence of bases
    - Ex: AAAA, ATTACCA, CATCATCAT
- **Amino Acid:** An Operation/Command out of 15 that operates on a strand. Defined/Derived from a duplet in a strand.
- **Enzyme:** A sequence of amino acids that operate on a strand, one unit/base at a time.
They are said to be "bound" to the unit they are currently operating on.
    - EX: rpu-inc-cop-mvr-mvl-swi-lpu-int
- **Binding Preference:** The base that a particular enzyme always choses to start at. An intrinsic property of the enzymes structure.

### Amino Acids / Instructions

Amino acids are derived from duplets in a sequence. If a sequence has a spare base at the end with no pair, it does nothing.

This table shows their mapping. The left side is the first base, the top is the second base. The table also says if the amino acid causes the enzyme's tertiary structure to "fold", denotes by the subscript l, r, or s.

[Note from jacob. In regards to the l, r, s. The table has some symmetry. Maybe theres some sort of clever math thing we can do to figure out which direction it should go.]

|     |  A              |  C              |  G              |  T              |
|---  | ---             | ---             | ---             | ---             |
|**A**| pun             | cut<sub>s</sub> | del<sub>s</sub> | swi<sub>r</sub> |
|**C**| mvr<sub>s</sub> | mvl<sub>s</sub> | cop<sub>r</sub> | off<sub>l</sub> |
|**G**| ina<sub>s</sub> | inc<sub>r</sub> | ing<sub>r</sub> | int<sub>l</sub> |
|**T**| rpy<sub>r</sub> | rpu<sub>l</sub> | lpy<sub>l</sub> | lpu<sub>l</sub> | 


| Abbreviation | Description | Implementation State |
| ---          | ---         | ---                  |
| [cut](#cut)  | Cut Strand(s) | DONE! |
| [del](#del)  | Delete a base from strand | |
| [swi](#swi)  | Switch enzyme to other strand | |
| [mvr](#mvr)  | Move one unit to the right | |
| [mvl](#mvl)  | Move one unit to the left | |
| [cop](#cop)  | Turn on copy mode | |
| [off](#off)  | Turn off copy mode | |
| [ina](#ina)  | Insert A to the right of this unit | |
| [inc](#inc)  | Insert C to the right of this unit | |
| [ing](#ing)  | Insert G to the right of this unit | |
| [int](#int)  | Insert T to the right of this unit | |
| [rpy](#rpy)  | Search of the nearest pyrimidine to the right | |
| [rpu](#rpu)  | Search for the nearest purine to the right | |
| [lpy](#lpy)  | Search for the nearest pyrimidine to the left | |
| [lpu](#lpu)  | Search for the nearest purine to the left   | |

#### Cut

Cuts the strand at the unit the enzyme is currently bound to.
The cut is placed to the right of the bound unit.
Cut applies to both the "active" strand and the "complementary" strand that
is being generated from the copy mode.

### Binding Preference

Binding preference is determined by the relative orientation of the first and last segments of an enzymes's tertiary structure.

| First Segment | Last Segment | Binding-Letter/Base |
| ---           | ---          | ---                 |
| &rarr; | &rarr; | A |
| &rarr; | &uarr; | C |
| &rarr; | &darr; | G |
| &rarr; | &larr; | T |

<figure class="image">

<div style="text-align: center">

<img src="notes/TypoProgramFlow.drawio.png">

</div>

</figure>

<p align="center">Preliminary Program Flowchart</p>
