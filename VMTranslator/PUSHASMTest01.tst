// normal case

load PUSHTest01.asm,
output-file PUSHASMTest01.cmp,
compare-to PUSHVMTest01.cmp,
output-list RAM[0]%D1.6.1 RAM[1]%D1.6.1 RAM[2]%D1.8.1 RAM[3]%D1.6.1 RAM[4]%D1.6.1
            RAM[256]%D1.8.1 RAM[257]%D1.8.1 RAM[258]%D1.8.1 RAM[259]%D1.8.1 RAM[260]%D1.8.1 RAM[261]%D1.8.1 RAM[262]%D1.8.1 RAM[263]%D1.8.1;

set PC 0,
set RAM[0] 256,
set RAM[1] 300,
set RAM[2] 400,
set RAM[3] 3000,
set RAM[4] 3010,

set RAM[19] -1,  // static 3
set RAM[8] 22,   // temp 3
set RAM[3000] 22,   // this 0
set RAM[3010] 33,   // that 0
set RAM[300] 32767,  // local 3
set RAM[400] 100,  // argument 0

repeat 80 {        // Change this number to cover the number of instructions in the VM test file
  ticktock;
}
output;

