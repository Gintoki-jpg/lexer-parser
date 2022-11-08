#include <iostream>
#include <string>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

typedef map<string, vector<string>> FIRST_TABLE;
typedef map<string, vector<string>> FOLLOW_TABLE;
typedef vector<vector<string>> ANALYZE_TABLE;

class GRAMMAR_TABLE
{
public:
    map<string, vector<string>> generative;
    vector<string> non_terminals;
    vector<string> terminals;
    string start_symbol;
};

class PREDICT_TABLE
{
public:
    map<string, map<string, string>> table;
    vector<string> non_terminals;
    vector<string> terminals;
    string start_symbol;
};

class SyntaxAnalyzer
{
public:
    PREDICT_TABLE create_predict_table(GRAMMAR_TABLE G, FIRST_TABLE first_table, FOLLOW_TABLE follow_table);
    void print_predict_table(PREDICT_TABLE predict_table);
    ANALYZE_TABLE predict_analyze(string input_string, PREDICT_TABLE M);
    void print_analyze_table(ANALYZE_TABLE analyze_table);
    void error(string error_string)
    {
        cout << error_string << endl;
    };
};

void init(GRAMMAR_TABLE &G, FIRST_TABLE &first_table, FOLLOW_TABLE &follow_table);

int startWith(string str, string pattern)
{
    return str.find(pattern) == 0 ? 1 : 0;
}

void init(GRAMMAR_TABLE &G, FIRST_TABLE &first_table, FOLLOW_TABLE &follow_table)
{
    vector<string> E_vector;
    E_vector.push_back("TG");
    G.generative.insert(pair<string, vector<string>>("E", E_vector));
    vector<string> G_vector;
    G_vector.push_back("+TG");
    G_vector.push_back("-TG");
    G_vector.push_back("ε");
    G.generative.insert(pair<string, vector<string>>("G", G_vector));
    vector<string> T_vector;
    T_vector.push_back("FU");
    G.generative.insert(pair<string, vector<string>>("T", T_vector));
    vector<string> U_vector;
    U_vector.push_back("*FU");
    U_vector.push_back("/FU");
    U_vector.push_back("ε");
    G.generative.insert(pair<string, vector<string>>("U", U_vector));
    vector<string> F_vector;
    F_vector.push_back("(E)");
    F_vector.push_back("num");
    G.generative.insert(pair<string, vector<string>>("F", F_vector));
    G.non_terminals.push_back("E");
    G.non_terminals.push_back("G");
    G.non_terminals.push_back("T");
    G.non_terminals.push_back("U");
    G.non_terminals.push_back("F");
    G.terminals.push_back("+");
    G.terminals.push_back("-");
    G.terminals.push_back("*");
    G.terminals.push_back("/");
    G.terminals.push_back("(");
    G.terminals.push_back(")");
    G.terminals.push_back("num");
    G.terminals.push_back("$");
    G.start_symbol = "E";
    vector<string> E_first_vector;
    E_first_vector.push_back("(");
    E_first_vector.push_back("num");
    first_table.insert(pair<string, vector<string>>("E", E_first_vector));
    vector<string> G_first_vector;
    G_first_vector.push_back("+");
    G_first_vector.push_back("-");
    G_first_vector.push_back("ε");
    first_table.insert(pair<string, vector<string>>("G", G_first_vector));
    vector<string> T_first_vector;
    T_first_vector.push_back("(");
    T_first_vector.push_back("num");
    first_table.insert(pair<string, vector<string>>("T", T_first_vector));
    vector<string> U_first_vector;
    U_first_vector.push_back("*");
    U_first_vector.push_back("/");
    U_first_vector.push_back("ε");
    first_table.insert(pair<string, vector<string>>("U", U_first_vector));
    vector<string> F_first_vector;
    F_first_vector.push_back("(");
    F_first_vector.push_back("num");
    first_table.insert(pair<string, vector<string>>("F", F_first_vector));
    vector<string> E_follow_vector;
    E_follow_vector.push_back("$");
    E_follow_vector.push_back(")");
    follow_table.insert(pair<string, vector<string>>("E", E_follow_vector));
    vector<string> G_follow_vector;
    G_follow_vector.push_back("$");
    G_follow_vector.push_back(")");
    follow_table.insert(pair<string, vector<string>>("G", G_follow_vector));
    vector<string> T_follow_vector;
    T_follow_vector.push_back("+");
    T_follow_vector.push_back("-");
    T_follow_vector.push_back("$");
    T_follow_vector.push_back(")");
    follow_table.insert(pair<string, vector<string>>("T", T_follow_vector));
    vector<string> U_follow_vector;
    U_follow_vector.push_back("+");
    U_follow_vector.push_back("-");
    U_follow_vector.push_back("$");
    U_follow_vector.push_back(")");
    follow_table.insert(pair<string, vector<string>>("U", U_follow_vector));
    vector<string> F_follow_vector;
    F_follow_vector.push_back("*");
    F_follow_vector.push_back("/");
    F_follow_vector.push_back("+");
    F_follow_vector.push_back("-");
    F_follow_vector.push_back("$");
    F_follow_vector.push_back(")");
    follow_table.insert(pair<string, vector<string>>("F", F_follow_vector));
}

