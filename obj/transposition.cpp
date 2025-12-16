/**
 * All imports.
 */
#include "transposition.h"
#include <QDebug>

/**
 * Implementation of a Transposition Transposition.
 *
 * This Transposition Transposition is an algorithm that uses
 * permutation and order to encrypt/decrypt text.
 *
 */
Transposition::Transposition(string key, string ptext)
{
    this->key = key;
    this->ptext = ptext;
}

Transposition::~Transposition()
{
    ;
}

/**
 * Gets the Transposition key.
 *
 * @return key A string representing the Transposition key.
 */
string Transposition::getKey(){
    return this->key;
}

/**
 * Sets the Transposition key.
 *
 * @param key A string representing the Transposition key.
 */
void Transposition::setKey(string key){
    this->key = key;
}

/**
 * Gets the plaintext.
 *
 * @return ptext A string representing the plaintext.
 */
string Transposition::getPlaintext(){
    return this->ptext;
}

/**
 * Sets the plaintext.
 *
 * @param ptext A string representing the plaintext.
 */
void Transposition::setPlaintext(string ptext){
    this->ptext = ptext;
}

/**
 * Gets the Transpositiontext.
 *
 * @return ctext A string representing the Transpositiontext.
 */
string Transposition::getCiphertext(){
    return this->ctext;
}

/**
 * Sets the Transpositiontext.
 *
 * @param ctext A string representing the Transpositiontext.
 */
void Transposition::setCiphertext(string ctext){
    this->ctext = ctext;
}

/**
 * Gets the Transposition table.
 *
 * @return table A vector of string vectors describing the Transposition table.
 */
vector<vector<string>> Transposition::getTable(){
    return this->table;
}

/**
 * Sets the Transposition table.
 *
 * @param table A vector of string vectors with plaintext.
 */
void Transposition::setTable(vector<vector<string>>& table){
    this->table = table;
}

/**
 * Gets the number of rows.
 *
 * @return rows The number of expected rows.
 */
int Transposition::getRows(){
    return this->rows;
}

/**
 * Sets the number of rows.
 *
 * @param rows The number of expected rows.
 */
void Transposition::setRows(int rows){
    this->rows = rows;
}

/**
 * Initializes a row.
 *
 * @param len An integer describing the length of the table.
 * @param row A string vector with plaintext.
 */
void Transposition::rowInit(int len, vector<string>& row){
    int i = 0;
    for (i; i < len; i ++){
        row.push_back("-");
    }
}

/**
 * Shows the Transposition table.
 *
 * @return null
 */
void Transposition::showTable(){

    cout << endl;
    for (const auto& row : this->getTable()){
        for (const auto& el : row){
            qDebug() << el << " " ;
        }
        qDebug() << "\n";
    }
    qDebug() << "\n";
}

/**
 * Shows a specified row.
 *
 * @param row A string vector with plaintext.
 */
void Transposition::showRow(vector<string>& row){

    for (const auto& el : row){
        cout << el << " ";
    }
    cout << endl;
}

/**
 * Puts the key into the table.
 *
 * @return null
 */
void Transposition::addKey(){

    vector<string> row;

    for(const auto& element : this->getKey()){
        string el (1, element);
        row.push_back(el);
    }

    this->addRow(row);
}

void Transposition::throw_exec(string type)
{
    if (type == "eval")
    {
        qDebug() << "Error evaluating cipher input.\n";
    }
    else if (type == "stage")
    {
        qDebug() << "Error staging cipher table.\n";
    }
    else if (type == "init")
    {
        qDebug() << "Error initializing table rows.\n";
    }
    else if (type == "trans")
    {
        qDebug() << "Error transposing table.\n";
    }
    else if (type == "order")
    {
        qDebug() << "Error ordering table elements.\n";
    }
    else if (type == "block")
    {
        qDebug() << "Error formatting output.\n";
    }
    else if (type == "pt")
    {
        qDebug() << "Error adding plaintext to table.\n";
    }
    else if (type == "encrypt")
    {
        qDebug() << "Error encrypting plaintext.\n";
    }
    else if (type == "decrypt")
    {
        qDebug() << "Error decrypting ciphertext.\n";
    }
}

/**
 * Puts the plaintext into the table.
 *
 * @return null
 */
