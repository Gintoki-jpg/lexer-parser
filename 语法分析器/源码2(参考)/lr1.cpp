#include <string>
#include <map>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

typedef map<string, map<string, string>> analyse_table;

class SyntaxAnalyzer
{
public:
    void loadTable(string file_name);
    void loadFormula(string file_name);
    void analyse(string str);
    int startWith(string str, string start)
    {
        return str.find(start) == 0 ? 1 : 0;
    }

private:
    analyse_table _table;
    vector<pair<string, string>> _formula;
    void _printStack(vector<string> stack, vector<string> state_stack, string str, string action)
    {
        string ans;
        for (auto i : state_stack)
        {
            ans += i + " ";
        }
        cout << ans;
        for (int i = 0; i < (6 - ans.size() / 8); i++)
        {
            cout << "\t";
        }
        cout << str;
        for (int i = 0; i < (6 - str.size() / 8); i++)
        {
            cout << "\t";
        }
        cout << action << endl;
        cout << "| ";
        for (auto i : stack)
        {
            cout << i << " ";
        }
        cout << endl;
    };
};

void SyntaxAnalyzer::loadTable(string file_name)
{
    ifstream file(file_name);
    if (!file.is_open())
    {
        cout << "Error: file " << file_name << " not found" << endl;
        return;
    }
    analyse_table table;
    string line;
    vector<string> tokens;
    getline(file, line);
    string word;
    for (int i = 0; i < line.size(); i++)
    {
        if (line[i] == ',' || line[i] == '\n')
        {
            string str2 = "state";
            if (word.size() > 0 && word.compare(str2) != 0)
            {
                tokens.push_back(word);
                word.clear();
            }
            else
            {
                word.clear();
            }
        }
        else
        {
            word += line[i];
        }
    }
    while (getline(file, line))
    {
        string word;
        int count = 0;
        string state;
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == ',')
            {
                if (count == 0)
                {
                    table.insert(make_pair(word, map<string, string>()));
                    state = word;
                    count++;
                }
                else if (word != string("0"))
                {
                    table[state].insert(make_pair(tokens[count - 1], word));
                    count++;
                }
                else
                {
                    count++;
                }
                word.clear();
            }
            else
            {
                word += line[i];
            }
        }
    }
    file.close();
    _table = table;
}

void SyntaxAnalyzer::loadFormula(string file_name)
{
    ifstream file(file_name);
    if (!file.is_open())
    {
        cout << "Error: file " << file_name << " not found" << endl;
        return;
    }
    vector<pair<string, string>> formula;
    string line;
    while (getline(file, line))
    {
        string word[2];
        int count = 0;
        for (int i = 0; i < line.size(); i++)
        {
            if (line[i] == '-' && i + 1 < line.size() && line[i + 1] == '>')
            {
                count++;
                i++;
            }
            else
            {
                word[count] += line[i];
            }
        }
        formula.push_back(make_pair(word[0], word[1]));
    }
    _formula = formula;
}

void SyntaxAnalyzer::analyse(string str)
{
    int ip = 0;
    vector<string> state_stack;
    vector<string> stack;
    state_stack.push_back("I0");
    str.push_back('$');
    while (true)
    {
        int ipAdd = 0;
        string state = state_stack.back();
        string a;
        if (startWith(str.substr(ip), "num"))
        {
            a = "num";
            ipAdd = 3;
        }
        else
        {
            a = str[ip];
            ipAdd = 1;
        }
        if (_table.find(state) == _table.end())
        {
            cout << "Error: state " << state << " not found" << endl;
            return;
        }
        if (_table[state].find(a) == _table[state].end())
        {
            cout << "Error: Unexpected token " << a << " in state " << state << ", skip..." << endl;
            ip += ipAdd;
            continue;
            return;
        }
        string next_state = _table[state][a];
        if (startWith(next_state, "s") || startWith(next_state, "S"))
        {
            _printStack(stack, state_stack, str.substr(ip), "Shift " + next_state);
            stack.push_back(a);
            state_stack.push_back("I" + next_state.substr(1));
            ip += ipAdd;
        }
        else if (startWith(next_state, "r"))
        {
            int counti = 0;
            int r = stoi(next_state.substr(1));
            _printStack(stack, state_stack, str.substr(ip), "Reduce " + _formula[r - 1].first + " -> " + _formula[r - 1].second);
            for (int i = 0; i < _formula[r - 1].second.size(); i++)
            {
                if (_formula[r - 1].second[i] == 'm' && i > 1 && _formula[r - 1].second[i - 1] == 'u' && _formula[r - 1].second[i - 2] == 'n')
                {
                    counti -= 2;
                }
                counti++;
            }
            for (int i = 0; i < counti; i++)
            {
                stack.pop_back();
                state_stack.pop_back();
            }
            stack.push_back(_formula[r - 1].first);
            state_stack.push_back("I" + _table[state_stack.back()][_formula[r - 1].first]);
        }
        else if (next_state == string("acc"))
        {
            _printStack(stack, state_stack, str.substr(ip), "Accept");
            return;
        }
        else
        {
            cout << "Error: Unexpected state " << next_state << endl;
            return;
        }
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
    SyntaxAnalyzer analyzer;
    analyzer.loadTable("lr1.csv");
    analyzer.loadFormula("lr1.conf");
    cout << "Please input string:" << endl;
    string str;
    cin >> str;
    str = process(str);
    analyzer.analyse(str);
    system("pause");
    return 0;
}