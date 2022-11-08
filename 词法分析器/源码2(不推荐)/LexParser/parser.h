#pragma once

#define MAX_TOKEN_LENGTH 10240 // max length of a token

#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
#include <stdio.h>
#include <sstream>

using namespace std;

// Token types
enum class wordClass
{
    id,
    digit,
    number,
    myChar,
    string,
    operater,
    delimiter,
    keyword,
    empty
};

// DFA states
enum class states
{
    begin,
    id_1,
    digit_1,
    digit_2,
    digit_3,
    digit_4,
    digit_5,
    digit_6,
    opr_1_1, // >, >>, >=, >>=
    opr_1_2, // >, >>, >=, >>=
    opr_2_1, // <, <<, <=, <<=
    opr_2_2, // <, <<, <=, <<=
    opr_3,   // !, !=
    opr_4,   // =, ==
    opr_5,   // |, ||, |=
    opr_6,   // &, &&, &=
    opr_7,   // +, +=, ++
    opr_8,   // -, -=, --
    opr_9,   // ,*, /*=
    opr_10,  // /, /=, //
    opr_11,  // %, %=
    opr_12,  // ^, ^=
    error_state,
    annotation,
    annotation_end,
    string_start,
    char_start,
    string_escape,
    char_escape
};

// keywords
enum class keywordClass : int
{
    not_key_word = -1,
    keyword_auto,
    keyword_double,
    keyword_int,
    keyword_struct,
    keyword_break,
    keyword_else,
    keyword_long,
    keyword_switch,
    keyword_case,
    keyword_enum,
    keyword_register,
    keyword_typedef,
    keyword_char,
    keyword_extern,
    keyword_return,
    keyword_union,
    keyword_const,
    keyword_float,
    keyword_short,
    keyword_unsigned,
    keyword_continue,
    keyword_for,
    keyword_signed,
    keyword_void,
    keyword_default,
    keyword_goto,
    keyword_sizeof,
    keyword_volatile,
    keyword_do,
    keyword_while,
    keyword_static,
    keyword_if,
    keyword_inline,
    keyword_restrict,
    keyword__Alignas,
    keyword__alignof,
    keyword__Atomic,
    keyword__Bool,
    keyword__Complex,
    keyword__Generic,
    keyword__Imaginary,
    keyword__Noreturn,
    keyword__Static_assert,
    keyword__Therad_local
};

// word class
class word
{
public:
    wordClass sign = wordClass::empty;
    long long attribute_num = 0;
    double attribute_digit = 0;
    string attribute_char = ""; //id_operator_delimiter_keyword
};

// location of a token
class location
{
public:
    int line;
    int col;
};

// parser class
class parser
{
public:
    parser(string _filename) // Parser constructor and init variables
    {
        filename = _filename;
        file.open(filename, ios::in);
        memset(wordCount, 0, sizeof(int) * 6);
        token[0] = 0;
        loc.line = 0;
        loc.col = 0;
    };

    ~parser() // Parser destructor and close file
    {
        file.close();
    };
    ostringstream out;            // output stream
    location loc;                 // location of token
    int lineCount = 1;            // line count
    int charCount = 0;            // char count
    int wordCount[8];             // word count
    int errorCount = 0;           // error count
    string filename;              // filename
    ifstream file;                // file stream
    int fileRenew();              // renew file
    int countLine();              // count line
    int countChar();              // count char
    string parseFile();           // parse file
    states state = states::begin; // current state
    char C;                       // current char
    char token[MAX_TOKEN_LENGTH]; // current token
    int get_char();               // get char from file
    int get_nbc();                // get next char that is not empty
    void cat();                   // cat char to token
    keywordClass iskey;           // is keyword
    bool letter();                // return is letter
    bool digit();                 // return is digit
    void retract();               // retract file pointer
    keywordClass reserve();       // return is keyword
    int SToI();                   // string to int
    double SToF();                // string to double
    // ouput tokens
    word return_id(wordClass id, char *charArray, location loc);
    word return_id(wordClass id, double digit, location loc);
    word return_id(wordClass id, long long number, location loc);
    word return_id(wordClass id, const char charArray[], location loc);
    void printClass(wordClass id); // output wordClass
};