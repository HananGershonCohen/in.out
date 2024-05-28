#include <iostream>
#include <fstream>
#include <cstdlib> // use with exit();
#include <string>
#include <sstream> // for stringstream



using namespace std;

struct Files
{
    ifstream txt1;
    ifstream txt2;
    ofstream out;
    string name_txt1 =/* "ex10c_inp1.txt";*/ "new1.txt";
    string name_txt2 = /*"ex10c_inp2.txt"; */ "new2.txt";
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


void comparing_files(Files& file)
{
    string line1, line2, str1, str2;
    bool exist;
    while (getline(file.txt1, line1)) // Read the first line from the first file
    {
        exist = false;
        // cout << line1 << endl;
         // כעת אני רוצה לבדוק אם קיים בקובץ השני שם  כזה
         // Use stringstream to extract the first word
        stringstream ss1(line1);
        ss1 >> str1;
        while (getline(file.txt2, line2))
        {
            stringstream ss2(line2);
            ss2 >> str2;

            // אם נמצאה שורה שווה אז נדפיס את כל השורה שבקובץ הראשון ואת הציונים בלבד שבקובץ השני
            if (str1 == str2)
            {
                exist = true;
                cout << line1;
                while (ss2 >> str2)
                {
                    cout << ' ' << str2;
                }
                cout << endl;
            }

        }
        if (!exist)
            cout << line1 << endl;
        file.txt2.clear(); // Clear any potential EOF flags
        file.txt2.seekg(0, ios::beg);
    }

    // עכשיו החלק ההפוך של הפונקציה 
    file.txt1.clear(); // Clear any potential EOF flags
    file.txt1.seekg(0, ios::beg);

    while (getline(file.txt2, line2))
    {
        stringstream ss2(line2);
        ss2 >> str2;
        exist = false;
        while (getline(file.txt1, line1))
        {
            stringstream ss1(line1);
            ss1 >> str1;
            if (str1 == str2)
            {
                exist = true;
            }
        }
        if (!exist)
            cout << line2 << endl;
        file.txt1.clear(); // Clear any potential EOF flags
        file.txt1.seekg(0, ios::beg);
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
