#include "schedule_operations.h"
#include <map>
#include <string>
#include <iostream>
#include <iomanip>

// Constructor implementation for ScheduleItem
ScheduleItem::ScheduleItem(const std::string& subj, const std::string& cat, const std::string& sect,
    const std::string& comp, const std::string& sess, int un, int totEn,
    int capEn, const std::string& instr)
    : subject(subj), catalog(cat), section(sect), component(comp),
    session(sess), instructor(instr), units(un),
    totalEnrolled(totEn), capacityEnrolled(capEn) {}

// Generate a unique key for the schedule item
std::string ScheduleItem::getKey() const {
    return subject + "_" + catalog + "_" + section;
}

// Overload output operator for easy printing
std::ostream& operator<<(std::ostream& os, const ScheduleItem& item) {
    os << std::setw(8) << item.subject
        << std::setw(8) << item.catalog
        << std::setw(8) << item.section
        << std::setw(10) << item.component
        << std::setw(8) << item.session
        << std::setw(6) << item.units
        << std::setw(10) << item.totalEnrolled
        << std::setw(10) << item.capacityEnrolled
        << "  " << item.instructor;
    return os;
}

// Initialize schedule from a file
void Schedule::initSchedule(std::ifstream& file) {
    if (!file.is_open()) {
        std::cerr << "Error: Could not open file." << std::endl;
        return;
    }

    std::string line;
    std::getline(file, line); // Skip header line

    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string subject, catalog, section, component, session, instructor;
        int units, totalEnrolled, capacityEnrolled;

        // Parse the required fields
        std::getline(iss, subject, ',');
        std::getline(iss, catalog, ',');
        std::getline(iss, section, ',');
        std::getline(iss, component, ',');
        std::getline(iss, session, ',');
        iss >> units;
        iss.ignore();
        iss >> totalEnrolled;
        iss.ignore();
        iss >> capacityEnrolled;
        iss.ignore();
        std::getline(iss, instructor);

        // Create a schedule item and add it to the map
        ScheduleItem item(subject, catalog, section, component, session, units, totalEnrolled, capacityEnrolled, instructor);
        addEntry(item);
    }
}

// Add a new entry to the schedule
void Schedule::addEntry(const ScheduleItem& item) {
    scheduleMap[item.getKey()] = item;
}

// Print all schedule items
void Schedule::print() const {
    std::cout << std::setw(8) << "Subject"
        << std::setw(8) << "Catalog"
        << std::setw(8) << "Section"
        << std::setw(10) << "Component"
        << std::setw(8) << "Session"
        << std::setw(6) << "Units"
        << std::setw(10) << "TotEnrl"
        << std::setw(10) << "CapEnrl"
        << "  Instructor" << std::endl;

    for (const auto& [key, item] : scheduleMap) {
        std::cout << item << std::endl;
    }
}

// Find and print all records with a target subject
void Schedule::findBySubject(const std::string& subject) const {
    for (const auto& [key, item] : scheduleMap) {
        if (item.subject == subject) {
            std::cout << item << std::endl;
        }
    }
}

// Find and print all records with a target subject and catalog number
void Schedule::findBySubjectAndCatalog(const std::string& subject, const std::string& catalog) const {
    for (const auto& [key, item] : scheduleMap) {
        if (item.subject == subject && item.catalog == catalog) {
            std::cout << item << std::endl;
        }
    }
}

// Find and print all records with a target instructor's last name
void Schedule::findByInstructorLastName(const std::string& lastName) const {
    for (const auto& [key, item] : scheduleMap) {
        if (item.instructor.find(lastName) != std::string::npos) {
            std::cout << item << std::endl;
        }
    }
}