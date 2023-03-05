#include <iostream>
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
public:
    void print_menu();
    
};

void utils::print_menu()
{
    cout << "*********** MENU ***********" << endl;
    cout << "I : Isert new element into queue." << endl;
    cout << "D : Delete element with smallest key from queue." << endl;
    cout << "C : Decrease key of element in queue." << endl;
    cout << "P : Print out all elements in queue" << endl;
    cout << "Q : Quit\n" << endl;
}


int main()
{
    return 0;
}