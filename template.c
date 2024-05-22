/*
Degree: Artificial Intelligence
Subject: Fundamentals of Programming 2
Practical project: 1

Simulator - main program
*/

#include <stdio.h>
#include <stdlib.h>
#include "project1.h" // header with all data structures

//----------------------------------------------------------General
// WARNING: do not change this function
enum EventType GenerateEventType()
{
	return rand()%3;
}

void CheckArguments (int argc, char ** argv)
{
	// check the input introduced by the user
}

//----------------------------------------------------------Books
// WARNING: do not change this function
struct Book * GenerateBook()
{
	// reserve memory for a book
	struct Book * book=malloc(sizeof(struct Book));
	int bookNum=rand()%8;
	// initialize the book's fields
	strcpy (book->author, authors[bookNum]);
	strcpy (book->title, titles[bookNum]);
	int year=rand()%40+1980;
	book->year=year;
	return book;
}

// function to print a list of books
void PrintBooks()
{
	
}

// function to search for a book
struct Book * SearchBook(/*...*/)
{

}

// function to simulate a sorting of books
void SimulateSortingBooks(struct Book * book)
{

}

// function to remove a list of books at the end of the program
void RemoveSortingBooks()
{

}

//----------------------------------------------------------Stack
// WARNING: do not change this function
struct Plate * GeneratePlate()
{
	// reserve memory for a Plate
	struct Plate * plate=malloc(sizeof(struct Plate));
	// initialize the plate's fields
	enum PlateType type=rand()%3;
	enum Colors color=rand()%4;
	plate->type = type;
	plate->color = color;
	return plate;
}

// function to initialize all stacks of plates 
void InitStacks()
{

}

// function to print all stacks of different plates
void PrintPlates()
{

}

// function to remove a given stack when its MAX_CAPACITY is reached
void RemoveStack(/*...*/)
{

}

// function to simulate putting a generated plate to a corresponding stack 
void SimulateManagingPlate(struct Plate * plate)
{

}

// function to clean all stacks before the end of the program
void CleanPlateStacks()
{

}

//----------------------------------------------------------Shopping
// WARNING: do not change this function
struct Shopping * GenerateShopping()
{
	// reserve memory for a Shopping
	struct Shopping * shopping=malloc(sizeof(struct Shopping));
	// initialize the shopping's fields
	int n=rand()%5+1;
	shopping->numberThingsToBuy = n;
	nextRobotID++;
	shopping->robot_id=nextRobotID;
	return shopping;
}

// function to print a list of robots in a shopping queue
void PrintShopping()
{

}

// function to add a robot to a shopping queue
void AddToQueue(struct Shopping * shopping)
{

}

// function to remove a robot from the queue and serve it
// it may return the number of things to buy to simulate the time
int Dequeue ()
{

}

// function to simulate the time the robot is in the queue
void UpdateShopping (/*...*/)
{

}

// function to simulate a robot going for shopping
void SimulateGoForShopping(struct Shopping * shopping)
{

}

// function to clean shopping queue before the end of the program
void CleanShoppingQueue(/*...*/)
{

}

//----------------------------------------------------------main
// This is the main loop of the program. 
// It generates and consumes events.
void SimulationLoop(int EventNumbers)
{
	// declare and initialize necessary variables

	InitStacks();
	
	for (int i=0; i<EventNumbers; i++)    
	{
		// generate event type
		// depending on the generated event type:
		// event type 0: 
			// generate book 
			// Simulate sorting books
		// event type 1:
			// generate plate
			// Simulate managing plate
		// event type 2:
			// generate shopping
			// Simulate shopping
		// UpdateShopping
	}
	// CLEANING THE SIMULATION
}

int main (int argc, char ** argv)
{
	int EventNumbers;
	printf ("Starting... \n");
	CheckArguments(argc, argv);
	
	// initialize EventNumbers 

	SimulationLoop(EventNumbers);
	return 0;
}