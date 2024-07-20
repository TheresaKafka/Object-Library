#include <iostream>
#include <vector>
#include <string>
#include<algorithm>
#define Limit 32767
using namespace std;
class Manager {
public:
    virtual void Menu() const {
        cout << "1. Person\n"
             << "2. Book\n";
    }

    virtual void Add() {
        Menu();
    }

    virtual void Delete() {
        Menu();
    }
    virtual void Change()
    {
        Menu();
    }
    virtual ~Manager() {}
};

class Calendar {
private:
    int day;
    int week;
    int year;

public:
    Calendar() : day(0), week(0), year(0) {}
    Calendar(int d, int w, int y) : day(d), week(w), year(y) {}
    Calendar(const Calendar &c) : day(c.day), week(c.week), year(c.year) {}

    int getDay() const { return day; }
    int getWeek() const { return week; }
    int getYear() const { return year; }

    void setDay(int d) { day = d; }
    void setWeek(int w) { week = w; }
    void setYear(int y) { year = y; }

    virtual void input() {
        cout << "Enter day: ";
        cin >> day;
        cout << "Enter week: ";
        cin >> week;
        cout << "Enter year: ";
        cin >> year;
    }

    virtual void display() const {
        cout << day << "," << week << "," << year << endl;
    }

    int operator-(const Calendar& other) const {
        int days1 = year * 365 + week * 7 + day;
        int days2 = other.year * 365 + other.week * 7 + other.day;
        return days1 - days2;
    }
};

class Person : public Calendar {
private:
    string phoneNumber;
    int ID;
    string Name;
    string Address;
    int sex; // 0.Male, 1.Female

public:
    Person() : Calendar(), ID(0), Name(""), Address(""), sex(0), phoneNumber("") {}
    Person(int id, const string& name, const string& address, int s, int d, int w, int y, const string& phoneNumber)
        : Calendar(d, w, y), ID(id), Name(name), Address(address), sex(s), phoneNumber(phoneNumber) {}
    Person(const Person& p)
        : Calendar(p), ID(p.ID), Name(p.Name), Address(p.Address), sex(p.sex), phoneNumber(p.phoneNumber) {}

    int getID() const { return ID; }
    string getName() const { return Name; }
    string getAddress() const { return Address; }
    int getSex() const { return sex; }
    string getPhoneNumber() const { return phoneNumber; }

    void setID(int id) { ID = id; }
    void setName(const string& name) { Name = name; }
    void setAddress(const string& address) { Address = address; }
    void setSex(int s) { sex = s; }
    void setPhoneNumber(const string& phone) { phoneNumber = phone; }

    virtual void input() override {
        Calendar::input();
        cout << "Enter ID: ";
        cin >> ID;
        cin.ignore(Limit,'\n');
        cout << "Enter Name: ";
        getline(cin, Name);
        cout << "Enter Address: ";
        getline(cin, Address);
        cout << "Enter Sex (0 for Male, 1 for Female): ";
        cin >> sex;
        cin.ignore(Limit,'\n');
        cout << "Enter Phone Number: ";
        getline(cin, phoneNumber);
    }

    virtual void display() const override {
        Calendar::display();
        cout << "ID: " << ID << ", Name: " << Name << ", Address: " << Address
            << ", Sex: " << (sex == 0 ? "Male" : "Female")
            << ", Phone Number: " << phoneNumber << "\n";
    }
};

class book : public Calendar {
private:
    int ID;
    int Quantity;
    string name;
    string title;
    string author;

public:
    book() : ID(0), Quantity(0), name(""), title(""), author("") {}

    book(int id, int quantity, const string& n, const string& t, const string& a, int d, int w, int y)
        : Calendar(d, w, y), ID(id), Quantity(quantity), name(n), title(t), author(a) {}

    book(const book& b)
        : Calendar(b), ID(b.ID), Quantity(b.Quantity), name(b.name), title(b.title), author(b.author) {}

    int getID() const { return ID; }
    int getQuantity() const { return Quantity; }
    string getName() const { return name; }
    string getTitle() const { return title; }
    string getAuthor() const { return author; }

