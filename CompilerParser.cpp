#include "CompilerParser.h"

/**
 * Constructor for the CompilerParser
 * @param tokens A linked list of tokens to be parsed
 */
CompilerParser::CompilerParser(std::list<Token*> tokens) {
    this->tokens = tokens;
    this->currentToken = this->tokens.begin();
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

    classNode->addChild(mustBe("keyword", "class"));
    classNode->addChild(mustBe("identifier", ""));
    classNode->addChild(mustBe("symbol", "{"));

    while (have("keyword", "static") || have("keyword", "field")) {
        classNode->addChild(compileClassVarDec());
        std::cout << "first while loop executing" << std::endl;
    }
    std::cout << "first while loop exited" << std::endl;
    while (have("keyword", "constructor") || have("keyword", "function") || have("keyword", "method")) {
        classNode->addChild(compileSubroutine());
    }

    classNode->addChild(mustBe("symbol", "}"));
    std::cout << "compile class done" << std::endl;
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

    subroutineNode->addChild(mustBe("keyword", ""));
    std::cout << "before if" << std::endl;
    if (have("keyword", "") || have("identifier", "")) {
        subroutineNode->addChild(mustBe(current()->getType(), current()->getValue()));
    } else {
        throw ParseException();
    }
    std::cout << "after if" << std::endl;
    subroutineNode->addChild(mustBe("identifier", ""));
    std::cout << "after identifier" << std::endl;
    subroutineNode->addChild(mustBe("symbol", "("));
    std::cout << "after symbol" << std::endl;
    subroutineNode->addChild(compileParameterList());
    std::cout << "after paramList" << std::endl;
    subroutineNode->addChild(mustBe("symbol", ")"));
    subroutineNode->addChild(compileSubroutineBody());
    std::cout << "after subroutineBody" << std::endl;

    return subroutineNode;
}

