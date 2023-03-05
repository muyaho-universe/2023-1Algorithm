#include <iostream>
#include <regex>
#include <string>

using namespace std;

#define MAX_HEAP_SIZE 30

//define class for elements.
class information
{
public:
    string name;
    string id;      // id data type is string, not integer, to handle non-ineger inputs
    string school;
    void set_data(string n, string i, string s);
};

void information::set_data(string n, string i, string s)
{
    name = n;
    id = i;
    school = s;
}

class utils
{
    string id_validation_check(string id);
public:
    void print_menu();
    void register_form();
};

void utils::print_menu()
{
    cout << "*********** MENU ***********" << endl;
    cout << "I : Isert new element into queue." << endl;
    cout << "D : Delete element with smallest key from queue." << endl;
    cout << "C : Decrease key of element in queue." << endl;
    cout << "P : Print out all elements in queue" << endl;
    cout << "Q : Quit\n" << endl;
    cout << "Choose menu: ";
}

string utils::id_validation_check(string id)
{
    if (id.length() < 4)
    {
        return "-1";              // id length is less than 4. don't need to check the rest
    }
    
    regex reg("\\d{4}");        // declare regular expression to check wheter id is four length integer number
    if (regex_match(id, reg))
    {
        return "1";               // if it is, return type 1;
    }
    else
    {
        string temp = "";
        for (int i = 0; i < id.length(); i++)
        {
            if (48 < id[i] && id[i] < 58)
            {
                temp += id[i];                  // store all the number characters in temp
            }
            if(id[i] == 'o' || id[i] == 'O')    // if user used "o" or "O" as 0, convert it to 0
            {
                temp += '0';
            }
            if (temp.length() >= 5)
            {
                break;
            }
        }

        if(temp.length() == 4 && temp[0] != '0')
        {
            return temp;          // return temp itself
        }
        else
        {
            return "-1";        // input id has length problem, or starts with 0
        }
    }   
}

void utils::register_form()
{
    string name;
    string id;
    string school;

    cout << "Enter name of element: ";
    cin >> name;
    cout << "Enter id of element: ";
    cin >> id;
    //if id format is invalid, it will be checked with the user
    
    cout << "Enter school of element: ";
    cin >> school;

    information info;
    info.set_data(name, id, school);

}




int main()
{
    return 0;
}