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
    return 
        vm_pop("temp", 8) + 
        vm_pop("temp", 9) + 
        "@14\nD=M\n@13\nM=M+D\n" + 
        vm_push("temp", 8);
}

/** Generate Hack Assembly code for a VM sub operation */
string VMTranslator::vm_sub(){
    return 
        vm_pop("temp", 8) + 
        vm_pop("temp", 9) + 
        "@13\nD=M\n@14\nM=M-D\n" + 
        vm_push("temp", 9);

}

/** Generate Hack Assembly code for a VM neg operation */
string VMTranslator::vm_neg(){
    return 
        vm_pop("temp", 8) += 
        "@13\nM=!M\nM=M+1\n" + 
        vm_push("temp", 8);

}

/** Generate Hack Assembly code for a VM eq operation */
string VMTranslator::vm_eq() {
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
    return 
        vm_pop("temp", 8) + 
        vm_pop("temp", 9) + 
        "@R14\nD=M\n@R13\nM=D&M\n" + 
        vm_push("temp", 8);
}

/** Generate Hack Assembly code for a VM or operation */
string VMTranslator::vm_or(){
    return 
        vm_pop("temp", 8) + 
        vm_pop("temp", 9) + 
        "@R14\nD=M\n@R13\nM=D|M\n" + 
        vm_push("temp", 8);
}

/** Generate Hack Assembly code for a VM not operation */
string VMTranslator::vm_not(){
    return 
        vm_pop("temp", 8) + 
        "@R13\nM=!M\n" + 
        vm_push("temp", 8);
}

/** Generate Hack Assembly code for a VM label operation */
string VMTranslator::vm_label(string label){
    return "(" + label + ")\n";
}

/** Generate Hack Assembly code for a VM goto operation */
string VMTranslator::vm_goto(string label){
    return "@" + label + "\n0;JMP\n";
}

/** Generate Hack Assembly code for a VM if-goto operation */
string VMTranslator::vm_if(string label){
    return 
        vm_pop("temp", 8) + 
        "@R13\nD=M\n@" + label + 
        "\nD;JNE\n";
}

/** Generate Hack Assembly code for a VM function operation */
string VMTranslator::vm_function(string function_name, int n_vars){
    string ASM = "";
    ASM += vm_label(function_name);
    for (int i=0; i<n_vars; i++) {
        ASM += "@SP\nA=M\nM=0\n@SP\nM=M+1\n";
    }
    return ASM;
}

/** Generate Hack Assembly code for a VM call operation */
string VMTranslator::vm_call(string function_name, int n_args){
    static int callCounter = 0;
    string returnLabel = function_name + "$ret." + to_string(callCounter);
    callCounter++;
    return 
        "@" + returnLabel + "\nD=A\n@SP\nA=M\nM=D\n@SP\nM=M+1\n" +

        vm_push("local", 0) + 
        vm_push("argument", 0) + 
        vm_push("this", 0) + 
        vm_push("that", 0) + 

        "@SP\nD=M\n@" + to_string(n_args) + "\nD=D-A\n@ARG\nM=D\n" +

        vm_goto(function_name) +
        vm_label(returnLabel);
}

/** Generate Hack Assembly code for a VM return operation */
string VMTranslator::vm_return(){
    return
    vm_push("local", 0) + vm_pop("temp", 8) +
    "@5\nA=D-A\nD=M\n@R14\nM=D\n" +
    vm_pop("argument", 0) +
    "@ARG\nD=M+1\n@SP\nM=D\n" + 
    "@R13\nAM=M-1\nD=M\n@THAT\nM=D\n" + 
    "@R13\nAM=M-1\nD=M\n@THIS\nM=D\n" + 
    "@R13\nAM=M-1\nD=M\n@ARG\nM=D\n" + 
    "@R13\nAM=M-1\nD=M\n@LCL\nM=D\n" +
    "@R14\nA=M\n0;JMP\n";
}