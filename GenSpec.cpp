#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <chrono>

using namespace std;

// read in spectrums.txt as a vector of vectors
vector<vector<double> > ReadSpectrums(const string& filename) {
    vector<vector<double> > result;
    ifstream file(filename);

    if (file.is_open()) {
        string line;
        while (getline(file, line)) {
            stringstream ss(line);
            double value;
            vector<double> numbers;
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

// multiply spectrums in a vector of vectors which are dynamically allocated
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

// multiply spectrums in a vector of vectors where the vectors are const to avoid copying
vector<double> MultiplySpectrumsConst(const vector<vector<double> >& spectrums) {
    const size_t size = spectrums[0].size();
    vector<double> result = spectrums[0];

    for (size_t i = 1; i < spectrums.size(); ++i) {
        const vector<double>& spectrum = spectrums[i];
        for (size_t j = 0; j < size; ++j) {
            result[j] *= spectrum[j];
        }
    }

    return result;
}

// multiply spectrums in a vector of vectors in place to avoid copying
void MultiplySpectrumsInPlace(vector<vector<double> >& spectrums, vector<double>& result) {
    const size_t size = spectrums[0].size();

    for (size_t i = 1; i < spectrums.size(); ++i) {
        const vector<double>& spectrum = spectrums[i];
        for (size_t j = 0; j < size; ++j) {
            result[j] *= spectrum[j];
        }
    }
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

  auto start_const = chrono::high_resolution_clock::now();
  vector<double> result_const = MultiplySpectrumsConst(spectrums);
  auto stop_const = chrono::high_resolution_clock::now();

  auto start_inplace = chrono::high_resolution_clock::now();
  vector<double> result_inplace = spectrums[0];
  MultiplySpectrumsInPlace(spectrums, result);
  auto stop_inplace = chrono::high_resolution_clock::now();

  // print out the result
  for (int i = 0; i < result.size(); i++) {
    cout << result[i] << " ";
  }

  // print out the time taken
  auto duration = chrono::duration_cast<chrono::microseconds>(stop - start);
  auto duration_const = chrono::duration_cast<chrono::microseconds>(stop_const - start_const);
  auto duration_inplace = chrono::duration_cast<chrono::microseconds>(stop_inplace - start_inplace);

  // Convert microseconds to seconds
  double seconds = duration.count() / 1000000.0;
  double seconds_const = duration_const.count() / 1000000.0;
  double seconds_inplace = duration_inplace.count() / 1000000.0;

  cout << endl << "Time taken by function: " << seconds << " seconds" << endl;
  cout << "Time taken by function (const): " << seconds_const << " seconds" << endl;
  cout << "Time taken by function (inplace): " << seconds_inplace << " seconds" << endl;
  return 0;
}

