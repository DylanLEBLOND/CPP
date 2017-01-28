;; = end of the program read from the standard input
exit = end of the program read from a file

make
then
./avm or ./avm FILENAME

S := INSTR [SEP INSTR]* #

INSTR :=
 push VALUE
 | pop
 | dump
 | assert VALUE
 | add
 | sub
 | mul
 | div
 | mod
 | print
 | exit

VALUE :=
 int8(N)
 | int16(N)
 | int32(N)
 | float(Z)
 | double(Z)

N := [-]?[0..9]+

Z := [-]?[0..9]+.[0..9]+

SEP := '\n'+
