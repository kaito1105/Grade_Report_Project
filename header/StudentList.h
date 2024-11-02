/*
	Miyamoto, Kaito

	Project: Grade Report
	CS A250
	Fall 2023
*/

#ifndef STUDENTLIST_H
#define STUDENTLIST_H

#include "Student.h"

#include <string>

class Node
{
public:
	Node() : next(nullptr) {}
	Node(Student newStudent, Node* newNext)
		: student(newStudent), next(newNext) {}
	Node* getNext() const { return next; }
	Student& getStudent() { return student; }
	void setNext(Node* newNext) { next = newNext; }
	void setStudent(Student newStudent) { student = newStudent; }
	~Node() {}
private:
	Student student;
	Node* next;
};

class StudentList
{
public:
	StudentList() : first(nullptr), last(nullptr), count(0) {}
	StudentList(const StudentList& otherStudentList);

	StudentList& operator=(const StudentList& otherStudentList);

	Node* searchStudentByID(int studentID) const;

	void addStudent(const Student& newStudent);
	void updateStudent(const Student& updatedStudent);

	int getNoOfStudents() const;

	void printStudentByID(int studentID, double tuitionRate) const;
	void printStudentByName(const std::string& lastName) const;
	void printStudentsByCourse(const std::string& coursePrefix,
		int courseNumber) const;
	void printAllStudents(double tuitionRate) const;
	void printStudentsToFile(std::ofstream& outfile,
		double tuitionRate) const;
	void printStudentsOnHold(double tuitionRate) const;

	void clearStudentList();

	~StudentList();

private:
	Node* first;
	Node* last;
	int count;

	void copyCallingObjIsEmpty(const StudentList& otherStudentList);
	void copyObjectsSameLength(const StudentList& otherStudentList);
	void copyCallingObjLonger(const StudentList& otherStudentList);
	void copyCallingObjShorter(const StudentList& otherStudentList);
};
#endif