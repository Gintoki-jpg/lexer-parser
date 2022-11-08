#include "parser.h"

// @breif: reopen the file
// @return: reopen state
int parser::fileRenew()
{
    file.close();
    file.open(filename, ios::in);
    return 0;
}

// @breif: count file line
// @return: line number
int parser::countLine()
{

    fileRenew();
    string tmp;
    int n = 1;
    while (getline(file, tmp))
    {
        n++;
    }
    return n;
}

// @breif: count file char
// @return: char number
int parser::countChar()
{
    fileRenew();
    char tmp;
    int n = -1;
    while (!file.eof())
    {
        tmp = file.get();
        n++;
    }
    return n;
}

// @breif: parse the file
// @return: parse answer
string parser::parseFile()
{
    fileRenew();
    // continuly read the file
    while (!file.eof() && !file.fail())
    {
        // DFA
        switch (state)
        {
        case states::begin:
            token[0] = 0;
            get_char();
            get_nbc();
            switch (C)
            {
            case '_':
            case 'a':
            case 'b':
            case 'c':
            case 'd':
            case 'e':
            case 'f':
            case 'g':
            case 'h':
            case 'i':
            case 'j':
            case 'k':
            case 'l':
            case 'm':
            case 'n':
            case 'o':
            case 'p':
            case 'q':
            case 'r':
            case 's':
            case 't':
            case 'u':
            case 'v':
            case 'w':
            case 'x':
            case 'y':
            case 'z':
            case 'A':
            case 'B':
            case 'C':
            case 'D':
            case 'E':
            case 'F':
            case 'G':
            case 'H':
            case 'I':
            case 'J':
            case 'K':
            case 'L':
            case 'M':
            case 'N':
            case 'O':
            case 'P':
            case 'Q':
            case 'R':
            case 'S':
            case 'T':
            case 'U':
            case 'V':
            case 'W':
            case 'X':
            case 'Y':
            case 'Z':
                loc.line = lineCount;
                loc.col = charCount;
                state = states::id_1;
                break;

            case '0':
            case '1':
            case '2':
            case '3':
            case '4':
            case '5':
            case '6':
            case '7':
            case '8':
            case '9':
                loc.line = lineCount;
                loc.col = charCount;
                state = states::digit_1;
                break;

            case '>':
                loc.line = lineCount;
                loc.col = charCount;
                state = states::opr_1_1;
                break;

            case '<':
                loc.line = lineCount;
                loc.col = charCount;
                state = states::opr_2_1;
                break;

            case '!':
                loc.line = lineCount;
                loc.col = charCount;
                state = states::opr_3;
                break;

            case '=':
                loc.line = lineCount;
                loc.col = charCount;
                state = states::opr_4;
                break;

            case '|':
                loc.line = lineCount;
                loc.col = charCount;
                state = states::opr_5;
                break;

            case '&':
                loc.line = lineCount;
                loc.col = charCount;
                state = states::opr_6;
                break;

            case '+':
                loc.line = lineCount;
                loc.col = charCount;
                state = states::opr_7;
                break;

            case '-':
                loc.line = lineCount;
                loc.col = charCount;
                state = states::opr_8;
                break;

            case '*':
                loc.line = lineCount;
                loc.col = charCount;
                state = states::opr_9;
                break;

            case '/':
                loc.line = lineCount;
                loc.col = charCount;
                state = states::opr_10;
                break;

            case '%':
                loc.line = lineCount;
                loc.col = charCount;
                state = states::opr_11;
                break;

            case '^':
                loc.line = lineCount;
                loc.col = charCount;
                state = states::opr_12;
                break;

            case '\'':
                loc.line = lineCount;
                loc.col = charCount;
                state = states::char_start;
                return_id(wordClass::id, "'", loc);
                C = 0;
                loc.col++;
                token[0] = 0;
                break;

            case '"':
                loc.line = lineCount;
                loc.col = charCount;
                state = states::string_start;
                return_id(wordClass::id, "\"", loc);
                C = 0;
                loc.col++;
                token[0] = 0;
                break;

            case '(':
                loc.line = lineCount;
                loc.col = charCount;
                state = states::begin;
                return_id(wordClass::delimiter, "(", loc);
                break;

            case ')':
                loc.line = lineCount;
                loc.col = charCount;
                state = states::begin;
                return_id(wordClass::delimiter, ")", loc);
                break;

            case '{':
                loc.line = lineCount;
                loc.col = charCount;
                state = states::begin;
                return_id(wordClass::delimiter, "{", loc);
                break;

            case '}':
                loc.line = lineCount;
                loc.col = charCount;
                state = states::begin;
                return_id(wordClass::delimiter, "}", loc);
                break;

            case '[':
                loc.line = lineCount;
                loc.col = charCount;
                state = states::begin;
                return_id(wordClass::delimiter, "[", loc);
                break;

            case ']':
                loc.line = lineCount;
                loc.col = charCount;
                state = states::begin;
                return_id(wordClass::delimiter, "]", loc);
                break;

            case ';':
                loc.line = lineCount;
                loc.col = charCount;
                state = states::begin;
                return_id(wordClass::delimiter, ";", loc);
                break;

            case '.':
                loc.line = lineCount;
                loc.col = charCount;
                state = states::begin;
                return_id(wordClass::delimiter, ".", loc);
                break;

            case ',':
                loc.line = lineCount;
                loc.col = charCount;
                state = states::begin;
                return_id(wordClass::delimiter, ",", loc);
                break;

            case ':':
                loc.line = lineCount;
                loc.col = charCount;
                state = states::begin;
                return_id(wordClass::delimiter, ":", loc);
                break;

            case '#':
                loc.line = lineCount;
                loc.col = charCount;
                state = states::begin;
                return_id(wordClass::delimiter, "#", loc);
                break;

            case '?':
                loc.line = lineCount;
                loc.col = charCount;
                state = states::begin;
                return_id(wordClass::operater, "?", loc);
                break;

            default:
                loc.line = lineCount;
                loc.col = charCount;
                state = states::error_state;
                break;
            }
            break;
        case states::id_1:
            cat();
            get_char();
            if (letter() || digit())
            {
                state = states::id_1;
            }
            else
            {
                retract();
                state = states::begin;
                iskey = reserve();
                if (iskey == keywordClass::not_key_word)
                {
                    return_id(wordClass::id, token, loc);
                }
                else
                {
                    return_id(wordClass::keyword, token, loc);
                }
            }
            break;
        case states::digit_1:
            cat();
            get_char();
            if (digit())
            {
                state = states::digit_1;
            }
            else if (C == '.')
            {
                state = states::digit_2;
            }
            else if (C == 'e' || C == 'E')
            {
                state = states::digit_4;
            }
            else
            {
                retract();
                state = states::begin;
                return_id(wordClass::number, (long long)SToI(), loc);
            }
            break;
        case states::digit_2:
            cat();
            get_char();
            if (digit())
            {
                state = states::digit_3;
            }
            else
            {
                retract();
                state = states::error_state;
            }
            break;
        case states::digit_3:
            cat();
            get_char();
            if (digit())
            {
                state = states::digit_3;
            }
            else if (C == 'e' || C == 'E')
            {
                state = states::digit_4;
            }
            else
            {
                retract();
                state = states::begin;
                return_id(wordClass::digit, SToF(), loc);
            }
            break;
        case states::digit_4:
            cat();
            get_char();
            if (C == '+' || C == '-')
            {
                state = states::digit_5;
            }
            else if (digit())
            {
                state = states::digit_6;
            }
            else
            {
                retract();
                state = states::error_state;
            }
            break;
        case states::digit_5:
            cat();
            get_char();
            if (digit())
            {
                state = states::digit_6;
            }
            else
            {
                retract();
                state = states::error_state;
            }
            break;
        case states::digit_6:
            cat();
            get_char();
            if (digit())
            {
                state = states::digit_6;
            }
            else
            {
                retract();
                state = states::begin;
                return_id(wordClass::digit, SToF(), loc);
            }
            break;
        case states::opr_1_1:
            cat();
            get_char();
            if (C == '=')
            {
                state = states::begin;
                return_id(wordClass::operater, ">=", loc);
            }
            else if (C == '>')
            {
                state = states::opr_1_2;
            }
            else
            {
                retract();
                state = states::begin;
                return_id(wordClass::operater, ">", loc);
            }
            break;
        case states::opr_1_2:
            cat();
            get_char();
            if (C == '=')
            {
                state = states::begin;
                return_id(wordClass::operater, ">>=", loc);
            }
            else
            {
                retract();
                state = states::begin;
                return_id(wordClass::operater, ">>", loc);
            }
            break;
        case states::opr_2_1:
            cat();
            get_char();
            if (C == '=')
            {
                state = states::begin;
                return_id(wordClass::operater, "<=", loc);
            }
            else if (C == '<')
            {
                state = states::opr_2_2;
            }
            else
            {
                retract();
                state = states::begin;
                return_id(wordClass::operater, "<", loc);
            }
            break;
            break;
        case states::opr_2_2:
            cat();
            get_char();
            if (C == '=')
            {
                state = states::begin;
                return_id(wordClass::operater, "<<=", loc);
            }
            else
            {
                retract();
                state = states::begin;
                return_id(wordClass::operater, "<<", loc);
            }
            break;
        case states::opr_3:
            cat();
            get_char();
            if (C == '=')
            {
                state = states::begin;
                return_id(wordClass::operater, "!=", loc);
            }
            else
            {
                retract();
                state = states::begin;
                return_id(wordClass::operater, "!", loc);
            }
            break;
        case states::opr_4:
            cat();
            get_char();
            if (C == '=')
            {
                state = states::begin;
                return_id(wordClass::operater, "==", loc);
            }
            else
            {
                retract();
                state = states::begin;
                return_id(wordClass::operater, "=", loc);
            }
            break;
        case states::opr_5:
            cat();
            get_char();
            if (C == '=')
            {
                state = states::begin;
                return_id(wordClass::operater, "|=", loc);
            }
            else if (C == '|')
            {
                state = states::begin;
                return_id(wordClass::operater, "||", loc);
            }
            else
            {
                retract();
                state = states::begin;
                return_id(wordClass::operater, "|", loc);
            }
            break;
        case states::opr_6:
            cat();
            get_char();
            if (C == '=')
            {
                state = states::begin;
                return_id(wordClass::operater, "&=", loc);
            }
            else if (C == '&')
            {
                state = states::begin;
                return_id(wordClass::operater, "&&", loc);
            }
            else
            {
                retract();
                state = states::begin;
                return_id(wordClass::operater, "&", loc);
            }
            break;
        case states::opr_7:
            cat();
            get_char();
            if (C == '=')
            {
                state = states::begin;
                return_id(wordClass::operater, "+=", loc);
            }
            else if (C == '+')
            {
                state = states::begin;
                return_id(wordClass::operater, "++", loc);
            }
            else
            {
                retract();
                state = states::begin;
                return_id(wordClass::operater, "+", loc);
            }
            break;
        case states::opr_8:
            cat();
            get_char();
            if (C == '=')
            {
                state = states::begin;
                return_id(wordClass::operater, "-=", loc);
            }
            else if (C == '-')
            {
                state = states::begin;
                return_id(wordClass::operater, "--", loc);
            }
            else if (C == '>')
            {
                state = states::begin;
                return_id(wordClass::operater, "->", loc);
            }
            else
            {
                retract();
                state = states::begin;
                return_id(wordClass::operater, "-", loc);
            }
            break;
        case states::opr_9:
            cat();
            get_char();
            if (C == '=')
            {
                state = states::begin;
                return_id(wordClass::operater, "*=", loc);
            }
            else
            {
                retract();
                state = states::begin;
                return_id(wordClass::operater, "*", loc);
            }
            break;
        case states::opr_10:
            cat();
            get_char();
            if (C == '=')
            {
                state = states::begin;
                return_id(wordClass::operater, "/=", loc);
            }
            else if (C == '/')
            {
                state = states::begin;
                string tmp;
                getline(file, tmp);
                lineCount++;
                charCount = 0;
            }
            else if (C == '*')
            {
                state = states::annotation;
            }
            else
            {
                retract();
                state = states::begin;
                return_id(wordClass::operater, "/", loc);
            }
            break;
        case states::opr_11:
            cat();
            get_char();
            if (C == '=')
            {
                state = states::begin;
                return_id(wordClass::operater, "%=", loc);
            }
            else
            {
                retract();
                state = states::begin;
                return_id(wordClass::operater, "%", loc);
            }
            break;
        case states::opr_12:
            cat();
            get_char();
            if (C == '=')
            {
                state = states::begin;
                return_id(wordClass::operater, "^=", loc);
            }
            else
            {
                retract();
                state = states::begin;
                return_id(wordClass::operater, "^", loc);
            }
            break;
        case states::annotation:
            get_char();
            if (C == '*')
            {
                state = states::annotation_end;
            }
            break;
        case states::annotation_end:
            get_char();
            if (C == '/')
            {
                state = states::begin;
            }
            else if (C == '*')
            {
                state = states::annotation_end;
            }
            else
            {
                state = states::annotation;
            }
            break;
        case states::string_start:
            cat();
            get_char();
            if (C == '"')
            {
                state = states::begin;
                return_id(wordClass::string, token, loc);
                return_id(wordClass::id, "\"", loc);
            }
            else if (C == '\\')
            {
                state = states::string_escape;
            }
            else
            {
                state = states::string_start;
            }
            break;
        case states::char_start:
            cat();
            get_char();
            if (C == '\'')
            {
                state = states::begin;
                return_id(wordClass::myChar, token, loc);
                return_id(wordClass::id, "\'", loc);
            }
            else if (C == '\\')
            {
                state = states::char_escape;
            }
            else
            {
                state = states::char_start;
            }
            break;
        case states::string_escape:
            cat();
            get_char();
            state = states::string_start;
            break;
        case states::char_escape:
            cat();
            get_char();
            state = states::char_start;
            break;
        case states::error_state:
            parser::out << "error state" << endl
                        << (int)C << endl
                        << token << endl;
            state = states::begin;
            errorCount++;
            break;
        default:
            break;
        }
    }
    parser::out << "Word count:" << endl;
    parser::out << "ID:        " << wordCount[0] << endl;
    parser::out << "Digit:     " << wordCount[1] << endl;
    parser::out << "Number:    " << wordCount[2] << endl;
    parser::out << "Char:      " << wordCount[3] << endl;
    parser::out << "String:    " << wordCount[4] << endl;
    parser::out << "Operater:  " << wordCount[5] << endl;
    parser::out << "Delimiter: " << wordCount[6] << endl;
    parser::out << "Keyword:   " << wordCount[7] << endl;
    parser::out << "Total:     " << wordCount[0] + wordCount[1] + wordCount[2] + wordCount[3] + wordCount[4] + wordCount[5] + wordCount[6] + wordCount[7] << endl;
    return parser::out.str();
}