    void setID(int id) { ID = id; }
    void setQuantity(int quantity) { Quantity = quantity; }
    void setName(const string& n) { name = n; }
    void setTitle(const string& t) { title = t; }
    void setAuthor(const string& a) { author = a; }

    void input() override {
        Calendar::input();
        cout << "Enter Book ID: ";
        cin >> ID;
        cout << "Enter Quantity: ";
        cin >> Quantity;
        cin.ignore(Limit,'\n');
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Title: ";
        getline(cin, title);
        cout << "Enter Author: ";
        getline(cin, author);
    }

    void display() const override {
        Calendar::display();
        cout << "Book ID: " << ID << ", Quantity: " << Quantity << ", Name: " << name
            << ", Title: " << title << ", Author: " << author << "\n";
    }
};

class customer : public Person {
private:
    int member; // 0: member, 1: no member

public:
    customer() : Person(), member(0) {}

    customer(int id, const string& name, const string& address, int s, int d, int w, int y, const string& phoneNumber, int member)
        : Person(id, name, address, s, d, w, y, phoneNumber), member(member) {}

    customer(const customer& c)
        : Person(c), member(c.member) {}

    int getMember() const { return member; }

    void setMember(int member) { this->member = member; }

    void input() override {
        Person::input();
        cout << "0. Member, 1. No Member: ";
        cin >> member;
    }

    void display() const override {
        Person::display();
        cout << "Member: " << (member == 0 ? "Yes" : "No") << "\n";
    }
};

class staff : public Person {
private:
    string staffID;
    string Position;

public:
    staff() : Person(), staffID(""), Position("") {}

    staff(const string& id, const string& position, int pid, const string& name, const string& address, int s, int d, int w, int y, const string& phoneNumber)
        : Person(pid, name, address, s, d, w, y, phoneNumber), staffID(id), Position(position) {}

    staff(const staff& s)
        : Person(s), staffID(s.staffID), Position(s.Position) {}

    string getStaffID() const { return staffID; }
    string getPosition() const { return Position; }

    void setStaffID(const string& id) { staffID = id; }
    void setPosition(const string& position) { Position = position; }

    void input() override {
        Person::input();
        cout << "Enter Staff ID: ";
        getline(cin, staffID);
        cout << "Enter Position: ";
        getline(cin, Position);
    }

    void display() const override {
        Person::display();
        cout << "Staff ID: " << staffID << ", Position: " << Position << "\n";
    }
};
class changer
{
    private:
    int pid,bid,prince;
    Calendar bookreturn,payday; 
    public:
    changer() : pid(0), bid(0), prince(0),  bookreturn(), payday() {}
    changer(int personID, int bookID, int price,  const Calendar& returnDate, const Calendar& paymentDate)
        : pid(personID), bid(bookID), prince(price), bookreturn(returnDate), payday(paymentDate) {}

    int getPersonID() const { return pid; }
    int getBookID() const { return bid; }
    int getPrice() const { return prince; }
    Calendar getReturnDate() const { return bookreturn; }
    Calendar getPaymentDate() const { return payday; }

