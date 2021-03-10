
#include <string>
#include<vector>
#include <queue>
#include "ParserToken.h"

/// <summary>
/// éöãÂâêÕ
/// </summary>
class MyLexer
{
public:
    MyLexer(std::string s) {
        _tokens = std::queue<ParserToken>();

        for (int i = 0; i < s.length(); i++) {
            while (isBlank(s[i])) i++;//ãÛîíâ¸çsì«Ç›îÚÇŒÇµ

            if (isDigit(s[i])) {
                std::string res = getNum(s, i);
                i--;
                addToken(res, TokenType::NUMBER);
                continue;
            }

            if (isAlpha(s[i])) {
                std::string res = getWord(s, i);
                i--;
                if (isType(res))addToken(res, TokenType::TYPE);
                else addToken(res, TokenType::NAME);
                continue;
            }

            if (s[i]==',') {
                addToken(std::string{ s[i] }, TokenType::COMMA);
                continue;
            }
            if (s[i] == '=') {
                addToken(std::string{ s[i] }, TokenType::ASSIGN);
                continue;
            }


            if (s[i]=='*') {
                addToken(std::string{ s[i] }, TokenType::MUL);
                continue;
            }
            if (s[i]=='/') {
                addToken(std::string{ s[i] }, TokenType::DIV);
                continue;
            }
            if (s[i]=='%') {
                addToken(std::string{ s[i] }, TokenType::MOD);
                continue;
            }

            if (s[i]=='+') {
                addToken(std::string{ s[i] }, TokenType::ADD);
                continue;
            }
            if (s[i]=='-') {
                addToken(std::string{ s[i] }, TokenType::SUB);
                continue;
            }

            if (s[i] == '(') {
                addToken(std::string{ s[i] }, TokenType::LPAREN);
                continue;
            }

            if (s[i] == ')') {
                addToken(std::string{ s[i] }, TokenType::RPAREN);
                continue;
            }

           // throw runtime_error("Lexer error");
        }
    }

    std::queue<ParserToken> getTokens() const { return _tokens; }

private:
    std::queue<ParserToken> _tokens;
    std::string getNum(std::string original, int& currentIndex) {
        std::string res = "";
        res += original[currentIndex++];
        while (isDigit(original[currentIndex])) {
            res += original[currentIndex++];
        }
        if (original[currentIndex] == '.') res += original[currentIndex++];
        while (isDigit(original[currentIndex])) {
            res += original[currentIndex++];
        }
        return res;
    }
    std::string getWord(std::string original, int& currentIndex) {
        std::string res = "";
        res += original[currentIndex++];
        while (isIdentifier(original[currentIndex])) {
            res += original[currentIndex++];
        }
        return res;
    }
    void addToken(std::string letter, TokenType tokenType) {
        _tokens.push(ParserToken(letter, tokenType));
    }

    static bool isType(std::string text) { return text == "int" || text == "double" || text == "bool"; }

    static bool isBlank(char letter) { return letter == ' ' || letter == '\t' || letter == '\n'; }
    static bool isDigit(char letter) { return '0' <= letter && letter <= '9'; }
    static bool isAlpha(char letter) { return 'a' <= letter && letter <= 'z' || 'A' <= letter && letter <= 'Z'; }
    static bool isIdentifier(char letter) { return isAlpha(letter) || isDigit(letter) || letter == '_'; };
};