/**
 * Generates a parse tree for a subroutine's parameters
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileParameterList() {
    ParseTree* parameterListNode = new ParseTree("parameterList", "");

    if (have("symbol", ")")) {
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
    ParseTree* subroutineBodyNode = new ParseTree("subroutineBody", "");
    std::cout << "before first addchild" << std::endl;
    subroutineBodyNode->addChild(mustBe("symbol", "{"));
    std::cout << "before vardec" << std::endl;
    while (have("keyword", "var")) {
        subroutineBodyNode->addChild(compileVarDec());
    }
    std::cout << "after vardec" << std::endl;
    subroutineBodyNode->addChild(compileStatements());
    std::cout << "after statements" << std::endl;
    subroutineBodyNode->addChild(mustBe("symbol", "}"));

    return subroutineBodyNode;
}

/**
 * Generates a parse tree for a subroutine variable declaration
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileVarDec() {
    ParseTree* varDecNode = new ParseTree("varDec", "");

    varDecNode->addChild(mustBe("keyword", "var"));

    if (have("keyword", "") || have("identifier", "")) {
        varDecNode->addChild(mustBe(current()->getType(), ""));
    }

    varDecNode->addChild(mustBe("identifier", ""));

    while (have("symbol", ",")) {
        varDecNode->addChild(mustBe("symbol", ","));
        varDecNode->addChild(mustBe("identifier", ""));
    }

    varDecNode->addChild(mustBe("symbol", ";"));

    return varDecNode;
}

/**
 * Generates a parse tree for a series of statements
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileStatements() {
    ParseTree* statementsNode = new ParseTree("statements", "");

    while (have("keyword", "let") || have("keyword", "if") || have("keyword", "while") || have("keyword", "do") || have("keyword", "return")) {
        std::cout << "entered statements while loop" << std::endl;
        if (have("keyword", "let")) {
            statementsNode->addChild(compileLet());
        } else if (have("keyword", "if")) {
            statementsNode->addChild(compileIf());
        } else if (have("keyword", "while")) {
            statementsNode->addChild(compileWhile());
        } else if (have("keyword", "do")) {
            statementsNode->addChild(compileDo());
        } else if (have("keyword", "return")) {
            statementsNode->addChild(compileReturn());
        }
        std::cout << "passed statements while loop" << std::endl;
    }
    std::cout << "exited statements while loop" << std::endl;
    return statementsNode;
}

/**
 * Generates a parse tree for a let statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileLet() {
    ParseTree* letNode = new ParseTree("letStatement", "");
    std::cout << "before let" << std::endl;
    letNode->addChild(mustBe("keyword", "let"));
    letNode->addChild(mustBe("identifier", ""));
    std::cout << "before let if" << std::endl;
    if (have("symbol", "[")) {
        letNode->addChild(mustBe("symbol", "["));
        letNode->addChild(compileExpression());
        letNode->addChild(mustBe("symbol", "]"));
    }
    std::cout << "after let if" << std::endl;
    letNode->addChild(mustBe("symbol", "="));
    std::cout << "before expression" << std::endl;
    letNode->addChild(compileExpression());
    std::cout << "after expression" << std::endl;
    letNode->addChild(mustBe("symbol", ";"));
    std::cout << "after let return" << std::endl;
    return letNode;
}

/**
 * Generates a parse tree for an if statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileIf() {
    ParseTree* ifNode = new ParseTree("ifStatement", "");

    ifNode->addChild(mustBe("keyword", "if"));
    ifNode->addChild(mustBe("symbol", "("));
    ifNode->addChild(compileExpression());
    ifNode->addChild(mustBe("symbol", ")"));
    ifNode->addChild(mustBe("symbol", "{"));
    ifNode->addChild(compileStatements());
    ifNode->addChild(mustBe("symbol", "}"));
    
    if (have("keyword", "else")) {
        ifNode->addChild(mustBe("keyword", "else"));
        ifNode->addChild(mustBe("symbol", "{"));
        ifNode->addChild(compileStatements());
        ifNode->addChild(mustBe("symbol", "}"));
    }

    return ifNode;
}

/**
 * Generates a parse tree for a while statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileWhile() {
    ParseTree* whileNode = new ParseTree("whileStatement", "");

    whileNode->addChild(mustBe("keyword", "while"));
    whileNode->addChild(mustBe("symbol", "("));
    whileNode->addChild(compileExpression());
    whileNode->addChild(mustBe("symbol", ")"));
    whileNode->addChild(mustBe("symbol", "{"));
    whileNode->addChild(compileStatements());
    whileNode->addChild(mustBe("symbol", "}"));

    return whileNode;
}

/**
 * Generates a parse tree for a do statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileDo() {
    ParseTree* doNode = new ParseTree("doStatement", "");

    doNode->addChild(mustBe("keyword", "do"));
    doNode->addChild(compileExpression());
    doNode->addChild(mustBe("symbol", ";"));

    return doNode;
}

/**
 * Generates a parse tree for a return statement
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileReturn() {
    ParseTree* returnNode = new ParseTree("returnStatement", "");

    returnNode->addChild(mustBe("keyword", "return"));

    if (!have("symbol", ";")) {
        returnNode->addChild(compileExpression());
    }

    returnNode->addChild(mustBe("symbol", ";"));

    return returnNode;
}

/**
 * Generates a parse tree for an expression
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpression() {
    ParseTree* expressionNode = new ParseTree("expression", "");
    expressionNode->addChild(compileTerm());

    while (have("symbol", "+") || have("symbol", "-") || have("symbol", "*") || 
           have("symbol", "/") || have("symbol", "&") || have("symbol", "|") || 
           have("symbol", "<") || have("symbol", ">") || have("symbol", "=")) {
        expressionNode->addChild(mustBe("symbol", current()->getValue()));
        expressionNode->addChild(compileTerm());
    }

    return expressionNode;
}

/**
 * Generates a parse tree for an expression term
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileTerm() {
    ParseTree* termNode = new ParseTree("term", "");

    if (have("integerConstant", "")) {
        termNode->addChild(mustBe("integerConstant", current()->getValue()));
    } else if (have("stringConstant", "")) {
        termNode->addChild(mustBe("stringConstant", current()->getValue()));
    } else if (have("keyword", "true") || have("keyword", "false") || 
               have("keyword", "null") || have("keyword", "this")) {
        termNode->addChild(mustBe("keyword", current()->getValue()));
    } else if (have("identifier", "")) {
        termNode->addChild(mustBe("identifier", ""));
        
        if (have("symbol", "[")) {
            termNode->addChild(mustBe("symbol", "["));
            termNode->addChild(compileExpression());
            termNode->addChild(mustBe("symbol", "]"));
        } else if (have("symbol", "(")) {
            termNode->addChild(mustBe("symbol", "("));
            termNode->addChild(compileExpressionList());
            termNode->addChild(mustBe("symbol", ")"));
        } else if (have("symbol", ".")) {
            termNode->addChild(mustBe("symbol", "."));
            termNode->addChild(mustBe("identifier", ""));
            termNode->addChild(mustBe("symbol", "("));
            termNode->addChild(compileExpressionList());
            termNode->addChild(mustBe("symbol", ")"));
        }
    } else if (have("symbol", "(")) {
        termNode->addChild(mustBe("symbol", "("));
        termNode->addChild(compileExpression());
        termNode->addChild(mustBe("symbol", ")"));
    } else if (have("symbol", "-") || have("symbol", "~")) {
        termNode->addChild(mustBe("symbol", current()->getValue()));
        termNode->addChild(compileTerm());
    } else {
        throw ParseException();
    }

    return termNode;
}

/**
 * Generates a parse tree for an expression list
 * @return a ParseTree
 */
ParseTree* CompilerParser::compileExpressionList() {
    ParseTree* expressionListNode = new ParseTree("expressionList", "");

    if (!have("symbol", ")")) {
        expressionListNode->addChild(compileExpression());

        while (have("symbol", ",")) {
            expressionListNode->addChild(mustBe("symbol", ","));
            expressionListNode->addChild(compileExpression());
        }
    }

    return expressionListNode;
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
    if (token == nullptr) {
        return false;  
    }
    if (expectedValue.empty()) {
        return token->getType() == expectedType;
    } else {
        return token->getType() == expectedType && token->getValue() == expectedValue;
    }
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