    void setPersonID(int personID) { pid = personID; }
    void setBookID(int bookID) { bid = bookID; }
    void setPrice(int price) { prince = price; }
    void setReturnDate(const Calendar& returnDate) { bookreturn = returnDate; }
    void setPaymentDate(const Calendar& paymentDate) { payday = paymentDate; }

};
class library : public Manager {
private:
    vector<Person*> listPer;
    vector<book*> listBook;
    vector<changer> changerHis;
public:
    library() {}
    ~library() {
        for (Person* p : listPer) {
            delete p;
        }
        for (book* b : listBook) {
            delete b;
        }
    }
    void Add() override {
        cout<<"1.Customer\n"
            <<"2.Staff\n"
            <<"3.Book";
        int choice;
        cin >> choice;
        cin.ignore(Limit,'\n');

        switch (choice) {
        case 1: {
            
            customer* cust = new customer();
            
            bool IdExits;
        do
        {
        IdExits=false;
        cust->input();
        for ( const auto &listP : listPer)
        {
            if (listP->getID()==cust->getID())
            {
                IdExits=true;
                cout << "Warning: ID " << cust->getID() << " already exists. Please enter a ID.\n";
                break;
            }
            
        }
        }
        while(IdExits);
            listPer.push_back(cust);
            break;
        }
        case 2: {
            staff* stf = new staff();
            bool IdExits;
        do
        {
        IdExits=false;
        stf->input();
        for ( const auto &listP : listPer)
        {
            if (listP->getID()==stf->getID())
            {
                IdExits=true;
                cout << "Warning: ID " << stf->getID() << " already exists. Please enter a ID.\n";
                break;
            }
            
        }
        }
        while(IdExits);
            listPer.push_back(stf);
            break;
        }
        case 3: {
            book* bk = new book();
                bool IdExits;
        do
        {
        IdExits=false;
        bk->input();
        for ( const auto &listP : listPer)
        {
            if (listP->getID()==bk->getID())
            {
                IdExits=true;
                cout << "Warning: ID " << bk->getID() << " already exists. Please enter a ID.\n";
                break;
            }
            
        }
        }
        while(IdExits);
            listBook.push_back(bk);
            break;
        }
        default:
            cout << "Invalid choice.\n";
        }
    }

    void Delete() override {
        cout << "Delete operation\n";
    }