void Transposition::addPlaintext()
{
    try
    {
        int i = 0;
        int id = 0;
        vector<string> row;
        string temp = this->getPlaintext();
        int len = this->getKey().length();

        for (const auto& element : temp){
            string el(1, element);
            if (i == (len - 1)){
                if (el == " "){
                    row.push_back("*");
                }
                else
                {
                    row.push_back(el);
                }
                this->addRow(row);
                row.clear();
                i = 0;
            }
            else{
                row.push_back(el);
                i = i + 1;
            }
            id = id + 1;
        }

        if (row.size() == len){
            this->addRow(row);
        }
        if (id != temp.length() || row.size() > 0){
            while (row.size() < this->getKey().length()){
                row.push_back(" ");
            }
            this->addRow(row);
        }
    }
    catch (const exception &e)
    {
        this->throw_exec("pt");
    }
}

/**
 * Adds a row to the table.
 *
 * @param row A string vector.
 */
void Transposition::addRow(vector <string>& row){
    table.push_back(row);
}

/**
 * Finds the order of characters in the key.
 *
 * @return null
 */
void Transposition::order()
{
    try
    {
        vector<string> row;
        string temp1 = this->getKey();
        string temp2 = this->getKey();
        int len = this->getKey().length();
        int col = 0;
        int i = 0;
        int index = 0;
        int id = 1;

        sort(temp1.begin(), temp1.end());
        this->rowInit(len, row);

        for (col; col < len; col++){
            for (i; i < len; i++){
                if (temp1[col] == temp2[i]){
                    temp2[i] = '-';
                    row[i] = to_string(id);
                    id = id + 1;
                    break;
                }
            }
            i = 0;
        }
        this->addRow(row);
    }
    catch (const exception &e)
    {
        this->throw_exec("order");
    }
}

/**
 * Decrypts the Transpositiontext using the key.
 *
 * @return null
 */
void Transposition::decrypt()
{
    try
    {
        int id = 1;
        int col = 0;
        int len = this->getKey().length();
        int depth = this->getTable().size();
        vector<vector<string>> temptable = this->getTable();
        string temp = "";

        while (col < len)
        {
            if (this->getTable()[1][col] == to_string(id))
            {
                for (int row = 2; row < depth; row++)
                {
                    temptable[row][col] = this->getTable()[id+1][row-2];
                }
                col = 0;
                id = id + 1;
            }
            else
            {
                col = col + 1;
            }
        }
        qDebug() << temptable;

        for (int x = 2; x < depth; x++)
        {
            for (int y = 0; y < len; y++)
            {
                temp.append(temptable[x][y]);
            }
        }

        this->setCiphertext(temp);
    }
    catch (const exception &e)
    {
        this->throw_exec("decrypt");
    }
}

/**
 * Encrypts the plaintext using the key.
 *
 * @return null
 */
void Transposition::encrypt()
{
    try
    {
        int id = 1;
        int col = 0;
        int row = 2;
        int len = this->getKey().length();
        int depth = this->getTable().size();
        string temp = "";

        while (col < len){
            if (this->getTable()[1][col] == to_string(id))
            {
                for (row; row < depth; row++)
                {
                    temp.append(this->getTable()[row][col]);
                }
                row = 2;
                col = 0;
                id = id + 1;
            }
            else
            {
                col = col + 1;
            }
        }

        this->setCiphertext(temp);
    }
    catch (const exception &e)
    {
        this->throw_exec("encrypt");
    }
}

/**
 * Stages the Transposition table.
 *
 * @return null
 */
void Transposition::stage()
{
    try
    {
        this->addKey();
        this->order();
        this->addPlaintext();
        qDebug() << this->getTable();
        //this->showTable();
    }
    catch (const exception &e)
    {
        this->throw_exec("stage");
    }
}

/**
 * Evaluates the Transposition key and plaintext.
 *
 * @return null
 */
void Transposition::eval()
{
    try
    {
        string temp;
        temp = this->getPlaintext();
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        this->setPlaintext(temp);

        string temp2;
        temp2 = this->getKey();
        transform(temp2.begin(), temp2.end(), temp2.begin(), ::tolower);
        this->setKey(temp2);

    }
    catch (const exception &e)
    {
        this->throw_exec("eval");
    }
}
