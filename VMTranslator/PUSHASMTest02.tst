// normal case

load PUSHTest02.asm,
output-file PUSHASMTest02B.cmp,
compare-to PUSHVMTest02.cmp,
output-list RAM[0]%D1.6.1 RAM[1]%D1.6.1 RAM[2]%D1.8.1 RAM[3]%D1.6.1 RAM[4]%D1.6.1
            RAM[256]%D1.8.1 RAM[257]%D1.8.1 RAM[258]%D1.8.1 RAM[259]%D1.8.1 RAM[260]%D1.8.1 RAM[261]%D1.8.1 RAM[262]%D1.8.1 RAM[263]%D1.8.1;

set PC 0,
set RAM[0] 256,
set RAM[1] 300,
set RAM[2] 400,
set RAM[3] 3000,
set RAM[4] 3010,

set RAM[254] -1,  // static 239
set RAM[14] 22,   // temp 7
set RAM[3000] 32767,   // this 0
set RAM[3010] -32768,   // that 0
set RAM[303] 32767,  // local 3
set RAM[400] -32768,  // argument 0

repeat 80 {        // Change this number to cover the number of instructions in the VM test file
  ticktock;
}
output;

