#include <iostream>
#include <bits/stdc++.h>
#include "C:\Users\User\Documents\TY sem 2\sp\LAB\LAB\Lab5\Lab2\withArguments\TextTable.h"

using namespace std;

class MNT
{
public:
    int index;
    string m_name;
    int MDT_index;

    MNT(int index, string m_name, int MDT_index)
    {
        this->index = index;
        this->m_name = m_name;
        this->MDT_index = MDT_index;
    }
};

class MDT
{
public:
    int index;
    string card;

    MDT(int index, string card)
    {
        this->index = index;
        this->card = card;
    }
};

class ALA
{
public:
    string m_name;
    string formal_param;
    string positional_param;

    ALA(string m_name, string formal_param, string positional_param)
    {
        this->m_name = m_name;
        this->formal_param = formal_param;
        this->positional_param = positional_param;
    }
};

class AP
{
public:
    string macro_name;
    int actual_parameter;
    string positional_parameter;

    AP(string macro_name, int actual_parameter, string positional_parameter)
    {
        this->macro_name = macro_name;
        this->actual_parameter = actual_parameter;
        this->positional_parameter = positional_parameter;
    }
};

vector<MNT> mnt;
vector<MDT> mdt;
vector<ALA> ala;
vector<AP> ap;

int mntCount = 1;
int mdtCount = 20;

void printMDTTable()
{
    TextTable t('-', '|', '+');
    t.add("Index");
    t.add("Card");
    t.endOfRow();

    for (const auto &pair : mdt)
    {

        t.add(to_string(pair.index));
        t.add(pair.card);
        t.endOfRow();
    }
    t.setAlignment(2, TextTable::Alignment::LEFT);
    std::cout << t;
}

void printALATable()
{
    TextTable t('-', '|', '+');
    t.add("Macro Name");
    t.add("Formal Parameter");
    t.add("Positional Parameter");
    t.endOfRow();

    for (const auto &pair : ala)
    {

        t.add(pair.m_name);
        t.add(pair.formal_param);
        t.add(pair.positional_param);
        t.endOfRow();
    }
    t.setAlignment(2, TextTable::Alignment::LEFT);
    std::cout << t;
}

void printMNTTable()
{
    TextTable t('-', '|', '+');
    t.add("Index");
    t.add("Card");
    t.add("MDT Index");
    t.endOfRow();

    for (const auto &pair : mnt)
    {

        t.add(to_string(pair.index));
        t.add(pair.m_name);
        t.add(to_string(pair.MDT_index));
        t.endOfRow();
    }
    t.setAlignment(2, TextTable::Alignment::LEFT);
    std::cout << t;
}

void printAPTable()
{
    TextTable t('-', '|', '+');
    t.add("Macro Name");
    t.add("Actual");
    t.add("Positional");
    t.endOfRow();

    for (const auto &pair : ap)
    {

        t.add(pair.macro_name);
        t.add(to_string(pair.actual_parameter));
        t.add(pair.positional_parameter);
        t.endOfRow();
    }
    t.setAlignment(2, TextTable::Alignment::LEFT);
    std::cout << t;
}

bool isSubstringPresent(const string &mainString, const string &substring)
{
    // Find returns string::npos if the substring is not found
    return mainString.find(substring) != string::npos;
}

string getPositionalParam(string macro_name, string parameter)
{
    for (const auto &pair : ala)
    {
        if (pair.m_name == macro_name && pair.formal_param == parameter)
        {
            return pair.positional_param;
        }
    }

    return "not found";
}

pair<string, int> isValuePresent(const vector<MNT> &myMap, const string &valueToFind)
{
    pair<string, int> ans;
    // string macro_name = "";
    for (const auto &pair : myMap)
    {

        if (pair.m_name == valueToFind)
        {
            ans = make_pair(pair.m_name, pair.MDT_index);
            break;
        }
    }
    return ans;
}

void takeInput(string &filename)
{
    ifstream file(filename);
    string line;
    string macro_name;
    while (getline(file, line))
    {
        istringstream iss(line);
        string token;
        while (getline(iss, token))
        {
            if (isSubstringPresent(token, "MACRO"))
            {
                istringstream mnamestream(token);
                string temp;

                while (mnamestream >> temp)
                {
                    if (temp != "MACRO")
                    {
                        macro_name = temp;
                        mnt.push_back(MNT(mntCount++, macro_name, mdtCount));
                        int count = 1;
                        while (mnamestream >> temp)
                        {
                            ala.push_back(ALA(macro_name, temp, "#" + to_string(count++)));
                        }
                        break;
                    }
                }
            }
            else
            {
                string nextWord;
                istringstream mdtiss(token);
                string combine;

                mdtiss >> nextWord;
                string parameter;
                mdtiss >> parameter;

                string positional_param = getPositionalParam(macro_name, parameter);

                if (positional_param != "not found")
                {
                    mdt.push_back(MDT(mdtCount++, nextWord + " " + positional_param));
                }
                else
                {
                    mdt.push_back(MDT(mdtCount++, nextWord + " " + parameter));
                }
            }
        }
    }
}

int getActualValue(string macro_name, string argument)
{
    int ans = 0;
    for (const auto i : ap)
    {
        if (i.macro_name == macro_name && i.positional_parameter == argument)
        {
            ans = i.actual_parameter;
            break;
        }
    }

    return ans;
}

void createAP()
{
    ofstream outfile("output.txt");
    ifstream file("code.txt");
    string line;

    while (getline(file, line))
    {
        istringstream iss(line);
        string token;
        iss >> token;
        pair<string, int> macro_name = isValuePresent(mnt, token);
        int count = 1;
        int val = macro_name.second;

        if (val != 0)
        {
            while (iss >> token)
            {
                ap.push_back(AP(macro_name.first, stoi(token), "#" + to_string(count++)));
            }

            string card;
            for (const auto &pair : mdt)
            {
                if (pair.index == val && !isSubstringPresent(pair.card, "mend"))
                {
                    // Extract instruction and argument from the MDT card
                    istringstream cardIss(pair.card);
                    string instruction, argument;
                    cardIss >> instruction >> argument;

                    int actual_value = getActualValue(macro_name.first, argument);
                    if (actual_value != 0)
                    {
                        outfile << instruction << " " << actual_value << "\n";
                    }
                    else
                    {
                        outfile << instruction << " " << argument << "\n";
                    }
                    val++;
                }
            }
        }
        else
        {
            // write line to file
            outfile << line << "\n";
        }
    }
}

int main()
{
    string filename = "./input.txt";
    takeInput(filename);

    cout << "----------- MNT table is ----------- " << endl;
    printMNTTable();

    cout << "----------- ALA table is ----------- " << endl;
    printALATable();

    cout << "----------- MDT table is ----------- " << endl;
    printMDTTable();

    createAP();

    cout << "----------- Actual vs Positional table is ----------- " << endl;
    printAPTable();
}
