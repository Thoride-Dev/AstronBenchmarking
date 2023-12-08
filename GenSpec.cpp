#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;

// read in spectrums.txt as a vector of vectors
std::vector<std::vector<double> > ReadSpectrums(const std::string& filename) {
    std::vector<std::vector<double> > result;
    std::ifstream file(filename);

    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            std::stringstream ss(line);
            double value;
            std::vector<double> numbers;
            char discard;
            double num;

            // Ignore '[' at the start of the line
            ss >> discard;

            // Read comma-separated numbers until ']'
            while (ss >> num) {
                numbers.push_back(num);
                ss >> discard; // Discard ',' (if any)
            }

            result.push_back(numbers);
        }
        file.close();
    }

    return result;
}

// multiply spectrums in a vector of vectors
vector<double> MultiplySpectrums(vector<vector<double> > spectrums)
{
  vector<double> result;
  result = spectrums[0];
  for (int i = 1; i < spectrums.size(); i++) {
    for (int j = 0; j < spectrums[i].size(); j++) {
      result[j] *= spectrums[i][j];
    }
  }

  return result;
}


// Program to read in a file of spectra and multiply each of them together
int main(int argc, char* argv[])
{
  if (argc != 2) {
    cout << "Usage: ./GenSpec <input file>" << endl;
    return 1;
  }

  string inputfile = argv[1];

  vector<vector<double> > spectrums = ReadSpectrums(inputfile);

  auto start = chrono::high_resolution_clock::now();
  vector<double> result = MultiplySpectrums(spectrums);
  auto stop = chrono::high_resolution_clock::now();

  // print out the result
  for (int i = 0; i < result.size(); i++) {
    cout << result[i] << " ";
  }

  // print out the time taken
  auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);

  // Convert microseconds to seconds
  double seconds = duration.count() / 1000000.0;
  cout << endl << "Time taken by function: " << seconds << " seconds" << endl;
  return 0;
}

