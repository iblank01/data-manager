#include <iostream>


struct UsrNode
{
    int m_usr_date{ };
    int m_usr_weight{ };
    std::string m_usr_note{ };

    UsrNode *r_ptr;
    UsrNode *l_ptr;
};


class DataFormat
{
private:
    UsrNode* head_ptr_;
public:
    static UsrNode *GetNode();
    void DisplayNode();
};



int main()
{
    // create instance of DataFormat
    DataFormat Format{};

    // non-static requires instance of class, static does not
    DataFormat::GetNode();
    Format.DisplayNode();
    return 0;
}



UsrNode* DataFormat::GetNode()
{
    UsrNode *new_node;
    new_node = (UsrNode *) malloc(sizeof(UsrNode));// new_node uses malloc

    // allow usr enter date
    std::cout << "Date: ";
    std::cin >> new_node->m_usr_date;
    // allow usr enter weight
    std::cout << "Weight: ";
    std::cin >> new_node->m_usr_weight;
    // allow usr enter a note (NOTE: FIX STRING ENTRY)
    std::cout << "Note: ";
    std::cin >> new_node->m_usr_date;

    new_node->l_ptr = nullptr;
    new_node->r_ptr = nullptr;  // the new_node sides point to nothing by default

    return new_node;
}   // end of GetNode()


void DataFormat::DisplayNode()
{
    // DEBUGGING (L: 58)
    std::cout << '\n' << "Entered 'Display Node' function." << '\n';


}   // end of DisplayNode