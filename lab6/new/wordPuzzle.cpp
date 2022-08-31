#include <iostream>
#include <fstream>
#include <string>
#include <bits/stdc++.h>
#include "HashTable.h"
#include "timer.cpp"
#include <math.h>
//Liam Tolbert, lct4am, 10/18/2021,wordPuzzle.cpp
using namespace std;

char grid[500][500];

bool readInGrid(string filename, int& rows, int& cols);
string getWordInGrid(int startRow, int startCol, int dir, int len,
                     int numRows, int numCols, HashTable dictionary);

int main(int argc, char* argv[]){
  timer t;
  t.start();
  string dictionaryFilename = argv[1];
  string gridFilename = argv[2];

  string data;
  
  HashTable dictionary(33529);// prime number much larger than the capacity of the dictionary with a load factor of 0.75
  ifstream dictionaryFile(dictionaryFilename);
  
  if(!dictionaryFile.is_open()){
    cout << "Error!" << endl;
    return 0;
  }

  while(getline(dictionaryFile, data)){
    dictionary.insert(data);
  }
  dictionaryFile.close();

  int rows, cols;
  
  if(!readInGrid(gridFilename, rows, cols)){
    return 0;
  }

  int count = 0;
  string output, dir = "";
  for(int i = 0; i < rows; i++){
    for(int j = 0; j < cols; j++){
      for (int k = 0; k < 8; k++) {
	for(int l = 3; l < 23; l++){
	  output = getWordInGrid(i, j, k, l, rows, cols, dictionary);
	  if(output.length() == l && output != ""){
	    count++;
	    switch (k) {
	    case 0:
	      dir = "N";
	      break; // north
	    case 1:
	      dir = "NE";
	      break; // north-east
	    case 2:
	      dir = "E";
	      break; // east
	    case 3:
	      dir = "SE";
	      break; // south-east
	    case 4:
	      dir = "S";
	      break; // south
	    case 5:
	      dir = "SW";
	      break; // south-west
	    case 6:
	      dir = "W";
	      break; // west
	    case 7:
	      dir = "NW";
	      break; // north-west
	  }
	    cout << dir << "(" << i << ", " << j << "): " << output << endl;
	  }
	}
      }
    }
  }
  cout << count << " words found" << endl;
  t.stop();
  //cout << (int)(t.getTime()*1000) << endl;
}

/** This function will read in a grid file, as per the format in the
 * CS 2150 lab 6 document, into a global grid[][] array.  It uses C++
 * file streams, and thus requires the the <fstream> #include header.
 *
 * @return true or false, depending on whether the file was
 *         successfully opened.
 * @param filename The file name to read in -- it's assumed to be in
 *                 the file format described in the lab document.
 * @param rows The number of rows as specified in the input file;
 *             as this is a reference, it is set by the function.
 * @param cols The number of columns as specified in the input file;
 *             as this is a reference, it is set by the function.
 */
bool readInGrid(string filename, int& rows, int& cols) {
    // try to open the file
    ifstream file(filename);
    // upon an error, return false
    if (!file.is_open()) {
        return false;
    }

    file >> rows;
    file >> cols;
    
    // and finally the grid itself
    string data;
    file >> data;

    // close the file
    file.close();

    // convert the string read in to the 2-D grid format into the
    // grid[][] array.
    // In the process, we'll print the grid to the screen as well.
    int pos = 0; // the current position in the input data
    for (int r = 0; r < rows; r++) {
        for (int c = 0; c < cols; c++) {
            grid[r][c] = data[pos++];
        }
    }
    return true;
}

/** This function will retrieve a word in a grid of letters in a given
 * direction.  If the end of the grid is encountered before the length
 * of the desired string is reached, then a shorter string will be
 * returned.  The data is retrieved from a global char grid[][]
 * array, which is assumed to be defined (and in scope).  NOTE: The
 * return value is a static string variable (for efficiency
 * reasons), so a successive return value will overwrite a previous
 * return value.
 *
 * @return A STATIC string containing the letters in the provided direction.
 * @param startRow The starting (row,col) position to find the word.
 * @param startCol The starting (row,col) position to find the word.
 * @param dir The direction to move: 0 is north (upwards), 1 is
 *            northeast, and it rotates around clockwise until it
 *            reaches 7 for northwest.
 * @param len The desired length of the string to return (assuming
 *            the edge of the grid is not reached--if the edge of the
 *            grid is reached, it will return as many characters as
 *            possible up to the edge of the grid, so the returned
 *            string may not have the same length as this parameter
 *            indicates).
 * @param numRows The number of rows in the global char grid[][]
 *                array.
 * @param numCols The number of columns in the global char grid[][]
 *                array.
 */
string getWordInGrid (int startRow, int startCol, int dir, int len,
                      int numRows, int numCols, HashTable dictionary) {
    // the static-ness of this variable prevents it from being
    // re-declared upon each function invocation.  It also prevents it
    // from being deallocated between invocations.  It's probably not
    // good programming practice, but it's an efficient means to return
    // a value.
    static string output;
    output.clear(); // Since it's static we need to clear it
    output.reserve(256); // Can't set capacity in the constructor so do it the first time here

    // the position in the output array, the current row, and the
    // current column
    int r = startRow, c = startCol;
    // iterate once for each character in the output
    for (int i = 0; i < len; i++) {
        // if the current row or column is out of bounds, then break
        if (c >= numCols || r >= numRows || r < 0 || c < 0) {
            break;
        }

        // set the next character in the output array to the next letter
        // in the grid
        output += grid[r][c];

        // move in the direction specified by the parameter
        switch (dir) { // assumes grid[0][0] is in the upper-left
            case 0:
                r--;
                break; // north
            case 1:
                r--;
                c++;
                break; // north-east
            case 2:
                c++;
                break; // east
            case 3:
                r++;
                c++;
                break; // south-east
            case 4:
                r++;
                break; // south
            case 5:
                r++;
                c--;
                break; // south-west
            case 6:
                c--;
                break; // west
            case 7:
                r--;
                c--;
                break; // north-west
        }
    }
    if(dictionary.contains(output) && output.length() >= 3){
      return output;
    }
    return "";
}


