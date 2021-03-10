#pragma once

#include <string>


//https://qiita.com/hideckies/items/aa52af2b4a0b24303b3f
enum class TokenType {

    NAME,       // identifier
    TYPE,       //Œ^

    ASSIGN,     // "="

    LETTER,     // letter

    STRING,     // string
    NUMBER,     // real number

    S_QUOTES,   // '
    D_QUOTES,   // "

    COLON,      // ":"
    SEMICOLON,  // ";"

    COMMA,      // ","
    DOT,        // "."

    CLASS,      // "class"

    FUNC,       // function

    IF,         // if
    ELIF,       // elif
    ELSE,       // else

    LPAREN,     // "("
    RPAREN,     // ")"
    LSQUARE,    // "["
    RSQUARE,    // "]"
    LBRACE,     // "{"
    RBRACE,     // "}"

    OPERATOR2,  // "+","-"
    ADD,        // "+"
    SUB,        // "-"

    OPERATOR1,  // "*","/" ,"%"
    MUL,       // "*"
    DIV,       // "/"
    MOD,        // "%"

    LESS,       // "<"
    GREAT,      // ">"

    EQUAL,      // "=="
    NOT_EQ,     // "!="
    LESS_EQ,    // "<="
    GREAT_EQ,   // ">="

    AND,        // "&&"
    OR,         // "||"


    NULLTYPE,   // null
    E_O_T,      // End of Token
};

//https://joho-ka.mints.ne.jp/create-abstract-syntax-tree?doing_wp_cron=1607037495.0281510353088378906250
class ParserToken
{
public:
    ParserToken() :_tokenType(TokenType::E_O_T) {}
    ParserToken(std::string token, TokenType tokenType) :_token(token), _tokenType(tokenType) {}

    std::string getToken() const { return _token; }
    TokenType getTokenType()const { return _tokenType; }

    std::string to_string() const { return "(" + _token + "," + TokenTypeString(_tokenType) + ")"; }
    operator std::string() const { return to_string(); }
    static std::string TokenTypeString(TokenType type) {
        switch (type)
        {
        case TokenType::NAME:return "name";
        case TokenType::TYPE:return "type";
        case TokenType::ASSIGN:return "assign";
        case TokenType::LETTER:return "letter";
        case TokenType::STRING:return "string";
        case TokenType::NUMBER:return "number";
        case TokenType::S_QUOTES:return "single_quote";
        case TokenType::D_QUOTES:return "double_quote";
        case TokenType::COLON:return "colon";
        case TokenType::SEMICOLON:return "semicolon";
        case TokenType::COMMA:return "comma";
        case TokenType::DOT:return "dot";
        case TokenType::CLASS:return "class";
        case TokenType::FUNC:return "function";
        case TokenType::IF:return "if";
        case TokenType::ELIF:return "elif";
        case TokenType::ELSE:return "else";
        case TokenType::LPAREN:return "(";
        case TokenType::RPAREN:return ")";
        case TokenType::LSQUARE:return "[";
        case TokenType::RSQUARE:return "]";
        case TokenType::LBRACE:return "{";
        case TokenType::RBRACE:return "}";
        case TokenType::OPERATOR2:return "+-";
        case TokenType::ADD:return "+";
        case TokenType::SUB:return "-";
        case TokenType::OPERATOR1:return "*/%";
        case TokenType::MUL:return "*";
        case TokenType::DIV:return "/";
        case TokenType::MOD:return "%";
        case TokenType::LESS:return "<";
        case TokenType::GREAT:return ">";
        case TokenType::EQUAL:return "==";
        case TokenType::NOT_EQ:return "!=";
        case TokenType::LESS_EQ:return "<=";
        case TokenType::GREAT_EQ:return ">=";
        case TokenType::AND:return "&";
        case TokenType::OR:return "|";
        case TokenType::NULLTYPE:return "null";
        case TokenType::E_O_T:return "e_o_t";
        }
    }
private:
    std::string _token;
    TokenType _tokenType;
};