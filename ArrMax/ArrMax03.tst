// very large number of elements in array

load ArrMax.vm,
output-file ArrMax03.out,
compare-to ArrMax03.cmp,
output-list sp%D1.6.1 local%D1.6.1 argument%D1.8.1 this%D1.6.1 that%D1.6.1
            RAM[16]%D1.6.1 RAM[17]%D1.6.1 RAM[18]%D1.6.1
            local[0]%D1.8.1 local[1]%D1.8.1 local[2]%D1.8.1
            argument[0]%D1.11.1 argument[1]%D1.11.1 argument[2]%D1.11.1;

set sp 256,        // stack pointer
set local 300,     // base address of the local segment
set argument 400,  // base address of the argument segment
set this 3000,     // base address of the this segment
set that 3010,     // base address of the that segment

set RAM[16] 0,     // static 0
set RAM[17] 2048,  // static 1
set RAM[18] 14,     // static 2

set local[0] 10,   // local 0
set local[1] 20,   // local 1
set local[2] 30,   // local 2

set argument[0] 100,  // argument 0
set argument[1] 200,  // argument 1
set argument[2] 300,  // argument 2

set RAM[2048] -32768,  // Set Arr[0]
set RAM[2049] 32767,  // Set Arr[1]
set RAM[2050] 0,  // Set Arr[2]
set RAM[2051] 32767;  // Set Arr[3]
set RAM[2052] -32768,  // Set Arr[4]
set RAM[2053] 0,  // Set Arr[5]
set RAM[2054] -32768,  // Set Arr[6]
set RAM[2055] 32767;  // Set Arr[7]
set RAM[2056] 69,  // Set Arr[8]
set RAM[2057] 32767,  // Set Arr[9]
set RAM[2058] -32768,  // Set Arr[10]
set RAM[2059] 420;  // Set Arr[11]
set RAM[2060] -32768,  // Set Arr[12]
set RAM[2061] 32767,  // Set Arr[13]
set RAM[2062] -32768,  // Set Arr[14]
set RAM[2063] 0;  // Set Arr[15]

repeat 400 {        // Change this number to cover the number of instructions in the VM test file
  vmstep;
}
output;