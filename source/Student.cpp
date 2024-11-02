/*
	Miyamoto, Kaito

	Project: Grade Report
	CS A250
	Fall 2023
*/

#include "Student.h"

#include <iostream>
#include <iomanip>

using namespace std;

void Student::setStudent(const Student& newStudent)
{
	studentID = newStudent.studentID;
	firstName = newStudent.firstName;
	lastName = newStudent.lastName;
	numberOfCourses = newStudent.numberOfCourses;
	tuitionWasPaid = newStudent.tuitionWasPaid;
	coursesCompleted = newStudent.coursesCompleted;
}

void Student::setStudentInfo(int setStudentID,
	const string& setFirstName, const string& setLastName,
	bool setTuitionWasPaid,
	const multimap<Course, char>& setCoursesCompleted)
{
	studentID = setStudentID;
	firstName = setFirstName;
	lastName = setLastName;
	numberOfCourses = static_cast<int>(setCoursesCompleted.size());
	tuitionWasPaid = setTuitionWasPaid;
	coursesCompleted = setCoursesCompleted;
}

void Student::addNewCourse(const string& coursePrefix,
	int courseNumber, int courseUnits, char courseGrade)
{
	Course newCourse;
	newCourse.setCourseInfo(coursePrefix, courseNumber, courseUnits);
	coursesCompleted.insert(make_pair(newCourse, courseGrade));
	setStudentInfo(studentID, firstName, lastName, tuitionWasPaid,
		coursesCompleted);
}

int Student::getID() const
{
	return studentID;
}

string Student::getFirstName() const
{
	return firstName;
}

string Student::getLastName() const
{
	return lastName;
}

void Student::getName(string& aFirstName, string& aLastName) const
{
	aFirstName = firstName;
	aLastName = lastName;
}

int Student::getNumberOfCourses() const
{
	return numberOfCourses;
}

int Student::getUnitsCompleted() const
{
	int totalNumberOfUnits = 0;

	for (auto& key : coursesCompleted)
	{
		totalNumberOfUnits += key.first.getCourseUnits();
	}

	return totalNumberOfUnits;
}

multimap<Course, char> Student::getCoursesCompleted() const
{
	return coursesCompleted;
}

bool Student::isTuitionPaid() const
{
	return tuitionWasPaid;
}

bool Student::isCourseCompleted(const string& coursePrefix,
	int courseNumber) const
{
	if (numberOfCourses > 0)
	{
		auto iter = coursesCompleted.begin();

		while (iter != coursesCompleted.end())
		{
			if (iter->first.getCoursePrefix() == coursePrefix &&
				iter->first.getCourseNumber() == courseNumber)
			{
				return true;
			}
			++iter;
		}
	}

	return false;
}

double Student::calculateGPA() const
{
	double sumOfGPA = 0.0;
	double totalUnits = 0.0;

	for (auto& key : coursesCompleted)
	{
		double eachGPA = 0.0;

		if (key.second == 'A') { eachGPA = 4.0; }
		else if (key.second == 'B') { eachGPA = 3.0; }
		else if (key.second == 'C') { eachGPA = 2.0; }
		else if (key.second == 'D') { eachGPA = 1.0; }

		sumOfGPA = sumOfGPA + (eachGPA * key.first.getCourseUnits());
		totalUnits += key.first.getCourseUnits();
	}

	return sumOfGPA / totalUnits;
}

double Student::billingAmount(double tuitionRate) const
{
	return numberOfCourses * tuitionRate;
}

void Student::printStudent() const
{
	cout << studentID << " - " << lastName << ", " << firstName
		<< endl;
}

void Student::printStudentInfo(double tuitionRate) const
{
	cout << "Student Name: " << lastName << ", " << firstName << endl
		<< "Student ID: " << studentID << endl
		<< "Number of courses completed: " << getNumberOfCourses()
		<< endl << endl;

	auto iter = coursesCompleted.begin();
	cout << "CourseNo  Units  Grade" << endl;
	while (iter != coursesCompleted.end())
	{
		string coursePrefix = iter->first.getCoursePrefix();
		cout << coursePrefix;
		if (coursePrefix.size() == 4)
		{
			 cout << " ";
		}
		else
		{
			for (int i = coursePrefix.size(); i < 5; ++i)
			{
				cout << " ";
			}
		}
		cout << iter->first.getCourseNumber() << "    "
			<< iter->first.getCourseUnits() << "      "
			<< iter->second << endl;
		++iter;
	}

	cout << "\nTotal number of credit hours: "
		<< getUnitsCompleted() << endl;

	if (isTuitionPaid())
	{
		cout << "Current Term GPA: " << fixed << setprecision(2)
			<< calculateGPA() << endl;
	}
	else
	{
		cout << "*** "
			<< "Grades are being held for not paying the tuition. "
			<< "***\n"
			<< "Amount Due: $" << billingAmount(tuitionRate) << endl;
	}

	cout
		<< "\n-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n\n";
}