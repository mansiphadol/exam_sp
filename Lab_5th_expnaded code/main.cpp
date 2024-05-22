//expanded code

#include <bits/stdc++.h>
using namespace std;

// Function to Trim whitespaces
inline void trim(std::string &s)
{
    s.erase(0, s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
}

struct macroname
{
    int index;
    string name;
    int mdtIndex;
    macroname(int index, string name, int mdtIndex)
    {
        this->index = index;
        this->name = name;
        this->mdtIndex = mdtIndex;
    }
};

struct macrodef
{
    int index;
    string line;
    macrodef(int index, string line)
    {
        this->index = index;
        this->line = line;
    }
};

void init(vector<macroname> &mnt, vector<macrodef> &mdt)
//This function initializes the Macro Name Table (MNT) and the Macro Definition Table (MDT) with some predefined macro names and their definitions.
{
    mnt.push_back(macroname(1, "ABC", 100));
    mdt.push_back(macrodef(100, "add a"));
    mdt.push_back(macrodef(101, "sub b"));
    mdt.push_back(macrodef(102, "mend"));

    mnt.push_back(macroname(2, "PQR", 103));
    mdt.push_back(macrodef(103, "add b"));
    mdt.push_back(macrodef(104, "sub a"));
    mdt.push_back(macrodef(105, "mend"));
}
int mntfind(vector<macroname> &mnt, string name) //searches for macro-name in mnt if found returns index else returns -1
{
    for (int i = 0; i < mnt.size(); i++)
    {
        if (mnt[i].name == name)
        {
            return i;
        }
    }
    return -1;
}

// Function to find the index of the macrodef in the mdt (MDT)
int mdtFind(vector<macrodef> &mdt, int index)
{
    for (int i = 0; i < mdt.size(); i++)
    {
        if (mdt[i].index == index)
        {
            return i;
        }
    }
    return -1;
}

void pass2(ifstream &fin, ofstream &fout, vector<macroname> &mnt, vector<macrodef> &mdt)
//expands macro calls in the input file and writes the expanded code to the output file.
{
    string line;
    while (getline(fin, line))
    {
        trim(line);
        int index = mntfind(mnt, line);

        if (index == -1)
        {
            fout << line << "\n";
            continue;

        }
        int mdt_loc = mdtFind(mdt, mnt[index].mdtIndex);
        if (mdt_loc == -1) exit(2);
        while (mdt[mdt_loc].line != "mend")
        {
            fout << mdt[mdt_loc].line << "\n"; // if macro name found directly write to output file
            mdt_loc++;
        }
        fout << flush;
    }
}
int main()
{
    string inputfile = "input.txt";
    ifstream fin;
    ofstream fout;
    fin.open(inputfile);
    fout.open("output.txt");

    vector<macroname> mnt;
    vector<macrodef> mdt;

    init(mnt, mdt);
    pass2(fin, fout, mnt, mdt);

    fin.close();
    fout.close();
    return 0;
}
