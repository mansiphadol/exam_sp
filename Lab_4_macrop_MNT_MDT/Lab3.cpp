#include <iostream>
#include <bits/stdc++.h>
#include "C:\Users\User\Documents\TY sem 2\sp\LAB\LAB\Lab5\Lab4\TextTable.h"

using namespace std;

class MOT
{
public:
    string mneumonic;
    int opcode, operands;

    MOT(string mneumonic, int opcode, int operands)
    {
        this->mneumonic = mneumonic;
        this->opcode = opcode;
        this->operands = operands;
    }
};

class mainp
{
public:
    int line;
    string label;
    string memorial;
    string operand;
    int location;
    string output;

    mainp(int line, string label, string memorial, string operand, int location, string output)
    {
        this->line = line;
        this->label = label;
        this->memorial = memorial;
        this->operand = operand;
        this->location = location;
        this->output = output;
    }
};

vector<MOT> mot;
map<string, int> pot;
vector<mainp> maintable;
map<string, int> sym_table;
int lineNumber = 1;
int location_count = 0;

void takePOT()
{
    ifstream file("POT.txt");
    string line;

    while (getline(file, line))
    {
        istringstream iss(line);
        string token;
        int value;

        while (getline(iss, token, '|'))
        {
            iss >> value;
        }

        pot[token] = value;
    }
}

void takeMOT()
{
    ifstream file("MOT.txt");
    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        string token;

        while (getline(iss, token, '|'))
        {
            string mneumonic, operand;
            int opcode;
            mneumonic = token;
            iss >> opcode;
            getline(iss, operand, '|');
            iss >> operand;

            mot.push_back(MOT(mneumonic, opcode, stoi(operand)));
        }
    }
}

void printMOT()
{
    TextTable t('-', '|', '+');
    t.add("Mnemonic");
    t.add("Opcode");
    t.add("Operand");
    t.endOfRow();

    for (const auto i : mot)
    {
        t.add(i.mneumonic);
        t.add(to_string(i.opcode));
        t.add(to_string(i.operands));
        t.endOfRow();
    }

    t.setAlignment(2, TextTable::Alignment::LEFT);
    cout << t;
}

void printPOT()
{
    TextTable t('-', '|', '+');
    t.add("Opcode");
    t.add("Operand");
    t.endOfRow();

    for (const auto i : pot)
    {
        t.add(i.first);
        t.add(to_string(i.second));
        t.endOfRow();
    }

    t.setAlignment(2, TextTable::Alignment::LEFT);
    cout << t;
}

void takeInput()
{
    ifstream file("input.txt");
    string line;
    int ct = 2;

    while (getline(file, line))
    {
        istringstream iss(line);
        string token;
        vector<string> temp;
        while (getline(iss, token, ' '))
        {
            temp.push_back(token);
        }
        if (temp.size() == 2)  // exactly 2 tokens in line
        {
            maintable.push_back(mainp(lineNumber, "", temp[0], temp[1], location_count, ""));  // addind tokens to maintable vector
            location_count += ct; // increments location count by 2 0 
        }
        else if (temp.size() == 3)
        {
            sym_table[temp[0]] = location_count;
            maintable.push_back(mainp(lineNumber, temp[0], temp[1], temp[2], location_count, ""));
            location_count += ct;
        }
        else if (temp[0] == "stop")
        {
            maintable.push_back(mainp(lineNumber, "", temp[0], "", location_count, ""));
            ct = 1;
            location_count += ct;
        }

        lineNumber++;
    }
}

void printMainTable()
{
    TextTable t('-', '|', '+');
    t.add("line");
    t.add("label");
    t.add("memorial");
    t.add("operand");
    t.add("location");
    t.add("Output");
    t.endOfRow();

    for (const auto i : maintable)
    {
        t.add((to_string(i.line)));
        t.add(i.label);
        t.add(i.memorial);
        t.add(i.operand);
        t.add(to_string(i.location));
        t.add(i.output);
        t.endOfRow();
    }

    t.setAlignment(2, TextTable::Alignment::LEFT);
    cout << t;
}

void printMap()
{
    for (const auto i : sym_table)
    {
        cout << i.first << ":" << i.second << endl;
    }
}

int getOpcode(string operand)
{
    for (const auto i : mot)
    {
        if (i.mneumonic == operand)
        {
            return i.opcode;
        }
    }

    return -1;
}

void secondPass()
{
    for (auto &i : maintable)
    {
        string memorial = i.memorial;
        string operand = i.operand;
        int opcode = getOpcode(memorial);
        int location = sym_table[operand];

        i.output = to_string(opcode) + " " + to_string(location);
    }
}

int main()
{
    takeMOT();
    takePOT();

    cout << "POT is: " << endl;
    printPOT();
    cout << "MOT is: " << endl;
    printMOT();

    takeInput();
    cout<<"1st pass"<<endl;
    printMainTable();
    cout<<"1st pass"<<endl;
    printMap();
    secondPass();
    printMainTable();

    return 0;
}