// @breif: get char from file
// @return: state
int parser::get_char()
{
    if (!file.eof())
    {
        C = file.get();
        charCount++;
        if (C == '\n')
        {
            lineCount++;
            charCount = 0;
        }
        if (file.fail())
        {
            return -1;
        }
    }
    return 0;
}

// @breif: get a not empty char from file
// @return: state
int parser::get_nbc()
{
    while (!file.eof() && (C == ' ' || C == '\n' || C == '\r' || C == '\t'))
    {
        get_char();
        if (file.fail())
        {
            return -1;
        }
    }
    return 0;
}

// @breif: cat a char to token
void parser::cat()
{
    int n = strlen(token);
    token[n] = C;
    token[n + 1] = 0;
}

// @breif: return if C is a letter
// @return: true or false
bool parser::letter()
{
    return (C >= 'a' && C <= 'z') || (C >= 'A' && C <= 'Z') || C == '_';
}

// @breif: return if C is a digit
// @return: true or false
bool parser::digit()
{
    return (C >= '0' && C <= '9');
}

// @breif: retract a char
void parser::retract()
{
    file.seekg(-1, ios_base::cur);
    char tmp;
    tmp = file.get();
    if (tmp == '\n') // maintain line count
    {
        lineCount--;
    }
    file.seekg(-1, ios_base::cur);
}

