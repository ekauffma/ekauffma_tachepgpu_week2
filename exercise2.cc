#include <iostream>
#include <string>

// struct for TACHEP student
struct Student {
    std::string name;
    std::string email;
    std::string username;
    std::string experiment;
};

// function to print student's information
int printStudent(const Student &a) {

    // try to change value
    std::cout<<"Student Name = "<<a.name<<std::endl;
    std::cout<<"Student Email = "<<a.email<<std::endl;
    std::cout<<"Student Username = "<<a.username<<std::endl;
    std::cout<<"Student Experiment = "<<a.experiment<<std::endl;

    return 0;
}


int main() {

    // define student elliott
    Student elliott;
    elliott.name = "Elliott Kauffman";
    elliott.email = "ek8842@princeton.edu";
    elliott.username = "ekauffma";
    elliott.experiment = "CMS";

    // define student ashling
    Student ashling;
    ashling.name = "Ashling Quinn";
    ashling.email = "ashling.quinn@cern.ch";
    ashling.username = "aquinn";
    ashling.experiment = "CMS";

    // print out information for both students
    printStudent(elliott);
    std::cout<<std::endl;
    printStudent(ashling);

    return 0;
}
