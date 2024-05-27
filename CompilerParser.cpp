#include "CompilerParser.h"

/**
 * Constructor for the CompilerParser
 * @param tokens A linked list of tokens to be parsed
 */
CompilerParser::CompilerParser(std::list<Token*> tokens) {
    this->tokens = tokens;
    this->currentToken = tokens.begin();
}

/**
 * Generates a parse tree for a single program
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileProgram() {
    return compileClass();
}

/**
 * Generates a parse tree for a single class
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClass() {
    ParseTree* classNode = new ParseTree("class", "");
    std::cout << "parseTree made" << std::endl;
    classNode->addChild(mustBe("keyword", "class"));
    std::cout << "one child added" << std::endl;
    classNode->addChild(mustBe("identifier", ""));
    std::cout << "two childs added" << std::endl;
    classNode->addChild(mustBe("symbol", "{"));
    std::cout << "three childs added" << std::endl;

    while (have("keyword", "static") || have("keyword", "field")) {
        classNode->addChild(compileClassVarDec());
        std::cout << "first while loop executing" << std::endl;
    }
    std::cout << "first while loop exited" << std::endl;
    while (have("keyword", "constructor") || have("keyword", "function") || have("keyword", "method")) {
        classNode->addChild(compileSubroutine());
    }

    classNode->addChild(mustBe("symbol", "}"));
    return classNode;
}

/**
 * Generates a parse tree for a static variable declaration or field declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileClassVarDec() {
    ParseTree* classVarDecNode = new ParseTree("classVarDec", "");

    classVarDecNode->addChild(mustBe("keyword", ""));

    if (have("keyword", "") || have("identifier", "")) {
        classVarDecNode->addChild(mustBe(current()->getType(), current()->getValue()));
    } else {
        throw ParseException();
    }

    classVarDecNode->addChild(mustBe("identifier", ""));

    while (have("symbol", ",")) {
        classVarDecNode->addChild(mustBe("symbol", ","));
        classVarDecNode->addChild(mustBe("identifier", ""));
    }

    classVarDecNode->addChild(mustBe("symbol", ";"));

    return classVarDecNode;
}


/**
 * Generates a parse tree for a method, function, or constructor
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutine() {
    ParseTree* subroutineNode = new ParseTree("subroutine", "");

    subroutineNode->addChild(mustBe("keyword", current()->getValue()));

    if (have("keyword", "") || have("identifier", "")) {
        subroutineNode->addChild(mustBe(current()->getType(), current()->getValue()));
    } else {
        throw ParseException();
    }

    subroutineNode->addChild(mustBe("identifier", ""));
    subroutineNode->addChild(mustBe("symbol", "("));
    subroutineNode->addChild(compileParameterList());
    subroutineNode->addChild(mustBe("symbol", ")"));
    subroutineNode->addChild(compileSubroutineBody());

    return subroutineNode;
}

/**
 * Generates a parse tree for a subroutine's parameters
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileParameterList() {
    ParseTree* parameterListNode = new ParseTree("parameterList", "");

    if (have("symbol", "(")) {
        return parameterListNode;
    }

    if (have("keyword", "") || have("identifier", "")) {
        parameterListNode->addChild(mustBe(current()->getType(), current()->getValue()));
    } else {
        throw ParseException();
    }

    parameterListNode->addChild(mustBe("identifier", ""));

    while (have("symbol", ",")) {
        parameterListNode->addChild(mustBe("symbol", ","));
        if (have("keyword", "") || have("identifier", "")) {
        parameterListNode->addChild(mustBe(current()->getType(), current()->getValue()));
        } else {
        throw ParseException();
        }
        parameterListNode->addChild(mustBe("identifier", ""));
    }

    return parameterListNode;
}

/**
 * Generates a parse tree for a subroutine's body
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileSubroutineBody() {
    return NULL;
}

/**
 * Generates a parse tree for a subroutine variable declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileVarDec() {
    return NULL;
}

/**
 * Generates a parse tree for a series of statements
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileStatements() {
    return NULL;
}

/**
 * Generates a parse tree for a let statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileLet() {
    return NULL;
}

/**
 * Generates a parse tree for an if statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileIf() {
    return NULL;
}

/**
 * Generates a parse tree for a while statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileWhile() {
    return NULL;
}

/**
 * Generates a parse tree for a do statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileDo() {
    return NULL;
}

/**
 * Generates a parse tree for a return statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileReturn() {
    return NULL;
}

/**
 * Generates a parse tree for an expression
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpression() {
    return NULL;
}

/**
 * Generates a parse tree for an expression term
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileTerm() {
    return NULL;
}

/**
 * Generates a parse tree for an expression list
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpressionList() {
    return NULL;
}

/**
 * Advance to the next token
 */
void CompilerParser::next(){
    if (this->currentToken != tokens.end()) {
        currentToken++;
    }
}

/**
 * Return the current token
 * @return the Token
 */
Token* CompilerParser::current(){
    if (this->currentToken != tokens.end()) {
        return *currentToken;
    }
    return nullptr;
}

/**
 * Check if the current token matches the expected type and value.
 * @return true if a match, false otherwise
 */
bool CompilerParser::have(std::string expectedType, std::string expectedValue){
    Token* token = current();
    return (token != nullptr) && (token->getType() == expectedType) && (token->getValue() == expectedValue);
}

/**
 * Check if the current token matches the expected type and value.
 * If so, advance to the next token, returning the current token, otherwise throw a ParseException.
 * @return the current token before advancing
 */
Token* CompilerParser::mustBe(std::string expectedType, std::string expectedValue){
    if (!have(expectedType, expectedValue)) {
        throw ParseException();
    }
    Token* token = current();
    next();
    return token;
}

/**
 * Definition of a ParseException
 * You can use this ParseException with `throw ParseException();`
 */
const char* ParseException::what() {
    return "An Exception occurred while parsing!";
}