// @breif: return a if token is a keyword
// @return: keyword class
keywordClass parser::reserve()
{
    string keywordsStr[] = {"auto", "double", "int", "struct", "break",
                            "else", "long", "switch", "case", "enum", "register", "typedef",
                            "char", "extern", "return", "union", "const", "float", "short",
                            "unsigned", "continue", "for", "signed", "void", "default", "goto",
                            "sizeof", "volatile", "do", "while", "static", "if", "inline", "restrict",
                            "_Alignas", "_alignof", "_Atomic", "_Bool", "_Complex", "_Generic",
                            "_Imaginary", "_Noreturn", "_Static_assert", "_Therad_local"};
    for (int i = 0; i < 44; i++)
    {
        if (strcmp(token, keywordsStr[i].c_str()) == 0)
        {
            return (keywordClass)i;
        }
    }
    return keywordClass::not_key_word;
}

// @breif: convert a string to a int
// @return: int
int parser::SToI()
{
    return atoi(token);
}

// @breif: convert a string to a double
// @return: double
double parser::SToF()
{
    return atof(token);
}

// @breif: output a token
word parser::return_id(wordClass id, char *charArray, location loc)
{
    word tmp;
    tmp.sign = id;
    tmp.attribute_char = string(charArray);
    wordCount[(int)id]++;
    parser::out << "Location:  " << loc.line << ":" << loc.col << endl;
    parser::printClass(id);
    parser::out << "Value:     "
                << tmp.attribute_char << endl
                << endl;
    return tmp;
}

