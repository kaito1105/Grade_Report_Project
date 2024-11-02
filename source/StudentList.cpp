/*
	Miyamoto, Kaito

	Project: Grade Report
	CS A250
	Fall 2023
*/

#include "StudentList.h"

#include <iostream>
#include <fstream>
#include <iomanip>

using namespace std;

Node* StudentList::searchStudentByID(int studentID) const
{
	Node* current = first;
	while (current != nullptr)
	{
		if (current->getStudent().getID() == studentID)
		{
			return current;
		}
		current = current->getNext();
	}
	return nullptr;
}

void StudentList::addStudent(const Student& newStudent)
{
	if (count == 0)
	{
		first = new Node(newStudent, nullptr);
		last = first;
	}
	else
	{
		last->setNext(new Node(newStudent, nullptr));
		last = last->getNext();
	}
	++count;
}

void StudentList::updateStudent(const Student& updatedStudent)
{
	Node* current = first;
	bool updated = false;

	while (!updated && current != nullptr)
	{
		if (current->getStudent().getID() == updatedStudent.getID())
		{
			current->setStudent(updatedStudent);
			updated = true;
		}
		current = current->getNext();
	}
}

int StudentList::getNoOfStudents() const
{
	return count;
}

void StudentList::printStudentByID(int studentID,
	double tuitionRate) const
{
	Node* current = first;
	bool found = false;

	while (current != nullptr && !found)
	{
		if (current->getStudent().getID() == studentID)
		{
			current->getStudent().printStudentInfo(tuitionRate);
			found = true;
		}
		current = current->getNext();
	}

	if (!found)
	{
		cout << "No students with ID " << studentID
			<< " found in the list.\n" << endl;
	}
}

void StudentList::printStudentByName(const string& lastName) const
{
	Node* current = first;
	bool found = false;

	while (current != nullptr)
	{
		if (current->getStudent().getLastName() == lastName)
		{
			current->getStudent().printStudent();
			found = true;
		}

		current = current->getNext();
	}

	if (!found)
	{
		cout << "No students with last name " << lastName
			<< " is on the list.\n";
	}

	cout << endl;
}

void StudentList::printStudentsByCourse(const string& coursePrefix,
	int courseNumber) const
{
	Node* current = first;
	bool found = false;

	while (current != nullptr)
	{
		if (current->getStudent().isCourseCompleted(
			coursePrefix, courseNumber))
		{
			current->getStudent().printStudent();
			found = true;
		}
		current = current->getNext();
	}

	if (!found)
	{
		cout << "No students enrolled in " << coursePrefix
			<< " " << courseNumber << ".\n";
	}

	cout << endl;
}

void StudentList::printAllStudents(double tuitionRate) const
{
	Node* current = first;

	while (current != nullptr)
	{
		current->getStudent().printStudentInfo(tuitionRate);
		current = current->getNext();
	}
}

void StudentList::printStudentsToFile(ofstream& outfile,
	double tuitionRate) const
{
	Node* current = first;
	while (current != nullptr)
	{
		outfile << "Student Name: "
			<< current->getStudent().getLastName() << ", "
			<< current->getStudent().getFirstName() << endl
			<< "Student ID: " << current->getStudent().getID()
			<< endl
			<< "Number of courses enrolled: "
			<< current->getStudent().getNumberOfCourses()
			<< endl << endl;

		outfile << "CourseNo  Units  Grade" << endl;

		if (current->getStudent().isTuitionPaid())
		{
			for (auto& iter : current->getStudent().
				getCoursesCompleted())
			{
				outfile << iter.first.getCoursePrefix() << " "
					<< iter.first.getCourseNumber() << "    "
					<< iter.first.getCourseUnits() << "      "
					<< iter.second << endl;
			}
			outfile << "Total number of credit hours: "
				<< current->getStudent().getUnitsCompleted() << endl;

			outfile << "Current Term GPA: " << fixed
				<< setprecision(2)
				<< current->getStudent().calculateGPA() << endl;
		}
		else
		{
			for (auto& iter : current->getStudent().
				getCoursesCompleted())
			{
				outfile << iter.first.getCoursePrefix() << " "
					<< iter.first.getCourseNumber() << "    "
					<< iter.first.getCourseUnits() << "     "
					<< "***" << endl;
			}
			outfile << "Total number of credit hours: "
				<< current->getStudent().getUnitsCompleted() << endl;

			outfile << "*** Grades are being held "
				<< "for not paying the tuition. ***\n"
				<< "Amount Due: $"
				<< current->getStudent().billingAmount(tuitionRate)
				<< endl;
		}

		outfile << endl
			<< "-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-\n"
			<< endl;

		current = current->getNext();
	}
}

void StudentList::printStudentsOnHold(double tuitionRate) const
{
	bool found = false;
	Node* current = first;

	while (current != nullptr)
	{
		if (!current->getStudent().isTuitionPaid())
		{
			found = true;
			current->getStudent().printStudent();
			cout << "    Amount Due: $" << fixed << setprecision(2)
				<< current->getStudent().billingAmount(tuitionRate)
				<< endl;
		}
		current = current->getNext();
	}

	if (!found)
	{
		cout << "There are no students on hold.\n";
	}
	cout << endl;
}

void StudentList::clearStudentList()
{
	Node* current = first;
	last = nullptr;

	while (current != nullptr)
	{
		first = first->getNext();
		delete current;
		current = first;
	}
	count = 0;
}

StudentList::~StudentList()
{
	clearStudentList();
}