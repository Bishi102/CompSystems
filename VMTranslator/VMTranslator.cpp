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
        seg = "LCL";
    } else if (segment == "argument"){
        seg = "ARG";
    } else if (segment == "this"){
        seg = "THIS";
    } else if (segment == "that"){
        seg = "THAT";
    } else if (segment == "temp"){
        seg = "LCL";
    } else if (segment == "static"){
        seg = "LCL";
    }

    ASM += "@" + to_string(offset) + "\nD=A\n";
    if (segment != "constant"){
        ASM += "@" + seg + "\nA=M+D\nD=M\n";
    }
    ASM += "@SP\nA=M\nM=D\n@SP\nM=M+1\n";
    return ASM;
}

/** Generate Hack Assembly code for a VM pop operation */
string VMTranslator::vm_pop(string segment, int offset){ 

    string ASM = "";
    string seg = "";

    if (segment == "local"){
        seg = "LCL";
    } else if (segment == "argument"){
        seg = "ARG";
    } else if (segment == "pointer"){
        if (offset == 0){
            seg = "THIS";
        } else {
            seg = "THAT";
            offset = 0;
        }
    } else if (segment == "temp"){
        seg = "LCL";
    } else if (segment == "static"){
        seg = "LCL";
    }   
    ASM += "@SP\nAM=M-1\nD=M\n@R13\nM=D\n@" + to_string(offset) + "\nD=A\n" +"@" + seg + "\nA=M+D\nD=A\n@R14\nM=D\n@R14\nM=D\n@R13\nD=M\n@R14\nA=M\nM=D\n";
    return ASM;
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