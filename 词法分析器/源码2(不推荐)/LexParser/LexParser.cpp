#include "LexParser.h"

int main(int argc, char *argv[])
{
	// Start timer
	clock_t start, end;
	start = clock();
	// No arguments
	if (argc < 2)
	{
		cout << endl
			 << "Usage: LexParser <file_to_parse_name> [outfile_name]" << endl
			 << endl;

		return -1;
	}
	// Get file name
	string dir;
	dir = argv[1];

	// Create parser object
	parser myParser(dir);

	// Open parse file failed
	if (myParser.file.fail())
	{
		cout << endl
			 << "Error: File to parse open failed." << endl;
		cout << "Usage: LexParser <file_to_parse_name> [outfile_name]" << endl
			 << endl;
		return -1;
	}
	ostringstream outStream;
	outStream << "Tokens:" << endl;
	// Parse file
	outStream << myParser.parseFile();
	// Output info
	outStream << endl
			  << "Info:" << endl
			  << "Char count:  " << myParser.countChar() << endl
			  << "Line count:  "
			  << myParser.countLine() << endl;
	outStream << "Error count: "
			  << myParser.errorCount << endl;
	// Output to file
	if (argc > 2)
	{
		ofstream outFile;
		string outDir;
		// Get output file name
		outDir = argv[2];
		// Open output file
		outFile.open(outDir);
		// Open output file failed
		if (outFile.fail())
		{
			cout << endl
				 << "Error: Outfile open failed." << endl;
			cout << "Usage: LexParser <file_to_parse_name> [outfile_name]" << endl
				 << endl;
			return -1;
		}
		// End timer
		end = clock();
		// Output to file
		outFile << outStream.str() << endl
				<< "Parsing time: " << end - start << "ms" << endl;
	}
	else // Output to console
	{
		// End timer
		end = clock();
		// Output to console
		cout << outStream.str() << endl
			 << "Parsing time: " << end - start << "ms" << endl;
	}
	return 0;
}