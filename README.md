# CUED 2nd Year Project: I-Don't-Panic

- Project Records: [link](https://docs.google.com/document/d/110WkkEqvjU1-dqSzpJSb_2VvEhg3sdYWeH0RdvRL9-M/edit)
- Software Records: [link](https://docs.google.com/document/d/1t8hccKTBRdeo6VtAheowXwqqX7eZCas97UfbfMCfLaE/edit)

## Tasks
Landmine clearance.

## Specs
- The robot must be of modular construction and use standard components where possible to allow easy maintenance and repair in the field [MECH] [ELEC] [SFTW]
- When a mine is found the flashing amber light is to be switched to continuous until the type of mine (live or dummy) has been determined. The robot must not touch the mine until the type is determined. [ELEC]  [SFTW]
- A green light displayed for 5 seconds (along with the amber) shall signify that the mine is a dummy. A red light displayed for 5 seconds (along with the amber) shall signify that the mine is live. [ELEC]  [SFTW]
- The robot must display a flashing red light when transporting a live mine [ELEC]  [SFTW]
- Only a single live mine can be carried at a time [SFTW]
- A software print out and flow chart is required [SFTW]

## Structure
The software contains the following parts.
- C++ (Individual modules)
- Python (Testing modules)

## To contributor
To better develop this repo, please use the following format of commitment:
`Change Type - describe`:
Change Type can be:
- Syntax error fixed
- Variable tuning
- Add function
- Delete function
- Structure change
- General (Readme, folder ...)

Constant variable: CAPITAL LETTERS in the `.h` file.
C++: comment after every {}, ep: `if (...){ ... }//if`.

Please commit every step of progress.




