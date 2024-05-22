#include <bits/stdc++.h>
using namespace std;

// Function to leading and trailing whitespaces
inline void trim(std::string &s) {
    s.erase(0, s.find_first_not_of(" "));
    s.erase(s.find_last_not_of(" ") + 1);
}

struct macroname
{
    int index;
    string name;
    int mdtIndex;
    macroname(int index,string name,int mdtIndex) {
        this->index = index;
        this->name = name;
        this->mdtIndex = mdtIndex;
    }
};

struct macrodef
{
    int index;
    string line;
    macrodef(int index, string line) {
        this->index = index;
        this->line = line;
    }
};

int mdtIndex = 100;
int mntIndex = 10;

void pass1(ifstream &fin, vector<macroname> &mnt, vector<macrodef> &mdt)
{
    string line;
    while (getline(fin, line))
    {
        if (line.empty())
            continue;

        if (line.find("macro") != -1)

        {
            // macro found
            trim(line);
            line.erase(line.begin(), line.begin() + 6); // removes macro keyword from the line
            // To Push in MacroName Table
            macroname mstruct = macroname(mntIndex++,line,mdtIndex);
            mnt.push_back(mstruct);

            do
            {
                //To Push in Macro Definition Table
                getline(fin, line);
                trim(line);
                if (line.empty())
                    continue;
                macrodef mdef = macrodef(mdtIndex++,line);
                mdt.push_back(mdef);

            } while (line.find("mend") == -1);
        }
    }
}

int main()
{
    string inputfile = "input.txt";
    ifstream fin;
    fin.open(inputfile);

    vector<macroname> mnt;
    vector<macrodef> mdt;

    if (fin.is_open())
    {
        pass1(fin, mnt, mdt);
    }
    cout << "Index\tMacro\tMDTIndex\n";
    for (auto i : mnt)
    {
        cout << i.index << "\t" << i.name << "\t" << i.mdtIndex << "\n";
    }
    cout << "\nIndex\tCode\n";
    for (auto j : mdt)
    {
        cout << j.index << "\t" << j.line << "\n";
    }
    cout << endl;

    fin.close();
    return 0;
}
