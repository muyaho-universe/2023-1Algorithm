#include <iostream>
#include <regex>
#include <string>

using namespace std;

#define MAX_HEAP_SIZE 31        // index 0 in queue will be left empty for null saftety
                                // heap will start from 1, so its size is fixed at 30


//define class for elements.
class information
{
    string name;
    string id;      // id data type is string, not integer, to handle non-ineger inputs
    string school;
public:
    information();
    information(string n, string i, string s);
    void set_name(string n);
    void set_id(string i);
    void set_school(string s);
    string get_name();
    string get_id();
    string get_school();
};

information::information(string n, string i, string s)
{
    name = n;
    id = i;
    school = s;
}

information::information()
{
    name = " ";
    id = " ";
    school = " ";
}

void information::set_name(string n)
{
    name = n;
}

void information::set_id(string i)
{
    id = i;
}

void information::set_school(string s)
{
    school = s;
}

string information::get_name()
{
    return name;
}

string information::get_id()
{
    return id;
}

string information::get_school()
{
    return school;
}

class min_priority_queue
{
    information q[MAX_HEAP_SIZE];
    int queue_length;
    void adjust(int t_root);
public :
    min_priority_queue();
    int get_queue_length();
    void insert(information info);
    void print_queue();
    void edit_q(int index);
    information delete_first();
    bool is_full();
    bool is_empty();
};

min_priority_queue::min_priority_queue()
{
    queue_length = 0;
}

int min_priority_queue::get_queue_length()
{
    return queue_length;
}

void min_priority_queue::insert(information info)   // applying heap concept here
{
    int i;
    queue_length++;
    i = queue_length;

    while ((i != 1) && (stoi(info.get_id()) < stoi(q[i / 2].get_id())))
    {
        q[i] = q[i / 2];
        i /= 2;
    }
    q[i] = info;
}

void min_priority_queue::print_queue()
{
    for(int i = 1; i < queue_length + 1; i++)
    {
        cout << "["+ q[i].get_name() +", "+ q[i].get_id() + ", "+ q[i].get_school() +"] ";
    }
    cout << endl;
}

void min_priority_queue::adjust(int t_root)
{
    int tmpkey;
    int parent;
    information tmp;

    tmp = q[t_root];
    tmpkey = stoi(tmp.get_id());
    parent = t_root / 2;

    while (parent >= 1)
    {
        if(tmpkey > stoi(q[parent].get_id()))
        {
            break;
        }
        else
        {
            q[t_root] = q[parent];
            t_root = parent;
            parent /= 2;
        }
    }
    
    q[t_root] = tmp;
}

information min_priority_queue::delete_first()
{
    information t;
    information tmp;
    int parent, child;
    t = q[1];           // for return value
    tmp = q[queue_length]; // last element
    queue_length--;
    parent = 1;         // root
    child = 2;          // left child of root

    while(child <= queue_length)
    {
        if ((child < queue_length) && (stoi(q[child].get_id()) > stoi(q[child + 1].get_id())))
        {
            child++;    // choose right child
        }
        if (stoi(tmp.get_id()) <= stoi(q[child].get_id()))
        {
            break;
        }
        q[parent] = q[child];
        parent = child;
        child *= 2;
    }
    q[parent] = tmp;
    return t;
}

bool min_priority_queue::is_full()
{
    return (queue_length == MAX_HEAP_SIZE - 1);
}

bool min_priority_queue::is_empty()
{
    return (queue_length == 0);
}

class utils
{    
public:
    string id_validation_check(string id);
    void print_menu();              //
    information register_form();    //
    int get_index(int len);               //
};

