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

    string ASM = "";
    string seg = "";

    if (segment == "local"){
        ASM += "@LCL\nA=M\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
        return ASM;
    } else if (segment == "argument"){
        ASM += "@ARG\nA=M\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
        return ASM;
    } else if (segment == "this"){
        ASM += "@THIS\nA=M\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
        return ASM;
    } else if (segment == "that"){
        ASM += "@THAT\nA=M\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
        return ASM;
    } else if (segment == "temp"){
        ASM += "@" + to_string(offset) + "\nD=A\n@5\nA=A+D\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
        return ASM;
    } else if (segment == "static"){
        ASM += "@" + to_string(offset) + "\nD=A\n@16\nA=A+D\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
        return ASM;
    } else if (segment == "pointer") {
        ASM += "@" + to_string(offset) + "\nD=A\n@3\nA=A+D\nD=M\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
        return ASM;
    } else if (segment == "constant") {
        ASM += "@" + to_string(offset) + "\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n";
        return ASM;
    }
}

/** Generate Hack Assembly code for a VM pop operation */
string VMTranslator::vm_pop(string segment, int offset){ 

    string ASM = "@SP\nAM=M-1\nD=M\n";

    if (segment == "local"){
        ASM += "@LCL\n";
        for (int i=0; i<offset; i++) {
            ASM += "A=A+1\n";
        }
        ASM += "M=D\n";
        return ASM;
    } else if (segment == "argument"){
        ASM += "@ARG\n";
        for (int i=0; i<offset; i++) {
            ASM += "A=A+1\n";
        }
        ASM += "M=D\n";
        return ASM;
    } else if (segment == "this"){
        ASM += "@THIS\n";
        for (int i=0; i<offset; i++) {
            ASM += "A=A+1\n";
        }
        ASM += "M=D\n";
        return ASM;
    } else if (segment == "that") {
        ASM += "@THAT\n";
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
}

/** Generate Hack Assembly code for a VM add operation */
string VMTranslator::vm_add(){
    return "";
}

/** Generate Hack Assembly code for a VM sub operation */
string VMTranslator::vm_sub(){
    return "";
}

/** Generate Hack Assembly code for a VM neg operation */
string VMTranslator::vm_neg(){
    return "";
}

/** Generate Hack Assembly code for a VM eq operation */
string VMTranslator::vm_eq(){
    return "";
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
    return "";
}

/** Generate Hack Assembly code for a VM or operation */
string VMTranslator::vm_or(){
    return "";
}

/** Generate Hack Assembly code for a VM not operation */
string VMTranslator::vm_not(){
    return "";
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