// @breif: output a token
word parser::return_id(wordClass id, double digit, location loc)
{
    word tmp;
    tmp.sign = id;
    tmp.attribute_digit = digit;
    wordCount[(int)id]++;
    parser::out << "Location:  " << loc.line << ":" << loc.col << endl;
    parser::printClass(id);
    parser::out << "Value:     "
                << tmp.attribute_digit << endl
                << endl;
    return tmp;
}

// @breif: output a token
word parser::return_id(wordClass id, long long number, location loc)
{
    word tmp;
    tmp.sign = id;
    tmp.attribute_num = number;
    wordCount[(int)id]++;
    parser::out << "Location:  " << loc.line << ":" << loc.col << endl;
    parser::printClass(id);
    parser::out << "Value:     "
                << tmp.attribute_num << endl
                << endl;
    return tmp;
}

// @breif: output a token
word parser::return_id(wordClass id, const char charArray[], location loc)
{
    word tmp;
    tmp.sign = id;
    tmp.attribute_char = string(charArray);
    wordCount[(int)id]++;
    parser::out << "Location:  " << loc.line << ":" << loc.col << endl;
    parser::printClass(id);
    parser::out << "Value:     "
                << tmp.attribute_char << endl
                << endl;
    return tmp;
}

// @breif: print token type
void parser::printClass(wordClass id)
{

    parser::out << "Type:      ";
    switch (id)
    {
    case wordClass::id:
        parser::out << "id" << endl;
        break;

    case wordClass::digit:
        parser::out << "digit" << endl;
        break;

    case wordClass::number:
        parser::out << "number" << endl;
        break;

    case wordClass::myChar:
        parser::out << "char" << endl;
        break;

    case wordClass::string:
        parser::out << "string" << endl;
        break;

    case wordClass::operater:
        parser::out << "operater" << endl;
        break;

    case wordClass::delimiter:
        parser::out << "delimiter" << endl;
        break;

    case wordClass::keyword:
        parser::out << "keyword" << endl;
        break;

    default:
        parser::out << "error" << endl;
        break;
    }
}