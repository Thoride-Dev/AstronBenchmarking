#include <iostream>
#include <string>


using namespace std;

// Program to read in a file of spectra and multiply each of them together

int main(int argc, char* argv[])
{
  if (argc != 3) {
    cout << "Usage: GenSpec <input file> <output file>" << endl;
    return 1;
  }

  string inputfile = argv[1];
  string outputfile = argv[2];

  cout << "Input file: " << inputfile << endl;
  cout << "Output file: " << outputfile << endl;

  return 0;
}