void utils::print_menu()
{
    cout << "\n*********** MENU ***********" << endl;
    cout << "I : Insert new element into queue." << endl;
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
    
    regex reg("[1-9]{1}\\d{4}");        // declare regular expression to check wheter id is four length integer number
    if (regex_match(id, reg))
    {
        return id;               // if it is, return type 1;
    }
    else
    {
        string temp = "";
        for (int i = 0; i < id.length(); i++)
        {
            if (47 < id[i] && id[i] < 58)
            {
                temp += id[i];                  // store all the number characters in temp
            }
            if(id[i] == 'o' || id[i] == 'O')    // if user used "o" or "O" as 0, convert it to 0
            {
                temp += '0';
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

information utils::register_form()
{
    string name;
    string id;
    string school;
    string temp;
    bool id_checker = true;

    cout << "Enter name of element: ";
    cin >> name;
    cin.ignore();
    while (id_checker)      // this while loop checks wheter id is valid. it gives users the chance to check the input id is what they intended
    {
        cout << "Enter id of element: ";
        getline(cin, id);   // to allow users using id with the space

        //if id format is invalid, it will be checked with the user
        temp = id_validation_check(id);
        if (temp == "-1")
        {
            cout << "Wrong id format. Enter id again!" << endl;
        }
        else
        {
            string go_nogo;
            cout << "Are you sure to use id: " << temp << "? (Y/n) ";
            cin >> go_nogo;
            do
            {
                if(go_nogo == "Y" || go_nogo == "y")
                {
                    id = temp;
                    id_checker = false;
                    break;
                }
                if(go_nogo == "N" || go_nogo == "n")
                {
                    cin.ignore();
                    break;
                }
                else
                {
                    cout << "Type wheter use it or not (Y/n): ";
                    cin >> go_nogo;
                }
            } while (true);
        }
        
    }
    
    cout << "Enter school of element: ";
    cin >> school;

    information info(name, id, school);     // define new information instance

    cout << "New element [" + info.get_name() + ", " + info.get_id() + ", " + info.get_school() + "] is inserted." << endl;

    return info;
}

int utils::get_index(int len)
{
    int index;

    while (true)
    {
        
        cout << "Enter index of element: ";
        cin >> index;
        cin.ignore();
        if (index <= len)
        {
            break;
        }
        else
        {
            cout << "Index out of bounds!" << endl;
            cin.ignore();
        }
    }
  
    return index;
}


void min_priority_queue::edit_q(int index)
{
    string temp;
    string id;
    bool id_checker = true;
    utils util;

    while (id_checker)
    {
        cout << "Enter id value: ";
        getline(cin, id);
        temp = util.id_validation_check(id);
        if (temp == "-1")
        {
            cout << "Wrong id format. Enter id again!" << endl;
        }
        else
        {
            string go_nogo;
            cout << "Are you sure to use id: " << temp << "? (Y/n) ";
            cin >> go_nogo;
            do
            {
                if(go_nogo == "Y" || go_nogo == "y")
                {
                    if(stoi(temp) > stoi(q[index].get_id()))
                    {
                        cout << "Id isn't decresead! Input it again." << endl;
                        cin.ignore();
                    }
                    else
                    {
                        id = temp;
                        id_checker = false;
                        q[index].set_id(id);
                        adjust(index);
                    }
                    break;
                }
                if(go_nogo == "N" || go_nogo == "n")
                {
                    cin.ignore();
                    break;
                }
                else
                {
                    cout << "Type wheter use it or not (Y/n): ";
                    cin >> go_nogo;
                }
            } while (true);
        }
    }
}

int main()
{
    min_priority_queue queue;
    bool keep = true;
    string menu;
    utils util;
    do
    {
        information temp;
        util.print_menu();
        cin >> menu;
        cin.clear();

        switch (menu[0])
        {
        case 'I':
            if (queue.is_full())
            {
                cout << "Queue is full." << endl;
            }
            else
            {
                queue.insert(util.register_form());
            }
            break;

        case 'D':
            if (queue.is_empty())
            {
                cout << "Queue is empty." << endl;
            }
            else
            {
                information info = queue.delete_first();
                cout << "[" + info.get_name() + ", " + info.get_id() + ", "+ info.get_school() +"] is deleted." << endl;
            } 
            break;
            
        case 'C':
            if (queue.is_empty())
            {
                cout << "Queue is empty." << endl;
            }
            else
            {
                int index = util.get_index(queue.get_queue_length());
                queue.edit_q(index);          
            } 
            break;

        case 'P':
            if(queue.is_empty())
            {
                cout << "Queue is empty." << endl;
            }
            else
            {
                queue.print_queue();
            }
            break;
        case 'Q':
            keep = false;
            break;
        default:
            cout << "Wrong Input!" << endl;
            break;
        }
    } while (keep);
    
    cout << "Thank you. Bye!" << endl;

    return 0;
}