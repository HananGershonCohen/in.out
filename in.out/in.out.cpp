#include <iostream>
#include <fstream>
#include <cstdlib> // use with exit();
#include <string>


using namespace std;

struct Files
{
    ifstream txt1;
    ifstream txt2;
    ofstream out;
    string name_txt1 = "ex10c_inp1.txt";
    string name_txt2 = "ex10c_inp2.txt";
    string name_out = "ex10_oup.txt";
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
    open_file(file.txt1, file.name_txt1); // Changed file1 to key, and f1_name to key_name
    open_file(file.txt2, file.name_txt2); // Changed file2 to txt, and f2_name to txt_name
    file.out.open(file.name_out);
    if (!file.out)
    {
        cerr << "The file " << file.name_out << " not opened.\n";
        exit(1);
    }
     cout << "The file " << file.name_out << " was opened successfully.\n";
}
void close_files(Files& file)
{
    file.txt1.close();
    file.txt2.close();
    file.out.close();
}

void print_line(Files& file, bool exist,string &str1)
{
    if (!exist)
    {
        cout << str1;
        getline(file.txt1, str1);
        cout << str1;
    }
    else
        getline(file.txt1, str1);
}



void merger(Files& file, string str1, string str2)
{
    cout << str1; // dana
    file.txt1 >> str1;
    file.txt2 >> str2;
    while (file.txt1.peek() != '\n' && file.txt1.peek() != EOF && file.txt2.peek() != '\n' && file.txt2.peek() != EOF)
    {
        

        if (str1 > str2)
        {
            cout << str1;
            file.txt1 >> str1;
        }
        else
        {
            cout << str2;
            file.txt2 >> str2;
        }
    }
    while (file.txt1.peek() != '\n' && file.txt1.peek() != EOF)
    {
        cout << str1;
        file.txt1 >> str1;
    }
    while (file.txt2.peek() != '\n' && file.txt2.peek() != EOF)
    {
        cout << str2;
        file.txt2 >> str2;
    }
}

void check_string(Files &file, string str1, string  str2, bool &exist)
{
    while (file.txt2 >> str2)
    {
        if (str1 == str2)
        {
            exist = true;
            merger(file,str1, str2);
            return;
        }
    }
}

void comparing_files(Files& file)
{
    string str1, str2;
    while (file.txt1 >> str1)
    {
        bool exist = false;
        check_string(file, str1, str2, exist);

        file.txt2.clear(); // Clear any potential EOF flags
        file.txt2.seekg(0, ios::beg);

        // move to the next line
        print_line(file, exist, str1);
     
      
    }
}

int main()
{
    Files file;
    
    open_files(file);
    comparing_files(file);
    close_files(file);
 
    return 0;
}
