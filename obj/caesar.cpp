/**
 * All imports.
 */
#include "caesar.h"

/**
 * Implementation of the Caesar cipher.
 *
 * The Caesar cipher is an algorithm that uses permutation,
 * order, and patterns to encrypt/decrypt text.
 */
Caesar::Caesar(string ptext, int key)
{
    this->ptext = ptext;
    this->key = key;
}

/**
 * Gets the plaintext.
 *
 * @return ptext A string representing the plaintext.
 */
string Caesar::getPlaintext()
{
    return this->ptext;
}

/**
 * Sets the plaintext.
 *
 * @param ptext A string representing the plantext.
 */
void Caesar::setPlaintext(string ptext)
{
    this->ptext = ptext;
}

/**
 * Gets the cipher keys.
 *
 * @return keys A string vector describing the cipher keys.
 */
int Caesar::getKey()
{
    return this->key;
}

/**
 * Sets the cipher keys.
 *
 * @param keys A string vector describing the cipher keys.
 */
void Caesar::setKey(int key)
{
    this->key = key;
}

/**
 * Gets the cipher table.
 *
 * @return table A vector of string vectors describing the cipher table.
 */
vector<vector<string>> Caesar::getTable()
{
    return this->table;
}

/**
 * Sets the cipher table.
 *
 * @param table A vector of string vectors describing the cipher table.
 */
void Caesar::setTable(vector<vector<string>>& table)
{
    this->table = table;
}

/**
 * Adds a row to the table.
 *
 * @param row A string vector.
 */
void Caesar::addRow(vector<string>& row)
{
    table.push_back(row);
}

/**
 * Gets the ciphertext.
 *
 * @return ctext A string representing the ciphertext.
 */
string Caesar::getCiphertext()
{
    return this->ctext;
}

/**
 * Sets the ciphertext.
 *
 * @param ctext A string representing the ciphertext.
 */
void Caesar::setCiphertext(string ctext)
{
    this->ctext = ctext;
}

void Caesar::throw_exec(string type)
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
    else if (type == "shift")
    {
        qDebug() << "Error shifting table row.\n";
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
 * Initializes a row.
 *
 * @param row A string vector with plaintext.
 */
void Caesar::rowInit(vector<string>& row)
{
    int len = this->getTable()[0].size();

    for (int i=1; i <= len; i++)
    {
        row.push_back("-");
    }
}

/**
 * Shows the cipher table.
 *
 * @return null
 */
void Caesar::showTable()
{
    for (const auto& row : this->getTable()){
        for (const auto& el : row){
            cout << el << " " ;
        }
        cout << endl;
    }
}

/**
 * Shifts cipher table rows based on the keys.
 *
 * @return null
 */
void Caesar::makeShifts()
{
    try
    {
        vector<string> crow;
        int shift = 0;
        int len = this->getTable()[0].size();

        shift = this->getKey();
        this->rowInit(crow);

        for (int i=0; i < len; i++)
        {
            int j = i + shift;

            if (j >= len)
            {
                for (int c=1; c <= shift; c++)
                {
                    crow[len - c] = this->getTable()[0][shift - c];
                }
                this->addRow(crow);
                break;
            }
            else
            {
                crow[i] = this->getTable()[0][j];
            }
        }
    }
    catch (const exception &e)
    {
        this->throw_exec("shift");
    }
}

/**
 * Initializes the cipher table.
 *
 * @return null
 */
void Caesar::tableInit()
{
    try
    {
        vector<string> chars = {
            "a","b","c","d","e","f","g","h","i","j","k",
            "l","m","n","o","p","q","r","s","t","u","v",
            "w","x","y","z"
        };
        vector<string> order = {
            "1","2","3","4","5","6","7","8","9","10","11",
            "12","13","14","15","16","17","18","19","20",
            "21","22","23","24","25","26"
        };

        this->addRow(chars);
        this->addRow(order);
    }
    catch (const exception &e)
    {
        this->throw_exec("init");
    }
}

/**
 * Decrypts the ciphertext using the pattern.
 *
 * @return null
 */
void Caesar::decrypt()
{
    try
    {
        int len = this->getPlaintext().size();
        int j = 1;
        string temp = "";

        for (int i = 0; i < len; i ++)
        {
            string c = "";
            c = c + this->getPlaintext()[i];

            if (!isalnum(this->getPlaintext()[i]))
            {
                temp = temp + c;
            }
            else
            {

                int p = 0;
                for (int z = 0; z < this->getTable()[2].size(); z ++)
                {
                    string y = "";
                    y = y + this->getTable()[2][z];

                    if ( y == c )
                    {
                        p = z;
                    }
                }

                temp = temp + this->getTable()[0][p];
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
 * Encrypts the plaintext using the pattern.
 *
 * @return null
 */
void Caesar::encrypt()
{
    try
    {
        int len = this->getPlaintext().size();
        int j = 1;
        string temp = "";

        for (int i = 0; i < len; i ++)
        {
            string c = "";
            c = c + this->getPlaintext()[i];

            if (!isalnum(this->getPlaintext()[i]))
            {
                temp = temp + c;
            }
            else
            {

                int p = 0;
                for (int z = 0; z < this->getTable()[0].size(); z ++)
                {

                    string y = "";
                    y = y + this->getTable()[0][z];

                    if ( y == c )
                    {
                        p = z;
                    }

                }

                temp = temp + this->getTable()[2][p];
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
 * Stages the cipher table.
 *
 * @return null
 */
void Caesar::stage()
{
    try
    {
        this->tableInit();
        this->makeShifts();
        //this->showTable();
    }
    catch (const exception &e)
    {
        this->throw_exec("stage");
    }
}

/**
 * Evaluates the cipher key and the plaintext.
 *
 * @return null
 */
void Caesar::eval()
{
    try
    {
        string temp;
        temp = this->getPlaintext();
        transform(temp.begin(), temp.end(), temp.begin(), ::tolower);
        this->setPlaintext(temp);

        this->setKey(this->getKey() % 26);
    }
    catch (const exception &e)
    {
        this->throw_exec("eval");
    }
}
