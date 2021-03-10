#pragma once
#include<queue>
#include<iostream> 

#include"TreeNode.h"
#include"ParserToken.h"

//<translation-unit> ::= {<expression>}*
//<expression> ::= {{ <declaration> | <constant-expression>} ; }*
//<declaration> ::= <type-specifier> <declarator> { , <declarator>}* 
//<declarator> ::= <valiable> = <initializer>
//<initializer> ::= <constant-expression>
//<constant-expression> ::= <term> + <term> | <term> - <term> | <term>
//<term> ::= <uni_operation> * <uni_operation> | <uni_operation> / <uni_operation> | <uni_operation> % <uni_operation> | <uni_operation>
//<uni_operation> ::= +<factor> | -<factor>
//<factor> ::= <valiable> | <numeral> | Åg(" + <constant-expression> Åg)"
class MyParser {
public:
    MyParser() {}

    TreeNode<ParserToken> parse(const std::queue<ParserToken>& tokens) {
        _tokens = tokens;
        //return  Declaration();
        return ConstantExpression();
    }

private:

    void Debug(std::string token) {
        indent += " ";
        std::cout << indent << token << std::endl;
    }
    void DebugEnd() { indent.pop_back(); }
    //ÉfÉoÉbÉOóp
    std::string indent = "";
    std::queue<ParserToken> _tokens;

    //<declaration> ::= <type-specifier> <declarator> { , <declarator>}* ;
    TreeNode<ParserToken> Declaration()
    {
        Debug("Declaration");
        if (!_tokens.empty()) {
            TreeNode<ParserToken>  type = _tokens.front(); _tokens.pop();
            TreeNode<ParserToken > declarator = Declarator();
            type.Push(declarator);
            while (!_tokens.empty() &&
                (_tokens.front().getTokenType() == TokenType::COMMA)
                ) {
                _tokens.pop();
                TreeNode<ParserToken>  declarator_ = Declarator();
                type.Push(declarator_);
            }
            DebugEnd();
            return type;
        }
        DebugEnd();
        return {};
    }

    //<declarator> ::= <valiable> = <initializer>
    TreeNode<ParserToken> Declarator()
    {
        Debug("Declarator");
        if (!_tokens.empty()) {
            TreeNode<ParserToken>  valiable = _tokens.front(); _tokens.pop();
            if (_tokens.front().getTokenType() == TokenType::ASSIGN) {
                ParserToken operator_ = _tokens.front();
                _tokens.pop();
                TreeNode<ParserToken> initializer = Initializer();
                DebugEnd();
                return TreeNode<ParserToken>(operator_, valiable, initializer);
            }
        }
        DebugEnd();
        return {};
    }
    //<initializer> ::= <constant-expression>
    TreeNode<ParserToken> Initializer()
    {
        Debug("Initializer");
        DebugEnd();
        return ConstantExpression();
    }
    //<expression>::=<term> + <term> | <term> - <term> | <term>
    TreeNode<ParserToken> ConstantExpression()
    {
        Debug("constant_expression");
        TreeNode<ParserToken> left = Term();
        while (!_tokens.empty() &&
            (_tokens.front().getTokenType() == TokenType::ADD || _tokens.front().getTokenType() == TokenType::SUB)
            ) {
            ParserToken operator2 = _tokens.front(); _tokens.pop();
            TreeNode<ParserToken> right = Term();
            left = TreeNode<ParserToken>(operator2, left, right);
        }
        DebugEnd();
        return left;
    }

    //<term>::= <uni_operation> * <uni_operation> | <uni_operation> / <uni_operation> | <uni_operation> % <uni_operation> | <uni_operation>
    TreeNode<ParserToken> Term()
    {
        Debug("term");
        if (!_tokens.empty() && _tokens.front().getTokenType() == TokenType::SUB) {
            ParserToken operator1 = _tokens.front(); _tokens.pop();
            TreeNode<ParserToken> left = UniOperation();
            left = TreeNode<ParserToken>(operator1, left);
            DebugEnd();
            return left;
        }
        TreeNode<ParserToken> left = UniOperation();
        while (!_tokens.empty() &&
            (_tokens.front().getTokenType() == TokenType::MUL || _tokens.front().getTokenType() == TokenType::DIV || _tokens.front().getTokenType() == TokenType::MOD)
            ) {
            ParserToken operator1 = _tokens.front(); _tokens.pop();
            TreeNode<ParserToken> right = UniOperation();
            left = TreeNode<ParserToken>(operator1, left, right);
        }
        DebugEnd();
        return left;
    }

    //<uni_operation>::= +<factor> | -<factor>
    TreeNode<ParserToken> UniOperation() {
        Debug("uni_operation");
        if (!_tokens.empty() && (_tokens.front().getTokenType() == TokenType::ADD || _tokens.front().getTokenType() == TokenType::SUB)) {
            ParserToken operator1 = _tokens.front(); _tokens.pop();
            TreeNode<ParserToken> left = Factor();
            left = TreeNode<ParserToken>(operator1, left);
            DebugEnd();
            return left;
        }
        TreeNode<ParserToken> left = Factor();
        DebugEnd();
        return left;
    }

    //<factor>::=<valiable> |<numeral> | Åg(" + <constant-expression> Åg)"
    TreeNode<ParserToken> Factor()
    {
        Debug("factor");
        if (_tokens.front().getTokenType() == TokenType::LPAREN) {
            _tokens.pop();
            TreeNode<ParserToken> exp = ConstantExpression();
            if (!_tokens.empty() && _tokens.front().getTokenType() == TokenType::RPAREN) {
                _tokens.pop();
                DebugEnd();
                return exp;
            }
        }

        if (_tokens.front().getTokenType() == TokenType::NUMBER) {
            TreeNode<ParserToken> num(_tokens.front());
            _tokens.pop();
            DebugEnd();
            return num;
        }
        if (_tokens.front().getTokenType() == TokenType::NAME) {
            TreeNode<ParserToken> num(_tokens.front());
            _tokens.pop();
            DebugEnd();
            return num;
        }
    }
};