    void displayAll() const {
        cout << "\n=== Displaying Library Contents ===\n";
        cout << "Person:\n";
        for (const auto& p : listPer) {
            p->display();
        }
        cout << "\nBooks:\n";
        for (const auto& b : listBook) {
            b->display();
        }
    }
    void searchBook(vector<book*>&searched) const {

        bool found = false;
        cout<<"Search for\n";
        cout<<"1.ID\n"
            <<"2.Name\n"
            <<"3.Author\n"
            <<"4.Title\n"
            <<"5.Quantity\n";
        int choice;
        cin>>choice;
        cin.ignore(Limit,'\n');
        
    switch (choice) {
        case 1: {
            int searchID;
            cout << "Enter Book ID to search: ";
            cin >> searchID;
            for (const auto& b : listBook) {
                if (b->getID() == searchID) {
                    searched.push_back(b);
                    found = true;
                }
            }
            break;
        }
        case 2: {
            string searchName;
            cout << "Enter Book Name to search: ";
            getline(cin, searchName);
            for (const auto& b : listBook) {
                if (b->getName() == searchName) {
                    searched.push_back(b);
                    found = true;
                }
            }
            break;
        }
        case 3: {
            string searchAuthor;
            cout << "Enter Author Name to search: ";
            getline(cin, searchAuthor);
            for (const auto& b : listBook) {
                if (b->getAuthor() == searchAuthor) {
                    searched.push_back(b);
                    found = true;
                }
            }
            break;
        }
        case 4: {
            string searchTitle;
            cout << "Enter Title to search: ";
            getline(cin, searchTitle);
            for (const auto& b : listBook) {
                if (b->getTitle() == searchTitle) {
                    searched.push_back(b);
                    found = true;
                }
            }
            break;
        }
        case 5: {
            int searchQuantity;
            cout << "Enter Quantity to search: ";
            cin >> searchQuantity;
            for (const auto& b : listBook) {
                if (b->getQuantity() == searchQuantity) {
                    searched.push_back(b);
                    found = true;
                }
            }
            break;
        }
        default:
            cout << "Invalid choice.\n";
    }
    }
void searchPerson(vector<Person*>&searched) const {
    bool found = false;
    cout << "Search Person by:\n";
    cout << "1. ID\n"
         << "2. Name\n"
         << "3. Address\n"
         << "4. Phone Number\n"
         << "5. Member Status\n"
         << "6. Staff ID\n"
         << "7. Position\n";
    
    int choice;
    cin >> choice;
    cin.ignore(Limit, '\n');

    switch (choice) {
        case 1: {
            int searchID;
            cout << "Enter Person ID to search: ";
            cin >> searchID;
            for (const auto& p : listPer) {
                if (p->getID() == searchID) {
                    searched.push_back(p);
                    found = true;
                }
            }
            break;
        }
        case 2: {
            string searchName;
            cout << "Enter Person Name to search: ";
            getline(cin, searchName);
            for (const auto& p : listPer) {
                if (p->getName() == searchName) {
                    searched.push_back(p);
                    found = true;
                }
            }
            break;
        }
        case 3: {
            string searchAddress;
            cout << "Enter Address to search: ";
            getline(cin, searchAddress);
            for (const auto& p : listPer) {
                if (p->getAddress() == searchAddress) {
                    searched.push_back(p);
                    found = true;
                }
            }
            break;
        }
        case 4: {
            string searchPhoneNumber;
            cout << "Enter Phone Number to search: ";
            getline(cin, searchPhoneNumber);
            for (const auto& p : listPer) {
                if (p->getPhoneNumber() == searchPhoneNumber) {
                    searched.push_back(p);
                    found = true;
                }
            }
            break;
        }
        case 5: {
            int searchMemberStatus;
            cout << "Enter Member Status (0 for Member, 1 for Non-Member) to search: ";
            cin >> searchMemberStatus;
            for (const auto& p : listPer) {
                if (dynamic_cast<customer*>(p) && dynamic_cast<customer*>(p)->getMember() == searchMemberStatus) {
                    searched.push_back(p);
                    found = true;
                }
            }
            break;
        }
        case 6: {
            string searchStaffID;
            cout << "Enter Staff ID to search: ";
            getline(cin, searchStaffID);
            for (const auto& p : listPer) {
                if (dynamic_cast<staff*>(p) && dynamic_cast<staff*>(p)->getStaffID() == searchStaffID) {
                    searched.push_back(p);
                    found = true;
                }
            }
            break;
        }
        case 7: {
            string searchPosition;
            cout << "Enter Position to search: ";
            getline(cin, searchPosition);
            for (const auto& p : listPer) {
                if (dynamic_cast<staff*>(p) && dynamic_cast<staff*>(p)->getPosition() == searchPosition) {
                    searched.push_back(p);
                    found = true;
                }
            }
            break;
        }
        default:
            cout << "Invalid choice.\n";
    }
    if (!found) {
        cout << "Person not found.\n";
    }
}
void Delete1()  {
    Menu();
    int choice;
    cin >> choice;
    cin.ignore(Limit, '\n');
    switch (choice)
    {
    case 1:
    {
        searchPersonToDelete();
        break;
    }
    case 2:
    {
        searchBookToDelete();
        break;
    }
    default:
        cout << "Invalid choice.\n";
        break;
    }
}
void searchPersonToDelete() {
    bool found = false;
    vector<Person*> searched;
    searchPerson(searched);

    if (!searched.empty()) {
        cout << "Choose person to delete:\n";
        for (size_t i = 0; i < searched.size(); ++i) {
            cout << i + 1 << ". ";
            searched[i]->display();
        }

        int deleteChoice;
        cin >> deleteChoice;
        cin.ignore(Limit, '\n');

        if (deleteChoice >= 1 && deleteChoice <= static_cast<int>(searched.size())) {
            Person* personToDelete = searched[deleteChoice - 1];
            auto it = std::find(listPer.begin(), listPer.end(), personToDelete);
            if (it != listPer.end()) {
                listPer.erase(it);
                delete personToDelete;
                cout << "Person deleted successfully.\n";
            } else {
                cout << "Error: Person not found in list.\n";
            }
        } else {
            cout << "Invalid choice.\n";
        }
    }
}
void searchBookToDelete() {
    bool found = false;
    vector<book*> searched;
    searchBook(searched);

    if (!searched.empty()) {
        cout << "Choose book to delete:\n";
        for (size_t i = 0; i < searched.size(); ++i) {
            cout << i + 1 << ". ";
            searched[i]->display();
        }

        int deleteChoice;
        cin >> deleteChoice;
        cin.ignore(Limit, '\n');

        if (deleteChoice >= 1 && deleteChoice <= static_cast<int>(searched.size())) {
            book* bookToDelete = searched[deleteChoice - 1];
            auto it = find(listBook.begin(), listBook.end(), bookToDelete);
            if (it != listBook.end()) {
                listBook.erase(it);
                delete bookToDelete;
                cout << "Book deleted successfully.\n";
            } else {
                cout << "Error: Book not found in list.\n";
            }
        } else {
            cout << "Invalid choice.\n";
        }
    }
}
void sortLib()
{
    cout<<"Sort of\n";
        Menu();
    int choice;
    cin>>choice;
    cin.ignore(Limit,'\n');
    switch (choice)
    {
    case 1:
        sortbyPer();
        break;
    case 2:
        sortbyBook();
        break;
    default:
        cout << "Invalid choice.\n";
        break;
    }
}
void sortbyPer()
{
    cout<<"Sort by\n"
        << "1. ID\n"
        << "2. Name\n"
        << "3. Address\n"
        << "4. Phone Number\n"
        << "5. Member Status\n"
        << "6. Staff ID\n"
        << "7. Position\n";
    int choice;
    cin>>choice;
    switch (choice)
    {
    case 1:
        sort(listPer.begin(), listPer.end(), [](Person* a, Person* b) {
        return a->getID() < b->getID();
        });
        break;
    case 2:
        sort(listPer.begin(), listPer.end(), [](Person* a, Person* b) {
        return a->getName() < b->getName();
        });
        break;
    case 3:
        sort(listPer.begin(), listPer.end(), [](Person* a, Person* b) {
        return a->getAddress() < b->getAddress();
        });
    case 4:
        sort(listPer.begin(), listPer.end(), [](Person* a, Person* b) {
        return a->getPhoneNumber() < b->getPhoneNumber();
        });
        break;
    case 5:
        sort(listPer.begin(), listPer.end(), [](Person* a, Person* b) {
        return dynamic_cast<customer*>(a)->getMember() < dynamic_cast<customer*>(b)->getMember();
        });
        break;
    case 6:
        sort(listPer.begin(), listPer.end(), [](Person* a, Person* b) {
        return dynamic_cast<staff*>(a)->getStaffID() < dynamic_cast<staff*>(b)->getStaffID();
        });
        break;
    case 7:
        sort(listPer.begin(), listPer.end(), [](Person* a, Person* b) {
        return dynamic_cast<staff*>(a)->getPosition() < dynamic_cast<staff*>(b)->getPosition();
        });
        break;
    default:
        cout << "Invalid choice.\n";
        break;
    }
}
void sortbyBook()
{
    cout<<"Sort by\n"
        <<"1.ID\n"
        <<"2.Name\n"
        <<"3.Author\n"
        <<"4.Title\n"
        <<"5.Quantity\n";
    int choice;
    cin>>choice;
    cin.ignore(Limit,'\n');
    switch (choice)
    {
    case 1:
        sort(listBook.begin(), listBook.end(), [](book* a, book* b) {
        return a->getID() < b->getID();
        });
        break;
    case 2:
        sort(listBook.begin(), listBook.end(), [](book* a, book* b) {
        return a->getName() < b->getName();
        });
        break;
    case 3:
        sort(listBook.begin(), listBook.end(), [](book* a, book* b) {
        return a->getAuthor() < b->getAuthor();
        });
        break;
    case 4:
        sort(listBook.begin(), listBook.end(), [](book* a, book* b) {
        return a->getTitle() < b->getTitle();
        });
        break;
    case 5:
        sort(listBook.begin(), listBook.end(), [](book* a, book* b) {
        return a->getQuantity() < b->getQuantity();
        });
        break;
    default:
        cout << "Invalid choice.\n";
        break;
    }
}
void Change()override
{
    cout<<"Change for";
    Manager::Menu();
    int choice;
    cin>>choice;
    switch (choice)
    {
    case 1:
        ChangeByPerson();
        break;
    case 2:
        ChangeByBook();
        break;
    default:
        cout << "Invalid choice.\n";
        break;
    }
}
void ChangeByPerson()
{
    int personID;
        cout << "Enter the ID of the person you want to change: ";
        cin >> personID;
        cin.ignore(Limit, '\n');

        auto it = find_if(listPer.begin(), listPer.end(), [&](Person* p) { return p->getID() == personID; });
        if (it != listPer.end()) {
            cout << "Found person. Enter new details:\n";
            (*it)->input();
        } else {
            cout << "Person not found.\n";
        }
}
void ChangeByBook() {
        int bookID;
        cout << "Enter the ID of the book you want to change: ";
        cin >> bookID;
        cin.ignore(Limit, '\n');

        auto it = find_if(listBook.begin(), listBook.end(), [&](book* b) { return b->getID() == bookID; });
        if (it != listBook.end()) {
            cout << "Found book. Enter new details:\n";
            (*it)->input();
        } else {
            cout << "Book not found.\n";
        }
}   
void Borrow_books()
{
    int Price=300;
    vector<Person*> searched;
    vector<book*> searchBook1;
    Calendar Br_day;
    Calendar Pm_day;
    searchPerson(searched);
    for(auto it : searched)
    {
        for(auto it2:listPer)
            {
               if (it->getID()==it2->getID()) 
                {
                    searchBook(searchBook1);
                    for(auto itb : searchBook1)
                    {
                        for(auto itb2:listBook)
                        {
                            if(itb->getID()==itb2->getID())
                            {
                                int IDPer,IDBk;
                                IDPer=it2->getID();
                                IDBk=itb2->getID();
                                int nb= itb2->getQuantity();
                                if (nb!=0)
                                {
                                itb2->setQuantity(nb--);
                                Br_day.input();
                                Pm_day.input();
                                changer ch(IDPer,IDBk,Price,Br_day,Pm_day);
                                changerHis.push_back(ch);
                                }
                                else
                                cout<<"Out of book";
                            }
                        }
                    }
                }
            }
    }
}
float PriceBr_Bk()
{
    for(auto it:listPer)
        for(auto it2:changerHis)
            if(it->getID()==it2.getPersonID())
            {
                Calendar c;
                c.input();
                for(auto itb:listBook)
                
                if(itb->getID()==it2.getBookID())
                {
                int nb=itb->getQuantity();
                itb->setQuantity(nb++);
                int mb=dynamic_cast<customer*>(it)->getMember();
                return ((c-it2.getReturnDate())+(it2.getPaymentDate()-it2.getReturnDate()))*(mb==0?0.6:1);
                }
            }
}
};