PREDICT_TABLE SyntaxAnalyzer::create_predict_table(GRAMMAR_TABLE G, FIRST_TABLE first_table, FOLLOW_TABLE follow_table)
{
    PREDICT_TABLE M;
    M.table.insert(pair<string, map<string, string>>("E", map<string, string>()));
    M.table.insert(pair<string, map<string, string>>("G", map<string, string>()));
    M.table.insert(pair<string, map<string, string>>("T", map<string, string>()));
    M.table.insert(pair<string, map<string, string>>("U", map<string, string>()));
    M.table.insert(pair<string, map<string, string>>("F", map<string, string>()));
    for (auto iter = G.generative.begin(); iter != G.generative.end(); iter++)
    {
        string A = iter->first;
        for (auto iter2 = iter->second.begin(); iter2 != iter->second.end(); iter2++)
        {
            string alpha = *iter2;
            if (alpha[0] >= 'A' && alpha[0] <= 'Z')
            {
                vector<string> first_vector = first_table.find(string(1, alpha[0]))->second;
                for (auto a = first_vector.begin(); a != first_vector.end(); a++)
                {
                    if (*a != "ε")
                    {
                        M.table.find(A)->second.insert(pair<string, string>(*a, alpha));
                    }
                }
                if (find(first_vector.begin(), first_vector.end(), "ε") != first_vector.end())
                {
                    vector<string> follow_vector = follow_table.find(A)->second;
                    for (auto b = follow_vector.begin(); b != follow_vector.end(); b++)
                    {
                        if (*b != "ε")
                        {
                            M.table.find(A)->second.insert(pair<string, string>(*b, alpha));
                        }
                    }
                }
            }
            else
            {
                string alpha_first;
                if (startWith(alpha, "num"))
                {
                    alpha_first = "num";
                }
                else if (startWith(alpha, "ε"))
                {
                    alpha_first = "ε";
                }
                else
                {
                    alpha_first = alpha[0];
                }
                if (alpha_first != "ε")
                {
                    M.table.find(A)->second.insert(pair<string, string>(alpha_first, alpha));
                }
                if (alpha_first == "ε")
                {
                    vector<string> follow_vector = follow_table.find(A)->second;
                    for (auto b = follow_vector.begin(); b != follow_vector.end(); b++)
                    {
                        if (*b != "ε")
                        {
                            M.table.find(A)->second.insert(pair<string, string>(*b, alpha));
                        }
                    }
                }
            }
        }
    }
    for (auto iter = G.non_terminals.begin(); iter != G.non_terminals.end(); iter++)
    {
        string A = *iter;
        for (auto iter2 = G.terminals.begin(); iter2 != G.terminals.end(); iter2++)
        {
            string a = *iter2;
            if (M.table.find(A)->second.find(a) == M.table.find(A)->second.end())
            {
                M.table.find(A)->second.insert(pair<string, string>(a, "error"));
            }
        }
    }
    M.non_terminals = G.non_terminals;
    M.terminals = G.terminals;
    M.start_symbol = G.start_symbol;
    return M;
}

void SyntaxAnalyzer::print_predict_table(PREDICT_TABLE M)
{
    cout << "PREDICT_TABLE:" << endl;
    cout << "\t";
    for (auto iter : M.table.begin()->second)
    {
        cout << iter.first << "\t\t";
    }
    cout << endl;
    for (auto iter = M.table.begin(); iter != M.table.end(); iter++)
    {
        cout << iter->first << "\t";
        for (auto iter2 = iter->second.begin(); iter2 != iter->second.end(); iter2++)
        {
            string output_str;
            if (iter2->second == "error")
            {
                output_str = "error";
            }
            else if (iter2->second == "ε")
            {
                output_str = iter->first + "-><epsilon>";
            }
            else
            {
                output_str = iter->first + "->" + iter2->second;
            }
            if (output_str.length() >= 8)
            {
                cout << output_str << "\t";
            }
            else
            {
                cout << output_str << "\t\t";
            }
        }
        cout << endl;
    }
}

