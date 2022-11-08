%{
    #include <stdio.h>
    #include <string.h>
    #define yywrap() 1
    int wordCount = 0;
    int charCount = 0;
    int line = 1;
    int col = 0;
    void addLine(int cnt);
    void addCol(int cnt);
    void clearCol();
    void addChar(int cnt);
    void addWord(int cnt);
    int count[15] = {0};
%}

line_comment           (\/\/.*\n)
block_comment          (\/\*([^/]|[^*]\/|\n)*?\*\/)
char                   ('([^\\'\n]|\\.)*')
string                 (\"([^\\\"\n]|\\.)*\")
letter                 ([a-zA-Z_])
digit                  ([0-9])
reserved_word          "auto"|"double"|"int"|"struct"|"break"|"else"|"long"|"switch"|"case"|"enum"|"register"|"typedef"|"char"|"extern"|"return"|"union"|"const"|"float"|"short"|"unsigned"|"continue"|"for"|"signed"|"void"|"default"|"goto"|"sizeof"|"volatile"|"do"|"while"|"static"|"if"|"inline"|"restrict"|"_Alignas"|"_alignof"|"_Atomic"|"_Bool"|"_Complex"|"_Generic"|"_Imaginary"|"_Noreturn"|"_Static_assert"|"_Therad_local"
identifier             ({letter}({letter}|{digit})*)
bin_number             (0[bB][01]+)
oct_number             (0[0-7]+)
hex_number             (0[xX][0-9a-fA-F]+)
dec_number             ({digit}+)
float                  ({digit}+\.{digit}+[eE][-+]?{digit}+)
operator               ">"|">>"|">="|">>="|">"|">>"|">="|">>="|"<"|"<<"|"<="|"<<="|"<"|"<<"|"<="|"<<="|"!"|"!="|"="|"=="|"/"|"/="|"*"|"*="|"%"|"%="|"^"|"^="|"|"|"||"|"|="|"?"|"&"|"&&"|"&="|""|"+"|"+="|"++"|""|"-"|"-="|"--"
delimiter              ";"|","|":"|"."|"#"|"["|"]"|"("|")"|"{"|"}"|"<"|">"

%%

{line_comment} {
    printf("Location: %d:%d\n", line, col);
    printf("Type:     Line comment\n");
    printf("Value:    %s\n\n", yytext);
    addChar(yyleng);
    addLine(1);
    clearCol();
    count[0]++;
}
{block_comment} {
    printf("Location: %d:%d\n", line, col);
    printf("Type:     Block comment\n");
    printf("Value:    %s\n\n", yytext);
    addChar(yyleng);
    for (int i = 0; i < strlen(yytext); i++) {
        if (yytext[i] == '\n') {
            addLine(1);
            clearCol();
        } else {
            addCol(1);
        }
    }
    count[1]++;
}
{char} {
    printf("Location: %d:%d\n", line, col);
    printf("Type:     Character\n");
    printf("Value:    %s\n\n", yytext);
    addChar(yyleng);
    addCol(yyleng);
    count[2]++;
}
{string} {
    printf("Location: %d:%d\n", line, col);
    printf("Type:     String\n");
    printf("Value:    %s\n\n", yytext);
    addChar(yyleng);
    addCol(yyleng);
    count[3]++;
}
{reserved_word} {
    printf("Location: %d:%d\n", line, col);
    printf("Type:     Reserved word\n");
    printf("Value:    %s\n\n", yytext);
    addChar(yyleng);
    addCol(yyleng);
    count[4]++;
    addWord(1);
}
{identifier} {
    printf("Location: %d:%d\n", line, col);
    printf("Type:     Identifier\n");
    printf("Value:    %s\n\n", yytext);
    addChar(yyleng);
    addCol(yyleng);
    count[5]++;
    addWord(1);
}
{bin_number} {
    printf("Location: %d:%d\n", line, col);
    printf("Type:     Binary number\n");
    printf("Value:    %s\n\n", yytext);
    addChar(yyleng);
    addCol(yyleng);
    count[6]++;
}
{oct_number} {
    printf("Location: %d:%d\n", line, col);
    printf("Type:     Octal number\n");
    printf("Value:    %s\n\n", yytext);
    addChar(yyleng);
    addCol(yyleng);
    count[7]++;
}
{hex_number} {
    printf("Location: %d:%d\n", line, col);
    printf("Type:     Hexadecimal number\n");
    printf("Value:    %s\n\n", yytext);
    addChar(yyleng);
    addCol(yyleng);
    count[8]++;
}
{dec_number} {
    printf("Location: %d:%d\n", line, col);
    printf("Type:     Decimal number\n");
    printf("Value:    %s\n\n", yytext);
    addChar(yyleng);
    addCol(yyleng);
    count[9]++;
}
{float} {
    printf("Location: %d:%d\n", line, col);
    printf("Type:     Float\n");
    printf("Value:    %s\n\n", yytext);
    addChar(yyleng);
    addCol(yyleng);
    count[10]++;
}
{operator} {
    printf("Location: %d:%d\n", line, col);
    printf("Type:     Operator\n");
    printf("Value:    %s\n\n", yytext);
    addChar(yyleng);
    addCol(yyleng);
    count[11]++;
}
{delimiter} {
    printf("Location: %d:%d\n", line, col);
    printf("Type:     Delimiter\n");
    printf("Value:    %s\n\n", yytext);
    addChar(yyleng);
    addCol(yyleng);
    count[12]++;
}
.       {
    addChar(1);
    addCol(1);
}
\n      {
    addChar(1);
    addLine(1);
    clearCol();
}

%%

int main(void)
{
    puts("------------------------------------------");
    puts("            Lex Parser By Jray            ");
    puts("------------------------------------------");
    yylex();
    puts("------------------------------------------");
    puts("Count:");
    printf("Char: %d\n",charCount);
    printf("Line: %d\n",line);
    printf("Word: %d\n",wordCount);
    puts("\nTokens count:");
    printf("Line comment:       %d\n",count[0]);
    printf("Block comment:      %d\n",count[1]);
    printf("Character:          %d\n",count[2]);
    printf("String:             %d\n",count[3]);
    printf("Reserved word:      %d\n",count[4]);
    printf("Identifier:         %d\n",count[5]);
    printf("Binary number:      %d\n",count[6]);
    printf("Octal number:       %d\n",count[7]);
    printf("Hexadecimal number: %d\n",count[8]);
    printf("Decimal number:     %d\n",count[9]);
    printf("All number:         %d\n", count[6]+count[7]+count[8]+count[9]);
    printf("Float:              %d\n",count[10]);
    printf("Operator:           %d\n",count[11]);
    printf("Delimiter:          %d\n",count[12]);
    puts("------------------------------------------");
    return 0;
}

void addLine(int cnt)   {
    line += cnt;
}
void addCol(int cnt) {
    col += cnt;
}
void clearCol()  {
    col = 0;
}
void addChar(int cnt)  {
    charCount += cnt;
}
void addWord(int cnt)   {
    wordCount += cnt;
}