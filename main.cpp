#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

// functions for login management
void EnterInformationFile();
int IsValidCredential(string username, string password);
void MainMenu();


int main()
{
    EnterInformationFile();
    IsValidCredential("ianblankenship", "marlow");
    return 0;
}



// EnterInformationFile meant to allow user to register new user
// current: takes new credentials (separated by space; username password) and appends value to existing file
// tbd: connect to db for better/secure storage, allow new accounts to be registered and info entered into this
void EnterInformationFile()
{
    // create object userPassFile in fstream class
    ofstream userEntryFile ("/Users/ianblankenship/data-managing/userPassFile.txt", ios::app);

    // exit if the file does not exist/cannot be opened
    if (!userEntryFile)
    {
        cout << '\n' << "File Failed to open/Not Found" << '\n';
        exit(-1);
    }

    // create string var to store user/pass and read input into it
    string info_store{ };
    cout << "Enter a username and password, separated by a space: ";
    getline(cin, info_store);

    // write string data to file
    userEntryFile << info_store << endl;

    // close stream
    userEntryFile.close();
}


// validate credentials entered by a user (username, password)
// current: searches file "userPassFile.txt" for a given username & password a user enters and returns (0) if wrong, (1) is correct
// tbd: will validate and send user to user/session-specific data manager
int IsValidCredential(string username, string password)
{
    // debugging
    cout << '\n' << username << '\n';
    // end debug

    // create object for taking inputs
    ifstream userCheckFile("/Users/ianblankenship/data-managing/userPassFile.txt");

    if (!userCheckFile)
    {
        cout << "File not found/error in opening" << '\n';
        return(-1);
    }

    // line = temp line store; user = temp username store; pass = temp password store
    string line_store{ };
    string user_store{ };
    string pass_store{ };

    // for ret value
    int match_or_none{ };

    // while-loop, while still things still to be read-in
    while (getline(userCheckFile, line_store))
    {
        // to discern if what is read is a string
        stringstream iss(line_store);
        iss >> user_store >> pass_store;

        // if entered username == username_in_file & password == pass_in_file
        if (username == user_store && password == pass_store)
        {
            cout << '\n' << "Match Found! You're in";
            match_or_none = 1;
        }
        else       // user || pass wrong
        {
            cout << '\n' << "Wrong Username or password. Try again.";
            match_or_none = 0;
        }
    }

    // close file stream
    userCheckFile.close();

    // return validation/lack thereof
    return match_or_none;
}


// MainMenu function to be before other calls; serves to discern user intent
// current: display menu in console, take user input and decide where to go; if login, filter (0/1) if user moves to new page
// tbd: display menu in QtWidget or other GUI application (webapp),
void MainMenu()
{
    cout << "1) New User Registration" << '\n'
        << "2) Existing User? Login" << '\n'
        << "3) Not interested? Exit" << endl;

    // read user main menu read in
    char user_mm_choice{ };
    cin >> user_mm_choice;


}