ANALYZE_TABLE SyntaxAnalyzer::predict_analyze(string input_string, PREDICT_TABLE M)
{
    ANALYZE_TABLE analyze_table;
    int ip = 0;
    input_string += "$";
    vector<string> stack;
    stack.push_back("$");
    stack.push_back(M.start_symbol);
    while (stack.size() != 1)
    {
        vector<string> analyze_table_item;
        analyze_table.push_back(analyze_table_item);
        string stack_str = "[\"";
        for (auto iter = stack.begin(); iter != stack.end(); iter++)
        {
            stack_str += *iter + "\",\"";
        }
        stack_str.erase(stack_str.length() - 2, 2);
        stack_str += "]";
        analyze_table.back().push_back(stack_str);
        string input_str = input_string.substr(ip);
        analyze_table.back().push_back(input_str);
        string X = stack.back();
        if (find(M.terminals.begin(), M.terminals.end(), X) != M.terminals.end())
        {
            if (startWith(input_string.substr(ip), X))
            {
                ip += X.size();
                stack.pop_back();
            }
            else
            {
                error("Except2 " + X);
                return analyze_table;
            }
        }
        else if (find(M.non_terminals.begin(), M.non_terminals.end(), X) != M.non_terminals.end())
        {
            string input_string_first;
            if (input_string[ip] == 'n' && input_string[ip + 1] == 'u' && input_string[ip + 2] == 'm')
            {
                input_string_first = "num";
            }
            else
            {
                input_string_first = input_string.substr(ip, 1);
            }
            if (M.table.find(X) == M.table.end() || M.table.find(X)->second.find(input_string_first) == M.table.find(X)->second.end())
            {
                error("Except3 " + X);
                return analyze_table;
            }
            string Y = M.table.find(X)->second.find(input_string_first)->second;
            if (Y == "error")
            {
                error("Except4 " + X);
                return analyze_table;
            }
            else
            {
                stack.pop_back();
                if (Y != "ε")
                {
                    for (auto iter = Y.rbegin(); iter != Y.rend(); iter++)
                    {
                        string first;
                        if (*iter == 'm' && *(iter + 1) == 'u' && *(iter + 2) == 'n')
                        {
                            first = "num";
                            iter += 2;
                        }
                        else
                        {
                            first = string(1, *iter);
                        }
                        stack.push_back(first);
                    }
                    analyze_table.back().push_back(X + "->" + Y);
                }
                else
                {
                    analyze_table.back().push_back(X + "-><epsilon>");
                }
            }
        }
        else
        {
            error("Except5 " + X);
            return analyze_table;
        }
    }
    if (input_string[ip] == '$')
    {
        cout << "Accepted" << endl;
        vector<string> analyze_table_item;
        analyze_table.push_back(analyze_table_item);
        analyze_table.back().push_back("[\"$\"]");
        analyze_table.back().push_back("$");
    }
    else
    {
        error("Except6 $");
    }
    return analyze_table;
}

void SyntaxAnalyzer::print_analyze_table(ANALYZE_TABLE analyze_table)
{
    cout << "ANALYZE_TABLE:" << endl;
    for (auto iter = analyze_table.begin(); iter != analyze_table.end(); iter++)
    {
        vector<string> analyze_table_item = *iter;
        for (auto iter2 = analyze_table_item.begin(); iter2 != analyze_table_item.end(); iter2++)
        {
            cout << *iter2;
            if (iter2 == analyze_table_item.begin())
            {
                for (int i = 0; i < 6 - iter2->size() / 8; i++)
                {
                    cout << "\t";
                }
            }
            else
            {
                for (int i = 0; i < 4 - iter2->size() / 8; i++)
                {
                    cout << "\t";
                }
            }
        }
        cout << endl;
    }
}

string process(string str)
{
    string newStr;
    int isNum = 0;
    for (int i = 0; i < str.size(); i++)
    {
        if ((str[i] >= '0' && str[i] <= '9') || str[i] == '.')
        {
            if (!isNum)
            {
                isNum = 1;
                newStr += "num";
            }
            continue;
        }
        else
        {
            isNum = 0;
            newStr += str[i];
        }
    }
    return newStr;
}

int main()
{
    SyntaxAnalyzer sa;
    GRAMMAR_TABLE G;
    FIRST_TABLE first_table;
    FOLLOW_TABLE follow_table;
    init(G, first_table, follow_table);
    PREDICT_TABLE M = sa.create_predict_table(G, first_table, follow_table);
    sa.print_predict_table(M);
    cout << "Please input string:" << endl;
    string input_string;
    cin >> input_string;
    input_string = process(input_string);
    ANALYZE_TABLE at = sa.predict_analyze(input_string, M);
    sa.print_analyze_table(at);
    system("pause");
    return 0;
}