#include <iostream>
#include <string>
using namespace std;

class Person {
protected:
    string name;
public:
    Person(string n) : name(n) {}
    void display() { cout << "Name: " << name << endl; }
};

class Employee : public Person {
    int id;
    char pCode;
public:
    Employee(string n, char person, int i) : Person(n), id(i), pCode(person) {}
    void display() {
        cout << "Employee Name: " << name << ", ID: " << id << ", Project Code: " << pCode << endl;
    }
};

class Project {
    char code;
public:
    Project(char c) : code(c) {}
    void display() { cout << "Project Code: " << code << endl; }
};

int main() {
    Person Person("Alice");
    Employee employee("Bob", 'A', 101);
    Project project('X');

    Person.display();
    employee.display();
    project.display();

    return 0;
}
