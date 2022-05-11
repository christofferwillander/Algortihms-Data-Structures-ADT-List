#include "List.h"
#include <fstream>
#include <iostream>
#include <string>
using namespace std;

const int CAP = 20;

int find(List <string> clothing[], string findElement, int nrOf);
void split(string &garment, string &prerequisite);
void readFromFile(string filename, List <string> clothing[], int &nrOf) throw (...);
void ordering(List <string> clothing[], int nrOf);

int main()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	List<string> *clothing = new List<string>[CAP];
	int nrOfClothes = 0;

	try
	{
		readFromFile("clothing.txt", clothing, nrOfClothes);
	}
	catch (const char* exep)
	{
		cout << exep << endl;
	}

	cout << "Suggested order for getting dressed:" << endl;
	ordering(clothing, nrOfClothes);

	delete[] clothing; // Deallocating memory

	getchar();
	return 0;
}

int find(List <string> clothing[], string findElement, int nrOf) // Finds elements in array of lists (based on first item in list)
{
	int foundAtIndex = -1; // Initializing to -1 - this value is also returned if not found (false)

	for (int i = 0; i < nrOf && foundAtIndex == -1; i++)
	{
		if (clothing[i].getAt(0) == findElement)
		{
			foundAtIndex = i;
		}
	}

	return foundAtIndex;
}

void split(string &garment, string &prerequisite) // Splits clothing items written on the same row
{
	int splitAt = garment.find(" "); // Find at what position the two garments are separated by a blank space - store in splitAt
	prerequisite = ""; // Emptying prerequisite string
	
	for (int i = splitAt + 1; i < (static_cast <int> (garment.length())); i++)
	{
		prerequisite += garment[i]; // Transfer the characters after blank space, character by character - store in prerequisite
	}

	garment.erase(splitAt, garment.length() - splitAt); // Remove the second garment and the blank space from string garment
}

void readFromFile(string filename, List<string> clothing[], int &nrOf) throw (...)
{
	string garment = ""; // String variable temporarily storing the garment gathered from file
	string prerequisite = ""; // String variable temporarily storing the prerequisite item (after using function split)
	
	int index = 0; // Used for storing index gathered from find function

	ifstream inFile;
	inFile.open(filename);

	if (inFile.fail()) // If file could not be found
	{
		throw "File with the specified file name was not found - please try again";
	}

	while (getline(inFile, garment)) // Reading lines from file until reaching end of file
	{
		if (garment.find(" ") < garment.length()) // If a space is present on the line (separating the two garments)
		{
			split(garment, prerequisite); // Split the two garments into two separate strings
			index = find(clothing, garment, nrOf); // Find the index where the garment is present
			clothing[index].insertAt(clothing[index].length(), prerequisite); // Insert the prerequisite item into the list of said garment
		}
		else if (garment != "") // If the garment string is not empty
		{
			clothing[nrOf++].insertAt(0, garment); // Insert the garment into its own list - at index 0
		}
	}

	inFile.close(); // Close file
}

void ordering(List<string> clothing[], int nrOf)
{
	int nrOfOrdered = 0;
	string garmentTemp = "";

	while (nrOfOrdered < nrOf) // While not all clothing items have yet been added
	{
		for (int i = 0; i < nrOf; i++)
		{
			if (clothing[i].length() == 1) // If garment has no prerequisites
			{
				nrOfOrdered++;
				cout << nrOfOrdered << ". " << clothing[i].getAt(0) << endl;
				garmentTemp = clothing[i].getAt(0); // Storing ordered garment temporarily

				for (int j = 0; j < nrOf; j++)
				{
					clothing[j].removeElement(garmentTemp); // Iterating through all lists - removing ordered garment stored in garmentTemp
				}

				garmentTemp = "";
			}
		}
	}
}
