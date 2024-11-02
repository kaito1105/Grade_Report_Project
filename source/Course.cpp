/*
	Miyamoto, Kaito

	Project: Grade Report
	CS A250
	Fall 2023
*/

#include "Course.h"

using namespace std;

void Course::setCourseInfo(const string& newCoursePrefix,
	int newCourseNumber, int newCourseUnits)
{
	coursePrefix = newCoursePrefix;
	courseNumber = newCourseNumber;
	courseUnits = newCourseUnits;
}

string Course::getCoursePrefix() const
{
	return coursePrefix;
}

int Course::getCourseNumber() const
{
	return courseNumber;
}

int Course::getCourseUnits() const
{
	return courseUnits;
}

bool Course::operator<(const Course& other) const
{
	if (coursePrefix == other.coursePrefix)
	{
		return courseNumber < other.courseNumber;
	}
	else
	{
		return coursePrefix < other.coursePrefix;
	}
}