#include <iostream>
#include <fstream>
#include <cstdlib> // use whith exit();
#include <string>

using namespace std;

struct Files
{
    ifstream file1;
    ifstream file2;
    string f1_name = "key1.txt";
    string f2_name = "inp1.txt";
};

void open_file(ifstream& file, const string& filename)
{
    file.open(filename);
    if (!file)
    {
        cerr << "The file " << filename << " not opened.\n";
        exit(1);
    }
    cout << "The file " << filename << " was opened successfully.\n";
}

void open_files(Files& file)
{
    open_file(file.file1, file.f1_name);
    open_file(file.file2, file.f2_name);
}

void count_row_in_file(Files& file, int& counter, string line)
{
    counter = 0;

    while (getline(file.file1, line))
        counter++;

    cout << "The number of lines is: " << counter << endl;

    file.file1.clear();
    file.file1.seekg(0, ios::beg); // Move to the beginning of the file
}

void create_arr(Files& file, int& counter, string line, string* arrKey)
{
    for (int i = 0; i < counter; i++)
    {
        getline(file.file1, line);
        arrKey[i] = line;
    }
}

string* create_arr_key(Files& file, int& counter)
{
    string line;
    count_row_in_file(file, counter, line);
    string* arrKey = new string[counter];
    create_arr(file, counter, line, arrKey);
    return arrKey;
}



int main()
{
    Files file;
    string* arrKey;
    int counter;


    open_files(file);
    arrKey = create_arr_key(file, counter);

    //    for (int i = 0; i < counter; i++)
    //{
    //    cout << arrKey[i] << endl;
    //}

    return 0;
}
