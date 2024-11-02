/*
	Miyamoto, Kaito

	Project: Grade Report
	CS A250
	Fall 2023
*/

#include "StudentList.h"

#include <iostream>

using namespace std;

StudentList::StudentList(const StudentList& otherStudentList)
{
	if (otherStudentList.count == 0)
	{
		first = nullptr;
		last = nullptr;
		count = 0;
	}
	else
	{
		first = new Node(otherStudentList.first->getStudent(),
			nullptr);
		last = new Node(otherStudentList.last->getStudent(),
			nullptr);
		count = 0;

		Node* paramCurrent = otherStudentList.first;
		Node* callingCurrent = first;

		while (paramCurrent != otherStudentList.last)
		{
			callingCurrent->setNext(
				new Node(paramCurrent->getNext()->getStudent(),
					nullptr));
			paramCurrent = paramCurrent->getNext();
			callingCurrent = callingCurrent->getNext();
		}

		callingCurrent = last;
		count = otherStudentList.count;
	}
}

StudentList& StudentList::operator=(
	const StudentList& otherStudentList)
{
	if (&otherStudentList != this)
	{
		if (otherStudentList.count == 0)
		{
			clearStudentList();
		}
		else if (count == 0)
		{
			copyCallingObjIsEmpty(otherStudentList);
		}
		else if (count == otherStudentList.count)
		{
			copyObjectsSameLength(otherStudentList);
		}
		else if (count > otherStudentList.count)
		{
			copyCallingObjLonger(otherStudentList);
		}
		else
		{
			copyCallingObjShorter(otherStudentList);
		}
	}
	else
	{
		cerr << "Attempted assignment to itself.";
	}

	return *this;
}

void StudentList::copyCallingObjIsEmpty(
	const StudentList& otherStudentList)
{
	first = new Node(otherStudentList.first->getStudent(), nullptr);
	last = new Node(otherStudentList.last->getStudent(), nullptr);

	Node* paramCurrent = otherStudentList.first;
	Node* callingCurrent = first;

	while (paramCurrent != otherStudentList.last)
	{
		callingCurrent->setNext(new Node(
			paramCurrent->getNext()->getStudent(), nullptr));
		paramCurrent = paramCurrent->getNext();
		callingCurrent = callingCurrent->getNext();
	}

	callingCurrent = last;
	count = otherStudentList.count;
}

void StudentList::copyObjectsSameLength(
	const StudentList& otherStudentList)
{
	Node* paramCurrent = otherStudentList.first;
	Node* callingCurrent = first;

	while (paramCurrent != nullptr)
	{
		callingCurrent->setStudent(paramCurrent->getStudent());

		callingCurrent = callingCurrent->getNext();
		paramCurrent = paramCurrent->getNext();
	}
}

void StudentList::copyCallingObjLonger(
	const StudentList& otherStudentList)
{
	Node* paramCurrent = otherStudentList.first;
	Node* callingCurrent = first;

	while (paramCurrent != otherStudentList.last)
	{
		callingCurrent->setStudent(paramCurrent->getStudent());

		callingCurrent = callingCurrent->getNext();
		paramCurrent = paramCurrent->getNext();
	}

	last = callingCurrent;
	last->setStudent(paramCurrent->getStudent());

	callingCurrent = callingCurrent->getNext();
	Node* callingTemp = callingCurrent;
	last->setNext(nullptr);

	while (callingCurrent != nullptr)
	{
		callingCurrent = callingCurrent->getNext();
		delete callingTemp;
		callingTemp = callingCurrent;
	}

	count = otherStudentList.count;
}

void StudentList::copyCallingObjShorter(
	const StudentList& otherStudentList)
{
	Node* paramCurrent = otherStudentList.first;
	Node* callingCurrent = first;

	while (callingCurrent != last)
	{
		callingCurrent->setStudent(paramCurrent->getStudent());

		callingCurrent = callingCurrent->getNext();
		paramCurrent = paramCurrent->getNext();
	}

	last->setStudent(paramCurrent->getStudent());
	paramCurrent = paramCurrent->getNext();

	while (paramCurrent != nullptr)
	{
		last->setNext(new Node(paramCurrent->getStudent(), nullptr));
		last = last->getNext();

		paramCurrent = paramCurrent->getNext();
	}

	count = otherStudentList.count;
}