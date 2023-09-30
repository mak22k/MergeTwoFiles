// Capstone final project
// This lab takes inventory information from two .txt files and
// merges them into one larger, comprehensive .txt files.
// The data remains in ascending order by item ID.
// by Marisha Kulseng
// last modified 12/11/2018 at 5:00 PM

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

// function prototypes
void printBanner(ostream &os = cout);   // done
string connectFileStream(ifstream &inFile); //  done
string connectFileStream(ofstream &outFile);   // done
void mergeFiles(ifstream &inFile1, ifstream &inFile2, ostream &os = cout); // done

int main()   // done
{
	system("title CAPSTONE - Merge Sorted Files    by Marisha Kulseng");
	system("color 57");

	// variables
	string dataFile1, dataFile2, outputFileName;
	ifstream inFile1, inFile2;
	ofstream outFile;

	// wysiwyg banner
	printBanner();

	while (true)
	{
		cout << "\nPlease provide the file that contains the inventory information for"
			<< "\n\tstore #1: ";
		dataFile1 = connectFileStream(inFile1);
		//inFile1.open("s1.txt");

		cout << "Please provide the file that contains the inventory information for"
			<< "\n\tstore #2: ";
		dataFile2 = connectFileStream(inFile2);
		//inFile2.open("s2.txt");

		cout << "\n\nPlease provide the file that you want the MERGED data to go to: ";
		outputFileName = connectFileStream(outFile);
		//outFile.open("newestMerged.txt");

		cout << "\n\nYou can find the information from the files \"" << dataFile1 << "\""
			<< " and \"" << dataFile2 << "\"\n in the file \"" << outputFileName << "\".\n";

		mergeFiles(inFile1, inFile2);
		inFile1.close();
		inFile2.close();

		inFile1.open(dataFile1);
		inFile2.open(dataFile2);
		mergeFiles(inFile1, inFile2, outFile);
		// back to regularly scheduled programming

		// need to call  the merge again but this time send the output to the monitor
		inFile1.close();
		inFile2.close();
		outFile.close();
		cout << "\n\n";
		system("pause");
	}
	return 0;
}

void printBanner(ostream &os)   // done
{
	os
		<< "               Capstone - Merge Sorted Files         \n"
		<< "          Merge two short files into a third file    \n"
		<< "                   Keep the items sorted             \n"
		<< "                       by M. Kulseng                 \n\n\n";
}

string connectFileStream(ifstream &inFile)  // done
{
	string fileName;

	getline(cin >> ws, fileName);
	inFile.open(fileName);

	while (inFile.fail())
	{
		system("color b1");
		cout << "\a\tFailed to open \"" << fileName << "\" for READING the data.\n"
			<< "\tPlease make sure the file is located in the appropriate folder"
			<< " and\n\tit is not misspelled. "
			<< "\n\tDon't forget to include the filename extension: ";
		getline(cin >> ws, fileName);
		inFile.open(fileName);
	}
	system("color 57");
	return fileName;
}

string connectFileStream(ofstream &outFile)  // done
{
	string fileName;
	getline(cin >> ws, fileName);
	outFile.open(fileName);
	while (outFile.fail())
	{
		system("color b1");
		cout << "\n\tFailed to open \"" << fileName << "\" for WRITING the data.\n"
			<< "\tPlease make sure the file name does not contain illegal characters\n"
			<< "\tand it is not currently used by another application."
			<< "\n\tDon't forget to include the filename extension: ";

		getline(cin >> ws, fileName);
		outFile.open(fileName);
	}
	system("color 57");
	return fileName;
}


void mergeFiles(ifstream &inFile1, ifstream &inFile2, ostream &os)  // done
{
	string itemDesc1, itemDesc2, itemID1, itemID2;
	int itemQuant1, itemQuant2;

	// this section igmores the tile lines from the input files
	inFile1.ignore(120, '\n');
	inFile2.ignore(120, '\n');

	// reads the record from file1
	inFile1 >> itemID1 >> itemQuant1;
	getline(inFile1 >> ws, itemDesc1);

	// reads the record from file2
	inFile2 >> itemID2 >> itemQuant2;
	getline(inFile2 >> ws, itemDesc2);

	while (!inFile1.fail() && !inFile2.fail())  
	{
		if (itemID1 == itemID2)
		{
			os << "\n" << itemID1 << "\t" << setw(3) << itemQuant1 + itemQuant2 << "\t( "
				<< setw(3) << itemQuant1 << " + " << setw(3) << itemQuant2 << ")\t" << itemDesc1;

			// read the next record from file1
			inFile1 >> itemID1 >> itemQuant1;
			getline(inFile1 >> ws, itemDesc1);

			// read the next record from file2
			inFile2 >> itemID2 >> itemQuant2;
			getline(inFile2 >> ws, itemDesc2);
		}

		else if (itemID1 < itemID2)
		{
			os << "\n" << itemID1 << "\t" << setw(3) << itemQuant1 << "\t( "
				<< setw(3) << itemQuant1 << " + " << setw(3) << "NA" << ")\t" << itemDesc1;

			inFile1 >> itemID1 >> itemQuant1;
			getline(inFile1 >> ws, itemDesc1);
		}

		else if (itemID1 > itemID2)
		{
			os << "\n" << itemID2 << "\t" << setw(3) << itemQuant2 << "\t( "
				<< setw(3) << "NA" << " + " << setw(3) << itemQuant2 << ")\t" << itemDesc2;

			inFile2 >> itemID2 >> itemQuant2;
			getline(inFile2 >> ws, itemDesc2);
		}
	}
	// here see if any of them has any data left

	// to get here that means one of them has no more data
	while (!inFile1.fail())  // simplify the condition
	{
		os << "\n" << itemID1 << "\t" << setw(3) << itemQuant1 << "\t( "
			<< setw(3) << itemQuant1 << " + " << setw(3) << "NA" << ")\t" << itemDesc1;

		inFile1 >> itemID1 >> itemQuant1;
		getline(inFile1 >> ws, itemDesc1);
	}

	while (!inFile2.fail())  // simplify
	{
		os << "\n" << itemID2 << "\t" << setw(3) << itemQuant2 << "\t( "
			<< setw(3) << itemQuant2 << " + " << setw(3) << "NA" << ")\t" << itemDesc2;

		inFile2 >> itemID2 >> itemQuant2;
		getline(inFile2 >> ws, itemDesc2);
	}
}