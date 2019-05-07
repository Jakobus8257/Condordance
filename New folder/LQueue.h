
#pragma once
/*--- LQueue.h -------------------------------------------------------------
  This header file contains the declaration of class Queue.

  Basic operations:
	 Constructor: Constructs an empty queue
	 empty:       Checks if a queue is empty
	 enqueue:     Modifies a queue by adding a value at the back
	 front:       Accesses the front queue value; leaves queue unchanged
	 dequeue:     Modifies a queue by removing the value at the front
	 display:     Displays the queue elements from front to back
  Class Invariant:
	  1. The queue elements (if any) are stored in consecutive positions
		 in myArray, beginning at position myFront.
	  2. 0 <= myFront, myBack < QUEUE_CAPACITY
	  3. Queue's size < QUEUE_CAPACITY

  Written by:   Larry R. Nyhoff

  Written for:  Lab Manual for ADTs, Data Structures, and Problem
				Solving with C++, 2E

							   Lab #6.1
 --------------------------------------------------------------------------*/

#include <iostream>
#include <iomanip>
using namespace std;
const int QUEUE_CAPACITY = 10;
template <typename QueueElement>

class Queue {
public:
	/***** Function Members *****/
	/***** Constructor *****/
	Queue();
	const Queue(const Queue & original);
	~Queue();
	const Queue& operator=(const Queue & rightHandSide);
	bool empty() const;
	void enqueue(const QueueElement & value);
	QueueElement front() const;
	void display(ostream & out) const;
	void dequeue();

private:
	/***** Node Class *****/
	class Node {
	public:
		QueueElement data;
		Node *next;
		//---Node constructor
		Node(QueueElement value, Node * link = 0)
			/*-----------------------------------------------------------------------
			Precondition: value and link are recieved
			Postcondition: A Node has been constructed with value in its
			data part and its next part set to link (default 0).
			----------------------------------------------------------------------*/
			:data(value), next(link)
		{}
	};
	typedef Node * NodePointer;

	/******Data Members*****/
	NodePointer myBack;		//pointer to back of queue

}; // end of class declaration
template <typename QueueElement>
ostream & operator<<(ostream &out, const Queue<QueueElement> &q);

template <typename QueueElement>
Queue<QueueElement>::Queue() {
	myBack = NULL;
}
/*-----------------------------------------------------------------------
  Construct a Queue object.

  Precondition:  None.
  Postcondition: An empty Queue object has been constructed; myFront
	  and myBack are initialized to -1 and myArray is an array with
	  QUEUE_CAPACITY elements of type QueueElement.
 ----------------------------------------------------------------------*/
template <typename QueueElement>
Queue<QueueElement>::Queue(const Queue & original) {
	myBack = NULL;
	if (!original.empty()) {

		//Copy first node

		NodePointer cur = original.myBack->next;
		do {
			this->enqueue(cur->data);
			cur = cur->next;
		} while (cur != original.myBack->next);
	}
}
/*-----------------------------------------------------------------------
Copy Constructor

Precondition: original is the queue to be copied and is received as a
const reference parameter.
Postcondition: A copy of original has been constructed.
 ----------------------------------------------------------------------*/
template <typename QueueElement>
Queue<QueueElement>::~Queue() {
	while (!empty())//goes through whole list and dequeues
		dequeue();

}
/*-----------------------------------------------------------------------
Class destructor

Precondition: None.
Postcondition: The linked list in the queue has been deallocated.
----------------------------------------------------------------------*/
/**********Assignment*******/
template <typename QueueElement>
const Queue<QueueElement> & Queue<QueueElement>::operator=(const Queue<QueueElement> & rightHandSide) {
	if (this != &rightHandSide) {
		this->~Queue();

		if (rightHandSide.empty())
			myBack = NULL;
		else {
			NodePointer rhsPtr = rightHandSide.myBack->next;
			do {
				this->enqueue(rhsPtr->data);
				rhsPtr = rhsPtr->next;
			} while (rhsPtr != rightHandSide.myBack->next);
		}
	}
	return *this;
}
/*-----------------------------------------------------------------------
Assignment Operator

Precondition: rightHandSide is the queue to be assigned and is recieved
as a const reference parameter.
Postcondition: The current queue becomes a copy of rightHandSide
and a reference to it is returned
----------------------------------------------------------------------*/
template <typename QueueElement>
bool Queue<QueueElement>::empty() const
{
	return (myBack == NULL);
}

/*-----------------------------------------------------------------------
  Check if queue is empty.

  Precondition: None.
  Postcondition: True is returned if the queue is empty and false is
	  returned otherwise.
 ----------------------------------------------------------------------*/
template <typename QueueElement>
void Queue<QueueElement>::enqueue(const QueueElement & value)
{
	NodePointer newptr = new Node(value);

	if (empty()) {
		myBack = newptr;
		myBack->next = myBack;
	}
	else {
		newptr->next = myBack->next;
		myBack->next = newptr;
		myBack = newptr;
	}

}
/*-----------------------------------------------------------------------
  Add a value to a queue.

  Precondition:  value is to be added to this queue.
  Postcondition: value is added to back of queue provided there is space;
	  otherwise, a queue-full message is displayed and execution is
	  terminated.
 -----------------------------------------------------------------------*/
template <typename QueueElement>
void Queue<QueueElement>::display(ostream & out) const
{
	NodePointer ptr = myBack->next;

	do
	{
		out << showpoint << setprecision(1) << fixed << " -> " << ptr->data;

		ptr = ptr->next;

	} while (ptr != myBack->next);
}
/*-----------------------------------------------------------------------
  Output the values stored in the queue.

  Precondition:  ostream out is open.
  Postcondition: Queue's contents, from front to back, have been output
	  to out.
 -----------------------------------------------------------------------*/
template <typename QueueElement>
QueueElement Queue<QueueElement>::front() const
{
	if (!empty())
		return myBack->next->data;

	else
	{
		cerr << "*** Queue is empty -- returning garbage value ***\n";
		QueueElement garbage = 0;
		return garbage;
	}
}
/*-----------------------------------------------------------------------
  Retrieve value at front of queue (if any).

  Precondition:  Queue is nonempty.
  Postcondition: Value at front of queue is returned, unless queue is
	  empty; in that case, an error message is displayed and a "garbage
	  value" is returned.
 ----------------------------------------------------------------------*/
template <typename QueueElement>
void Queue<QueueElement>::dequeue()
{
	if (!empty()) {
		NodePointer ptr = myBack->next;//set pointer to front

		if (ptr == myBack) {
			myBack = NULL;
			delete ptr;
		}
		else {
			myBack->next = myBack->next->next;
			delete ptr;
		}

	}
	else
		cerr << "List is empty" << endl;
}
/*-----------------------------------------------------------------------
  Remove value at front of queue (if any).

  Precondition:  Queue is nonempty.
  Postcondition: Value at front of queue has been removed, unless queue
	  is empty; in that case, an error message is displayed and
	  execution is terminated.
 ----------------------------------------------------------------------*/
template <typename QueueElement>
ostream & operator<<(ostream &out, const Queue<QueueElement> &q) {
	q.display(out);
	return out;
}