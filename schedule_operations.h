#ifndef SCHEDULE_OPERATIONS_H
#define SCHEDULE_OPERATIONS_H

#include <map>
#include <string>
#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>

// Represents a single schedule item (row)
class ScheduleItem {
public:
    std::string subject;
    std::string catalog;
    std::string section;
    std::string component;
    std::string session;
    std::string instructor;
    int units;
    int totalEnrolled;
    int capacityEnrolled;

    // Constructor with default parameters
    ScheduleItem(const std::string& subj = "", const std::string& cat = "", const std::string& sect = "",
        const std::string& comp = "", const std::string& sess = "", int un = 0, int totEn = 0,
        int capEn = 0, const std::string& instr = "");

    // Generate a unique key for the schedule item
    std::string getKey() const;

    // Overload output operator for easy printing
    friend std::ostream& operator<<(std::ostream& os, const ScheduleItem& item);
};

// Represents the container for the schedule (multiple rows)
class Schedule {
private:
    std::map<std::string, ScheduleItem> scheduleMap; // Keyed by Subject_Catalog_Section

public:
    // Initialize schedule from a file
    void initSchedule(std::ifstream& file);

    // Add a new entry to the schedule
    void addEntry(const ScheduleItem& item);

    // Print all schedule items
    void print() const;

    // Find and print all records with a target subject
    void findBySubject(const std::string& subject) const;

    // Find and print all records with a target subject and catalog number
    void findBySubjectAndCatalog(const std::string& subject, const std::string& catalog) const;

    // Find and print all records with a target instructor's last name
    void findByInstructorLastName(const std::string& lastName) const;
};

#endif // SCHEDULE_OPERATIONS_H