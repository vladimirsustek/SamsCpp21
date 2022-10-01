#include <iostream>
#include <fstream>

using namespace std;

/** IOSTREAM, FSTREAM (FILE OPERATION) CHAPTER 17 */

int main(void)
{

    ifstream fin("theFile.vhdl");

    if(!fin.good()) /** Equal to !fin) */
    {
        cout << "theFile.vhdl does not exist" << endl;
    }
    else
    {
        cout << "theFile.vhdl exists " << endl;
    }

    int howManyTimesOpened = 0;

    fin >> howManyTimesOpened;

    cout << "The file was opened already: " << howManyTimesOpened << " times" << endl;

    howManyTimesOpened++;

    fin.close();

    /**
        ios::app—Appends to the end of existing files rather than truncating them.
        ios::ate—Places you at the end of the file, but you can write data anywhere in the file.
        ios::trunc—Causes existing files to be truncated; the default.
        ios::nocreate—If the file does not exist, the open fails.
        ios::noreplace—If the file does already exist, the open fails.
    **/
    ofstream fout("theFile.vhdl", ios::ate);

    fout <<howManyTimesOpened;
    fout.close();
    return 0;
}
