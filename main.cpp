#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// functions for login management
void EnterInformationFile();
void IsValidCredential(string username, string password);



int main()
{
    EnterInformationFile();
    return 0;
}



void EnterInformationFile()
{
    // create object userPassFile in fstream class
    fstream userFile ("/Users/ianblankenship/data-managing/userPassFile.txt", ios::app);

    // exit if the file does not exist/cannot be opened
    if (!userFile)
    {
        cout << '\n' << "File Failed to open/Not Found" << '\n';
        exit(-1);
    }

    // create string var to store user/pass and read input into it
    string info_store{ };
    cout << "Enter a username and password, separated by a space: ";
    getline(cin, info_store);

    // write string data to file
    userFile << info_store << endl;

    // close stream
    userFile.close();
}


void IsValidCredential(string username, string password)
{

}
