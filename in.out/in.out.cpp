#include <iostream>
#include <fstream>
#include <cstdlib> // use whith exit();
#include <string>
using namespace std;

void open_file(string file_name, ifstream& file)
{
    file_name = "key1.txt";
    cout << "file_name = key1.txt \n";
    file.open(file_name);
    if (!file)
    {
        cerr << "The file not opened. \n";
        exit(0);
    }
    cout << "The file was opened successfully\n";
}

void count_row_in_file(ifstream& file,int& counter, string line)
{
    counter = 0;

    while (getline(file, line))
        counter++;

    cout << "The number of lines is: " << counter << endl;

    file.clear();
    file.seekg(0, ios::beg); // Move to the beginning of the file
}

void create_arr(ifstream& file, int& counter, string line, string* arrKey)
{
    for (int i = 0; i < counter; i++)
    {
        getline(file, line);
        arrKey[i] = line;
        cout << arrKey[i] << endl;
    }
}

string* create_arr_key(ifstream& file,int& counter)
{
    string line;
    count_row_in_file(file, counter, line);
    string* arrKey = new string[counter];
    create_arr(file, counter, line, arrKey);
    return arrKey;
}



int main()
{
    ifstream file;
    string file_name;
    string* arrKey;
    int counter;


    open_file(file_name, file);
    arrKey = create_arr_key(file,counter);


    return 0;
}
