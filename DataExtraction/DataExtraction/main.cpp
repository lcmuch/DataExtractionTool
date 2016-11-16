//
//  main.cpp
//

#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <stdlib.h>
using namespace std;
int min_number_each_line = 1;
int total_lines_in_one_page = 51;
vector<int> target_lines = {3, 18, 21, 24, 27, 30, 33, 51};

float checkAndReturnFloat(string input) {
  string _input = "";
  for (char x: input) {
    if (!isdigit(x) && (x != ',') && (x != '.')) {
      return INT_MIN; // error code for number not found
    } else if (x != ',')
      _input += x;
  }
  return atof(_input.c_str());
}

void readTXTFileAndGenerateOutput(int year){
  //open file named "year.txt" and generate output "output_year.txt"
  string str_year = to_string(year);
  // read file
  ifstream input_file;
  input_file.open(str_year + ".txt");
  if (!input_file.is_open()) {
    return;
  }
  // write csv file
  ofstream output_file;
  output_file.open(str_year + "_output.txt");

  string line;
  vector<vector<float>> state_output;
  vector<vector<float>> tmp_output;
  while (std::getline(input_file, line))
  {
    // split line to words
    istringstream buf(line);
    istream_iterator<string> beg(buf), end;
    vector<string> words(beg, end);


    vector<float> nums_in_a_line;
    for (int i = 0; i < words.size(); i++) {
      // ignore the first word (cannot deal with "1.")
      if (i < min_number_each_line) {
        continue;
      } else if (checkAndReturnFloat(words[i]) != INT_MIN) {
        nums_in_a_line.push_back(checkAndReturnFloat(words[i]));
      }
    }

    // ignore any lines with only one number;
    if (nums_in_a_line.size() > 1) {
      tmp_output.push_back(nums_in_a_line);
    }

    // when tmp_output has TOTAL_LINES_EVERY_PAGE lines
    // check if others in target_lines, if yes same to final output.
    if (tmp_output.size() == total_lines_in_one_page) {
      for (int i = 0; i < tmp_output.size(); i++) {
        if (find(target_lines.begin(), target_lines.end(), i + 1) != target_lines.end()) {
          state_output.push_back(tmp_output[i]);
        }
      }
      for (auto line_of_nums: state_output) {
        for (auto num: line_of_nums) {
          output_file << fixed << num << ", ";
        }
        output_file << "\n\r";
      }
      output_file << "\n\r";

      state_output.clear();
      tmp_output.clear();
    }
  }
  input_file.close();
  output_file.close();
}

int main(int argc, const char * argv[]) {
  for (int i = 2002; i <= 2009; i ++) {
    readTXTFileAndGenerateOutput(i);
  }
  total_lines_in_one_page = 69;
  target_lines = {3, 24, 27, 30, 33, 36, 39, 69};
  for (int i = 2010; i <= 2015; i ++) {
    readTXTFileAndGenerateOutput(i);
  }
  // insert code here...
  std::cout << "Hello, World!\n";
    return 0;
}
