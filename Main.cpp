#include <iostream>
#include <list>

#include "CompilerParser.h"
#include "Token.h"

using namespace std;

int main(int argc, char *argv[]) {

    list<Token*> tokens;
    tokens.push_back(new Token("keyword", "class"));
    tokens.push_back(new Token("identifier", "Main"));
    tokens.push_back(new Token("symbol", "{"));
    tokens.push_back(new Token("keyword", "static"));
    tokens.push_back(new Token("keyword", "int"));
    tokens.push_back(new Token("identifier", "a"));
    tokens.push_back(new Token("symbol", ";"));
    tokens.push_back(new Token("symbol", "}"));

    CompilerParser parser(tokens);
    ParseTree* result = parser.compileProgram();

    try {
        CompilerParser parser(tokens);
        ParseTree* result = parser.compileProgram();
        if (result != NULL){
            cout << result->tostring() << endl;
        }
    } catch (ParseException e) {
        cout << "Error Parsing!" << endl;
    }
    return 0;
}