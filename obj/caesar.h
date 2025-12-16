#ifndef CAESAR_H
#define CAESAR_H

#include <string>
#include <vector>
#include <cctype>
#include <bits/stdc++.h>

#include <QDebug>

using namespace std;

class Caesar{

public:
    Caesar(string ptext, int key);

    string getPlaintext();
    void setPlaintext(string ptext);
    int getKey();
    void setKey(int key);
    string getCiphertext();
    void setCiphertext(string ctext);
    vector<vector<string>> getTable();
    void setTable(vector<vector<string>>& table);

    void throw_exec(string type);
    void tableInit();
    void rowInit(vector<string>& row);
    void addRow(vector<string>& row);
    void showTable();
    void makeShifts();

    void decrypt();
    void encrypt();
    void stage();
    void eval();

private:
    string ptext = "";
    int key = 0;
    vector<vector <string>> table;
    string ctext = "";
};

#endif
