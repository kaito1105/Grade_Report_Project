/*
	Miyamoto, Kaito

	Project: Grade Report
	CS A250
	Fall 2023
*/

#ifndef COURSE_H
#define COURSE_H

#include <string>

class Course
{
public:
	Course() : courseNumber(0), courseUnits(0) {}

	void setCourseInfo(const std::string& newCoursePrefix,
		int newCourseNumber, int newCourseUnits);

	std::string getCoursePrefix() const;
	int getCourseNumber() const;
	int getCourseUnits() const;

	bool operator<(const Course& other) const;

	~Course() {}

private:
	std::string coursePrefix;
	int courseNumber;
	int courseUnits;
};
#endif