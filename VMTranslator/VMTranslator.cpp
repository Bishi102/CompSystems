#include <string>

#include "VMTranslator.h"

using namespace std;

/**
 * VMTranslator constructor
 */
VMTranslator::VMTranslator() {
    // Your code here
}

/**
 * VMTranslator destructor
 */
VMTranslator::~VMTranslator() {
    // Your code here
}

/** Generate Hack Assembly code for a VM push operation */
string VMTranslator::vm_push(string segment, int offset){

    if (segment == "local"){
        return "@" + to_string(offset) + "\nD=A\n" + "@LCL" + "\nA=M+D\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    } else if (segment == "argument"){
        return "@" + to_string(offset) + "\nD=A\n" + "@ARG" + "\nA=M+D\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    } else if (segment == "this"){
        return "@" + to_string(offset) + "\nD=A\n" + "@THIS" + "\nA=M+D\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    } else if (segment == "that"){
        return "@" + to_string(offset) + "\nD=A\n" + "@THAT" + "\nA=M+D\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    } else if (segment == "temp"){
        return "@" + to_string(offset) + "\nD=A\n@5\nA=A+D\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    } else if (segment == "static"){
        return "@" + to_string(offset) + "\nD=A\n@16\nA=A+D\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    } else if (segment == "pointer") {
        return "@" + to_string(offset) + "\nD=A\n@3\nA=A+D\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    } else if (segment == "constant") {
        return "@" + to_string(offset) + "\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    }
    return "";
}

/** Generate Hack Assembly code for a VM pop operation */
string VMTranslator::vm_pop(string segment, int offset){ 

    string ASM = "@SP\nAM=M-1\nD=M\n";

    if (segment == "local"){
        ASM += "@LCL\nA=M\n";
        for (int i=0; i<offset; i++) {
            ASM += "A=A+1\n";
        }
        ASM += "M=D\n";
        return ASM;
    } else if (segment == "argument"){
        ASM += "@ARG\nA=M\n";
        for (int i=0; i<offset; i++) {
            ASM += "A=A+1\n";
        }
        ASM += "M=D\n";
        return ASM;
    } else if (segment == "this"){
        ASM += "@THIS\nA=M\n";
        for (int i=0; i<offset; i++) {
            ASM += "A=A+1\n";
        }
        ASM += "M=D\n";
        return ASM;
    } else if (segment == "that") {
        ASM += "@THAT\nA=M\n";
        for (int i=0; i<offset; i++) {
            ASM += "A=A+1\n";
        }
        ASM += "M=D\n";
        return ASM;
    } else if (segment == "temp"){
        ASM += "@5\n";
        for (int i=0; i<offset; i++) {
            ASM += "A=A+1\n";
        }
        ASM += "M=D\n";
        return ASM;
    } else if (segment == "static"){
        ASM += "@16\n";
        for (int i=0; i<offset; i++) {
            ASM += "A=A+1\n";
        }
        ASM += "M=D\n";
        return ASM;
    } else if (segment == "pointer") {
        ASM += "@3\n";
        for (int i=0; i<offset; i++) {
            ASM += "A=A+1\n";
        }
        ASM += "M=D\n";
        return ASM;
    }
    return ASM;
}

/** Generate Hack Assembly code for a VM add operation */
string VMTranslator::vm_add(){
    return vm_pop("temp", 8) + vm_pop("temp", 9) + "@14\nD=M\n@13\nM=M+D\n" + vm_push("temp", 8);
}

/** Generate Hack Assembly code for a VM sub operation */
string VMTranslator::vm_sub(){
    return vm_pop("temp", 8) + vm_pop("temp", 9) + "@13\nD=M\n@14\nM=M-D\n" + vm_push("temp", 9);

}

/** Generate Hack Assembly code for a VM neg operation */
string VMTranslator::vm_neg(){
    return vm_pop("temp", 8) += "@13\nM=!M\nM=M+1\n" + vm_push("temp", 8);

}

/** Generate Hack Assembly code for a VM eq operation */
string VMTranslator::vm_eq() {
    string ASM = "";
    ASM += vm_pop("temp", 8) + vm_pop("temp", 9);
    ASM += "@R13\nD=M\n@VMPOS\nD;JGE\n";
    ASM += "@R14\nD=M\n@VMPOS2\nD;JGE\n";
    ASM += "(VMNEG)\n@R14\nD=M\n@R13\nD=D-M\n@VMeq\nD;JEQ\n@R13\nM=0\n@VMeqend1\n0;JMP\n(VMeq)\n@R13\nM=-1\n(VMeqend1)\n@VMeqend2\n0;JMP\n";
    ASM += "(VMPOS2)\n@R13\nM=0\n@VMeqend2\n0;JMP\n";
    ASM += "(VMPOS)\n@R14\nD=M\n@VMNEG\nD;JGE\n";
    ASM += "@R13\nM=0\n(VMeqend2)\n" + vm_push("temp", 8);
    return ASM;
}


/** Generate Hack Assembly code for a VM gt operation */
string VMTranslator::vm_gt(){
    return "";
}

/** Generate Hack Assembly code for a VM lt operation */
string VMTranslator::vm_lt(){
    return "";
}

/** Generate Hack Assembly code for a VM and operation */
string VMTranslator::vm_and(){
    return vm_pop("temp", 8) + vm_pop("temp", 9) + "@R14\nD=M\n@R13\nM=D&M" + vm_push("temp", 8);
}

/** Generate Hack Assembly code for a VM or operation */
string VMTranslator::vm_or(){
    return vm_pop("temp", 8) + vm_pop("temp", 9) + "@R14\nD=M\n@R13\nM=D|M" + vm_push("temp", 8);
}

/** Generate Hack Assembly code for a VM not operation */
string VMTranslator::vm_not(){
    return vm_pop("temp", 8) + "@R13\nM=!M\n" + vm_push("temp", 8);
    
}

/** Generate Hack Assembly code for a VM label operation */
string VMTranslator::vm_label(string label){
    return "";
}

/** Generate Hack Assembly code for a VM goto operation */
string VMTranslator::vm_goto(string label){
    return "";
}

/** Generate Hack Assembly code for a VM if-goto operation */
string VMTranslator::vm_if(string label){
    return "";
}

/** Generate Hack Assembly code for a VM function operation */
string VMTranslator::vm_function(string function_name, int n_vars){
    return "";
}

/** Generate Hack Assembly code for a VM call operation */
string VMTranslator::vm_call(string function_name, int n_args){
    return "";
}

/** Generate Hack Assembly code for a VM return operation */
string VMTranslator::vm_return(){
    return "";
}