int main() {
    library lib;
    bool running = true;
    while (running) {
        cout << "Library Manager Menu\n";
        cout << "1. Add\n"
             << "2. Delete\n"
             << "3. Change\n"
             << "4. Display All\n"
             << "5. Borrow books\n"
             << "6. Price borrow books\n"
             << "7. Search\n"
             << "8. Exit\n";
        int choice;
        cin >> choice;
        cin.ignore(Limit, '\n');
        switch (choice) {
        case 1:
            lib.Add();
            break;
        case 2:
            lib.Delete1();
            break;
        case 3:
            lib.Change();
            break;
        case 4:
            lib.displayAll();
            break;
        case 5:
            lib.Borrow_books();
            break;
        case 6:
            cout<<"Price\n";
            cout<<lib.PriceBr_Bk();
            break;
        case 7:
            cout<<"1.Book\n"
                <<"2.Person\n";
            int lib2;
            cin>>lib2;
            if(lib2==1)
            {
                vector<book*>searchbk;
                lib.searchBook(searchbk);
            }else if(lib2 =2)
            {
                vector<Person*>searchPer;
                lib.searchPerson(searchPer);
            }
            else
            cout << "Invalid choice.\n";
            break;
        case 8:
            running = false;
            break;
        default:
            cout << "Invalid choice.\n";
        }
    }
    return 0;
}
