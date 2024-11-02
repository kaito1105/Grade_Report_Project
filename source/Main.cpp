/*
	Miyamoto, Kaito

	Project: Grade Report
	CS A250
	Fall 2023
*/

#include "StudentList.h"
#include "InputHandler.h"
#include "OutputHandler.h"

#include <iostream>

using namespace std;

const string FILENAME = "student_data.txt";

void displayMenu();
void processChoice(StudentList& studentList, double& tuitionRate);

int main()
{
	StudentList studentList;
	double tuitionRate = 0.0;
	readStudentData(FILENAME, studentList, tuitionRate);
	processChoice(studentList, tuitionRate);

	return 0;
}

void displayMenu()
{
	cout << "\n*** MAIN MENU ***\n\n"
		<< "Select one of the following:\n\n"
		<< "    1: Print all students\n"
		<< "    2: Print student information\n"
		<< "    3: Search student by last name\n"
		<< "    4: Print students by course\n"
		<< "    5: Print students on hold\n"
		<< "    6: Print students to file\n"
		<< "    7: Add new course for students\n"
		<< "    8: To exit\n\n";
}

void processChoice(StudentList& studentList, double& tuitionRate)
{
	string choice;
	int id = 0;
	string firstName;
	string lastName;
	string coursePrefix;
	int courseNumber = 0;

	do
	{
		displayMenu();
		cout << "Enter your choice: ";
		cin >> choice;
		cout << endl;

		if (choice == "1")
		{
			studentList.printAllStudents(tuitionRate);
		}
		else if (choice == "2")
		{
			cout << "Please enter student's ID: ";
			cin >> id;
			cout << endl;
			studentList.printStudentByID(id, tuitionRate);
		}
		else if (choice == "3")
		{
			cout << "Please enter the student's last name: ";
			cin >> lastName;
			cout << endl;
			studentList.printStudentByName(lastName);
		}
		else if (choice == "4")
		{
			cout << "Please enter the course prefix: ";
			cin >> coursePrefix;
			cout << "Please enter the course number: ";
			cin >> courseNumber;
			cout << endl;
			studentList.printStudentsByCourse(coursePrefix,
				courseNumber);
		}
		else if (choice == "5")
		{
			studentList.printStudentsOnHold(tuitionRate);
		}
		else if (choice == "6")
		{
			printAllStudentsToFile(studentList, tuitionRate);
			cout << endl;
		}
		else if (choice == "7")
		{
			cout << "Please enter student's ID: ";
			cin >> id;

			Node* temp = studentList.searchStudentByID(id);
			if (temp == nullptr)
			{
				cout << "\nNo students with ID " << id
					<< " found in the list.\n\n";
			}
			else
			{
				cout << "Please enter the student's first name: ";
				cin >> firstName;
				cout << "Please enter the student's last name: ";
				cin >> lastName;
				cout << endl;

				if (temp->getStudent().getFirstName() == firstName &&
					temp->getStudent().getLastName() == lastName)
				{
					cout << "Please enter the course prefix: ";
					cin >> coursePrefix;
					cout << "Please enter the course number: ";
					cin >> courseNumber;
					cout << "Please enter the course units: ";
					int courseUnits = 0;
					cin >> courseUnits;
					cout << "Please enter the course grade: ";
					char courseGrade = 'N';
					cin >> courseGrade;

					temp->getStudent().addNewCourse(coursePrefix,
						courseNumber, courseUnits, courseGrade);
					studentList.updateStudent(temp->getStudent());
					cout << endl;
				}
				else
				{
					cout << "No students with " << firstName << " "
						<< lastName << " matches ID " << id 
						<< ".\n\n";
				}
			}
		}
		else if (choice == "8")
		{
			cout << "Thank you for using the OCC Gradebook. "
				<< "Good-bye!\n\n";
		}
		else
		{
			cout << "Sorry. That is not a selection.\n\n";
		}

		system("Pause");

	} while (choice != "8");
}