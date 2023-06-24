#include <iostream>
#include <string>
#include <sstream>
#include <SQLiteCpp/SQLiteCpp.h>



int main()
{
    /*
     * Open the database named "login_system.db3"
     * OPEN_READWRITE | OPEN_CREATE will create the file if it doesn't exist
     * OPEN_READWRITE will open the file for reading and writing, OPEN_CREATE will create the file if it doesn't exist
    */
     SQLite::Database data_base("login_system.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

    /*
     * Create the "users" table if it doesn't exist using SQL DDL (Data Definition Language) statements
     * The table will have 2 columns, username and password, both of type TEXT
    */
    data_base.exec("CREATE TABLE IF NOT EXISTS users (username TEXT UNIQUE, password TEXT)");

    while (true)
    {
        int choice{ };
        std::cout << "1) Register\n2) Login\n3) Exit\nEnter your choice: ";
        std::cin >> choice;

        switch (choice)
        {
            // Register
            case 1:
            {
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
                catch (SQLite::Exception& e)
                {
                    // If the username is already taken, SQLite will throw an exception, we catch it and print the error
                    std::cout << "Error: " << e.what() << '\n';
                }
                
                break;
            }   // end case 1

            // Login
            case 2: {
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
                    } else
                    {
                        std::cout << "Incorrect username/password\n";
                    }
                } else
                {
                    std::cout << "Incorrect username/password\n";
                }
                break;
            }   // end case 2

            // exit
            case 3:
            {
                return 0;
            }
            // invalid choice (not in provided options)
            default:
                std::cout << "Invalid choice\n";
        }  // end switch
    }
}
