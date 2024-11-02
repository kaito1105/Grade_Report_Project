/*
	Miyamoto, Kaito

	Project: Grade Report
	CS A250
	Fall 2023
*/

#ifndef STUDENT_H
#define STUDENT_H

#include "Course.h"

#include <string>
#include <map>

class Student
{
public:
	Student()
		: studentID(0), numberOfCourses(0), tuitionWasPaid(false) {}

	void setStudent(const Student& newStudent);
	void setStudentInfo(int setStudentID,
		const std::string& setFirstName,
		const std::string& setLastName, bool setTuitionWasPaid,
		const std::multimap<Course, char>& setCoursesCompleted);

	void addNewCourse(const std::string& coursePrefix,
		int courseNumber, int courseUnits, char courseGrade);

	int getID() const;
	std::string getFirstName() const;
	std::string getLastName() const;
	void getName(std::string& aFirstName,
		std::string& aLastName) const;
	int getNumberOfCourses() const;
	int getUnitsCompleted() const;
	std::multimap<Course, char> getCoursesCompleted() const;

	bool isTuitionPaid() const;
	bool isCourseCompleted(const std::string& coursePrefix,
		int courseNumber) const;

	double calculateGPA() const;
	double billingAmount(double tuitionRate) const;

	void printStudent() const;
	void printStudentInfo(double tuitionRate) const;

	~Student() {}

private:
	int studentID;
	std::string firstName;
	std::string lastName;
	int numberOfCourses;
	bool tuitionWasPaid;
	std::multimap<Course, char> coursesCompleted;
};
#endif