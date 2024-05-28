#include <iostream>
#include <list>

#include "CompilerParser.h"
#include "Token.h"

using namespace std;

int main(int argc, char *argv[]) {
    // class Main { function void test ( ) { } }  
    list<Token*> tokens;
    tokens.push_back(new Token("keyword", "class"));
    tokens.push_back(new Token("identifier", "Main"));
    tokens.push_back(new Token("symbol", "{"));
    tokens.push_back(new Token("keyword", "function"));
    tokens.push_back(new Token("keyword", "void"));
    tokens.push_back(new Token("identifier", "test"));
    tokens.push_back(new Token("symbol", "("));
    tokens.push_back(new Token("symbol", ")"));
    tokens.push_back(new Token("symbol", "{"));
    tokens.push_back(new Token("symbol", "}"));
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