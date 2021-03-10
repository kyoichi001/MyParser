#include<iostream>
#include <memory>
#include<vector>
#include <map>
#include <string>
#include<cmath>
#include <iomanip> // setprecisionを使用するのに必要
#include <algorithm>

#define REP(i,N) for(int i=0;i<(N);i++)
#define REP2(i,a,N) for(int i=(a);i<(N);i++)

using namespace std;
using ll = long long;


#include<queue>
#include "Parser.h"
#include "Lexer.h"

class ParserEvaluator {
    union ParserValue {
        int i;
        double d;
        bool b;
        string s;
    };
    enum ParserType {
        INT,DOUBLE,BOOL,STRING
    };
    ParserType type;
    ParserValue value;
};


double calcrate(map<string,ParserEvaluator>& value_map,TreeNode<ParserToken> operator_) {
    auto childrenCount = operator_.children.size();
    auto operatorValue = operator_.value.getToken();
    auto operatorType = operator_.value.getTokenType();
    if (childrenCount == 2) {//2項演算子
        auto left = calcrate(value_map,operator_.children[0]);
        auto right = calcrate(value_map,operator_.children[1]);
        if (operatorType == TokenType::ADD) return left + right;
        if (operatorType == TokenType::SUB) return left - right;
        if (operatorType == TokenType::MUL) return left * right;
        if (operatorType == TokenType::DIV) return left / right;
        if (operatorType == TokenType::MOD) return (int)left % (int)right;
        if (operatorType == TokenType::ASSIGN) {
        
        }
    }
    else if (childrenCount == 1) {//単項演算子
        auto left = calcrate(value_map,operator_.children[0]);
        if (operatorType == TokenType::ADD) return left;
        if (operatorType == TokenType::SUB) return -left;
    }
    else {
        if(operatorType== TokenType::NUMBER)  return atoi(operator_.value.getToken().c_str());
        if (operatorType == TokenType::NAME) return 1;
    }
}

double calcrate( TreeNode<ParserToken> operator_) {
    auto childrenCount = operator_.children.size();
    auto operatorValue = operator_.value.getToken();
    auto operatorType = operator_.value.getTokenType();
    if (childrenCount == 2) {//2項演算子
        auto left = calcrate( operator_.children[0]);
        auto right = calcrate( operator_.children[1]);
        if (operatorType == TokenType::ADD) return left + right;
        if (operatorType == TokenType::SUB) return left - right;
        if (operatorType == TokenType::MUL) return left * right;
        if (operatorType == TokenType::DIV) return left / right;
        if (operatorType == TokenType::MOD) return (int)left % (int)right;
        if (operatorType == TokenType::ASSIGN) {

        }
    }
    else if (childrenCount == 1) {//単項演算子
        auto left = calcrate( operator_.children[0]);
        if (operatorType == TokenType::ADD) return left;
        if (operatorType == TokenType::SUB) return -left;
    }
    else {
        if (operatorType == TokenType::NUMBER)  return atoi(operator_.value.getToken().c_str());
        if (operatorType == TokenType::NAME) return 1;
    }
    return 0;
}


int main() {
    string target = "6+5*23";
    std::cout << "target : " << target << std::endl;
    MyLexer l = MyLexer(target);
    queue<ParserToken> res1 = l.getTokens();
    while (!res1.empty()) {
        auto a = res1.front();
        res1.pop();
        std::cout << a.to_string() << std::endl;
    }
    res1 = l.getTokens();
    MyParser p = MyParser();
    TreeNode<ParserToken> res2 = p.parse(res1);
    cout << TreeNode<ParserToken>::order_string(res2) << endl;
   cout << calcrate(res2) << endl;
}