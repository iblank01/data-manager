#include <iostream>
#include <string>
#include <sstream>
#include <SQLiteCpp/SQLiteCpp.h>

class RegistrationProcess
{
    public:
        // easy to use functions for user to register, login, and exit, modularized
        void userRegister();
        void userLogin();
        // may eventually add a userExit() function with a different functionality (i.e. return to home page, exiting the main menu screen
//        void userExit();
        void mainMenuSelect();
};

void RegistrationProcess::userRegister()
{
    // Create a database file, if it doesn't exist it will be created
    SQLite::Database data_base("login_system.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    // Create a table if it doesn't exist
    data_base.exec("CREATE TABLE IF NOT EXISTS users (username TEXT UNIQUE, password TEXT)");

    std::string username;
    std::string password;

    // prompt user for username and password
    std::cout << "Enter a username: ";
    std::cin >> username;
    std::cout << "Enter a password: ";
    std::cin >> password;

    // try to insert the username and password into the database
    try
    {
        // The ? are placeholders for the values we will bind to the query, this is to prevent SQL injection
        SQLite::Statement query(data_base, "INSERT INTO users VALUES (?, ?)");
        query.bind(1, username);
        query.bind(2, password);
        query.exec();
        std::cout << "User registered successfully\n";
    }
    // catch error if it is thrown in "try" block
    catch (SQLite::Exception &e)
    {
        // If the username is already taken, SQLite will throw an exception, we catch it and print the error
        std::cout << "Error: " << e.what() << '\n';
    }
}   // end userRegister


void RegistrationProcess::userLogin()
{
    // Create a database file, if it doesn't exist it will be created
    SQLite::Database data_base("login_system.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);
    // Create a table if it doesn't exist
    data_base.exec("CREATE TABLE IF NOT EXISTS users (username TEXT UNIQUE, password TEXT)");

    std::string username;
    std::string password;

    std::cout << "Enter your username: ";
    std::cin >> username;
    std::cout << "Enter your password: ";
    std::cin >> password;

    // Check if the username exists and if the password is correct
    SQLite::Statement query(data_base, "SELECT password FROM users WHERE username = ?");
    query.bind(1, username);

    // If the query returns a row the username exists, else "No user with that username"
    if (query.executeStep())
    {
        std::string stored_password = query.getColumn(0);

        // if pass matches, login user, else, incorrect password
        if (password == stored_password)
        {
            std::cout << "Login successful\n";
        }
        else
        {
            std::cout << "Incorrect username/password\n";
        }
    }
    else
    {
        std::cout << "Incorrect username/password\n";
    }
}   // end userLogin


void RegistrationProcess::mainMenuSelect()
{
    int main_menu_choice{ };
    char repeat_choice{ };

    // exe one time, then loop if user wants to try again
    do
    {
        std::cout << "1) Register\n2) Login\n3) Exit\nEnter your main_menu_choice: ";
        std::cin >> main_menu_choice;

        // switch menu for simpler implementation of menu
        switch (main_menu_choice)
        {
            case 1:
            {
                userRegister();
                break;
            }
            case 2:
            {
                userLogin();
                break;
            }
            case 3:
            {
                exit(-1);
            }
            default:
                std::cout << "Invalid main_menu_choice\n";
        }   // end switch

        // ask user if they want to try again
        std::cout << "Would you like to try again/return to main menu? (y/n): ";
        std::cin >> repeat_choice;

    } while (repeat_choice == 'y');
}   // end mainMenuSelect




int main()
{
    RegistrationProcess registration_process;
    registration_process.mainMenuSelect();

    return 0;
}
