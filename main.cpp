#include <iostream>
#include <sqlite3.h>
#include <SQLiteCpp/SQLiteCpp.h>


int main()
{
    std::cout << "**** To be turned into a test suite for SQLiteCpp and SQLite3 for other projects ****" << std::endl;
    std::cout << '\n';

    // create an object 'data_base' of class SQLite::Database and create a table called login-db if it does not already exist
    SQLite::Database data_base("login-db.db", SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE);
    data_base.exec("CREATE TABLE IF NOT EXISTS login-db (date INTEGER PRIMARY KEY, weight INTEGER, notes TEXT);");

    // get user input for weight, notes, and date
    std::cout << "Hello User! " << '\n' << "Please enter your weight: ";
    int temp_weight;
    std::cin >> temp_weight;

    std::cout << "Please enter any notes you would like to add: ";
    std::string temp_notes;
    std::cin.ignore();
    std::getline(std::cin, temp_notes);

    std::cout << "Please enter the date in the format YYYYMMDD: ";
    int temp_date;
    std::cin >> temp_date;

    // data insertion code
    try
    {
        // query the database login-db and bind the date, weight, and notes that the user entered to the database
        SQLite::Statement insert_user_stmt(data_base, "INSERT or IGNORE INTO login-db VALUES (?, ?, ?);");
        insert_user_stmt.bind(1, temp_date);
        insert_user_stmt.bind(2, temp_weight);
        insert_user_stmt.bind(3, temp_notes);

        if (insert_user_stmt.exec() == 0)  // Check if no rows were inserted
        {
            std::cout << "Data for the provided date already exists!" << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cout << "exception during insertion: " << e.what() << std::endl;
    }

    // display data code
    try
    {
        // Compile a SQL query, containing one parameter (index 1)
        SQLite::Statement query_stmt(data_base, "SELECT * FROM login-db");

        // Loop to execute the query step by step, to get rows of result
        while (query_stmt.executeStep())
        {
            // Demonstrate how to get some typed column value
            int date = query_stmt.getColumn(0);
            int weight = query_stmt.getColumn(1);
            std::string notes = query_stmt.getColumn(2);

            std::cout << "row: " << date << ", " << weight << ", " << notes << std::endl;
        }
    }
    catch (std::exception& e)
    {
        std::cout << "exception during data display/query_stmt: " << e.what() << std::endl;
    }

    return 0;
}
