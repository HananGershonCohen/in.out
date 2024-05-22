#include <iostream>
#include <fstream>
#include <cstdlib> // use with exit();
#include <string>

using namespace std;

struct Files
{
    ifstream key;
    ifstream txt;
    ofstream out;
    string key_name/* = "key1.txt"*/;
    string txt_name/* = "inp1.txt"*/;
    string out_name/* = "oup1.txt"*/;
};

void enter_name_file(Files& file)
{
   // cout << "please enter 3 name of files: \n";
    cin >> file.key_name;
    cin >> file.txt_name;
    cin >> file.out_name;
}

void open_file(ifstream& file, const string& filename)
{
    file.open(filename);
    if (!file)
    {
        cerr << "The file " << filename << " not opened.\n";
        exit(1);
    }
   // cout << "The file " << filename << " was opened successfully.\n";
}

void open_files(Files& file)
{
    open_file(file.key, file.key_name); // Changed file1 to key, and f1_name to key_name
    open_file(file.txt, file.txt_name); // Changed file2 to txt, and f2_name to txt_name
    file.out.open(file.out_name);
    if (!file.out)
    {
        cerr << "The file " << file.out_name << " not opened.\n";
        exit(1);
    }
   // cout << "The file " << file.out_name << " was opened successfully.\n";
}

void close_file(ifstream& file)
{
    file.close();
}

void close_files(Files& file)
{
    close_file(file.key);
    close_file(file.txt);
    file.out.close();
}

void count_row_in_file(Files& file, int& counter, string line)
{
    counter = 0;

    while (getline(file.key, line)) // Changed file1 to key
        counter++;

   // cout << "The number of lines is: " << counter << endl;

    file.key.clear(); // Changed file1 to key
    file.key.seekg(0, ios::beg); // Changed file1 to key
}

void create_arr(Files& file, int& counter, string line, string* arrKey)
{
    for (int i = 0; i < counter; i++)
    {
        getline(file.key, line); // Changed file1 to key
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

void  swap(Files& file, int counter, char ch, string* arrKey)
{
    for (int i = 0; i < counter; i++)
    {
        if (ch == arrKey[i][0])
        {
            file.out << arrKey[i][1];
            cout << arrKey[i][1];
            return;
        }
    }

    file.out << ch;
    cout << ch;
}

void swap_file_text(Files& file, string* arrKey, int counter)
{
    char ch;
    while (file.txt.get(ch))
    {
        swap(file, counter, ch, arrKey);
    }
}

int main()
{
    Files file;
    string* arrKey;
    int counter;

    enter_name_file(file);
    open_files(file);
    arrKey = create_arr_key(file, counter);
    swap_file_text(file, arrKey, counter);
    close_files(file);

    return 0;
}
