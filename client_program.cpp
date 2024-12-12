#include "schedule_operations.h"
#include <iostream>
#include <fstream>
#include <string>

void displayMenu() {
    std::cout << "\nMenu:\n";
    std::cout << "1. Print Schedule\n";
    std::cout << "2. Find by Subject\n";
    std::cout << "3. Find by Subject and Catalog\n";
    std::cout << "4. Find by Instructor's Last Name\n";
    std::cout << "5. Exit\n";
    std::cout << "Enter your choice: ";
}

int main() {
    Schedule schedule;

    // Open the input file
    std::ifstream file("STEM - Summer 2022 Schedule of Classes as of 05-02-22(1).csv");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open the file." << std::endl;
        return 1;
    }

    // Initialize schedule from the file
    schedule.initSchedule(file);
    file.close();

    int choice;
    do {
        displayMenu();
        std::cin >> choice;
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear input buffer

        switch (choice) {
        case 1: {
            std::cout << "\nFull Schedule:\n";
            schedule.print();
            break;
        }
        case 2: {
            std::string subject;
            std::cout << "Enter the subject: ";
            std::getline(std::cin, subject);
            std::cout << "\nResults for subject: " << subject << "\n";
            schedule.findBySubject(subject);
            break;
        }
        case 3: {
            std::string subject, catalog;
            std::cout << "Enter the subject: ";
            std::getline(std::cin, subject);
            std::cout << "Enter the catalog: ";
            std::getline(std::cin, catalog);
            std::cout << "\nResults for subject and catalog: " << subject << " " << catalog << "\n";
            schedule.findBySubjectAndCatalog(subject, catalog);
            break;
        }
        case 4: {
            std::string lastName;
            std::cout << "Enter the instructor's last name: ";
            std::getline(std::cin, lastName);
            std::cout << "\nResults for instructor: " << lastName << "\n";
            schedule.findByInstructorLastName(lastName);
            break;
        }
        case 5: {
            std::cout << "Exiting the program. Goodbye!" << std::endl;
            break;
        }
        default: {
            std::cout << "Invalid choice. Please try again." << std::endl;
        }
        }
    } while (choice != 5);

    return 0;
}