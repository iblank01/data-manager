#include <iostream>
#include <string>
#include <sstream>
#include <SQLiteCpp/SQLiteCpp.h>

int main() {
    SQLite::Database db("login_system.db3", SQLite::OPEN_READWRITE | SQLite::OPEN_CREATE);

    // Create the users table if it doesn't exist
    db.exec("CREATE TABLE IF NOT EXISTS users (username TEXT UNIQUE, password TEXT)");

    while (true) {
        int choice;
        std::cout << "1) Register\n2) Login\n3) Exit\nEnter your choice: ";
        std::cin >> choice;

        switch (choice) {
            case 1: {
                std::string username;
                std::string password;

                std::cout << "Enter a username: ";
                std::cin >> username;
                std::cout << "Enter a password: ";
                std::cin >> password;

                try {
                    SQLite::Statement query(db, "INSERT INTO users VALUES (?, ?)");
                    query.bind(1, username);
                    query.bind(2, password);
                    query.exec();
                    std::cout << "User registered successfully\n";
                } catch (SQLite::Exception& e) {
                    std::cout << "Error: " << e.what() << '\n';
                }
                break;
            }

            case 2: {
                std::string username;
                std::string password;

                std::cout << "Enter your username: ";
                std::cin >> username;
                std::cout << "Enter your password: ";
                std::cin >> password;

                SQLite::Statement query(db, "SELECT password FROM users WHERE username = ?");
                query.bind(1, username);

                if (query.executeStep()) {
                    std::string stored_password = query.getColumn(0);

                    if (password == stored_password) {
                        std::cout << "Login successful\n";
                    } else {
                        std::cout << "Incorrect password\n";
                    }
                } else {
                    std::cout << "No user with that username\n";
                }
                break;
            }

            case 3:
                return 0;

            default:
                std::cout << "Invalid choice\n";
        }
    }
}
