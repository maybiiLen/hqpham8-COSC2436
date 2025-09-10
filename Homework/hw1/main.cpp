#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "ArgumentManager.h"
using namespace std;

class DynamicArray{
private:
    int* data;
    int size;

public:
    DynamicArray(int arraySize){
        size = arraySize;
        data = new int[size];
        for(int i = 0; i < size; i++){
            data[i] = 0;
        }
    }
    ~DynamicArray(){
        delete[] data;
    }

    void setData(int index, int value) {
        if(index >= 0 && index < size) {
            data[index] = value;
        }
    }

    int addNums(int index) {
        //base case
        if(index >= size || index < 0){
            return 0;
        }
        if(index == 0){
            return 0;
        }
        //return current index value + recalls smaller version until it returns 0, then adds back up
        //for example if addNums(3) arr[1,4,2,6]
        //return data[index - 1] = 6 + addnums(index - 1) or addnums(2) and it goes until it reach base case 0;
        return data[index - 1] + addNums(index - 1);
    }

    bool findNum(int target, int index = 0){
        //base case 
        //if index is being added from 0 till size(the end) means we check through all the array
        if(index == size){
            return false;
        }
        //if the data in THIS index matches the target, return true because we found the value in the array
        if(data[index] == target){
            return true;
        }
        //added index parameter to go through dynamic array
        //return findNum function + 1 index, until we find a match
        return findNum(target, index + 1);
    }

    void replace(int value, int newValue, int index = 0){
        //base case
        if(index == size || index < 0){
            return;
        }
        //check if the current data matches the value, then replace the data in curr with newValue;
        if(data[index] == value){
            data[index] = newValue;
        }
        //calls the function with the same value while traversing through the dynamicArray with index + 1;
        replace(value, newValue, index + 1);
    }

    bool isSorted(int index = 0){
        //base case
        //if we check through all the pairs in the array and havent return false, mean its sorted
        if(index >= size - 1 || size <= 1){
            return true;
        }
        //checks the current data compare to the data of the index next to it, 
        //if its greater than, mean the array isnt sorted in ascending order
        //for example if data[i] = 2 and data[i] = 1; then the array looks like [2,1,?,?,?]
        //from this we know that it isnt sorted because 2 came before 1, but isnt less than, so return false bc its not sorted
        if(data[index] > data[index + 1]){
            return false;
        }
        //calls the functions and traverse with index + 1 until we either hit our base case, our we find its false 
        return isSorted(index + 1);
    }

    void print(ostream& out = cout, int index = 0){
        //base 
        //we hit the end of the array and can return while printing an endl;
        if(index == size){
            out << endl;
            return;
        }
        //prints out the current data at this index
        out << data[index];

        //prints a comment for every value until we hit the last num
        if(index < size - 1){
            out << ", ";
        }
        //traverse through the array with index + 1 and prints the data everytime
        //we traverse, but when we hit base case we stop
        print(out, index + 1);
    }
};


int main(int argc, char* argv[]) {
    ArgumentManager am(argc, argv);

    string inputFile = am.get("input");
    string commandFile = am.get("command");
    string outputFile = am.get("output");

    ifstream fin(inputFile);
    ifstream fcmd(commandFile);
    ofstream fout(outputFile);

    //test case to see if files can be open
    if(!fin.is_open() || !fout.is_open() || !fcmd.is_open()){
        return 1;
    }
    
    //read first number of the input file and set that to size
    // read size
    int arrSize;
    fin >> arrSize;
    DynamicArray* arr = new DynamicArray(arrSize);

    // read the rest of the numbers across lines, handle commas
    int idx = 0;
    string token;
    while (idx < arrSize && fin >> token) {
        // strip trailing comma if present
        if (!token.empty() && token.back() == ',') {
            token.pop_back();
        }
        if (!token.empty()) {
            arr->setData(idx++, stoi(token));
        }
    }


 
    string commandLine;
    while (getline(fcmd, commandLine)) {
        if (!commandLine.empty() && commandLine.back() == '\r') commandLine.pop_back();
        if(commandLine.empty()) continue;

        if (commandLine.find("AddNums(") != string::npos) {
            // find the number inside the parentheses
            int start = commandLine.find('(') + 1;
            int end = commandLine.find(')');
            int index = stoi(commandLine.substr(start, end - start));
            
            if(index >= arrSize || index < 0){
                fout << "Invalid index" << endl;
            } else {
                fout << arr->addNums(index) << endl;
            }
        }
        else if (commandLine.find("FindNum(") != string::npos) {
            // find the number inside the parentheses
            int start = commandLine.find('(') + 1;
            int end = commandLine.find(')');
            int target = stoi(commandLine.substr(start, end - start));
            fout << (arr->findNum(target) ? "true" : "false") << endl;
        }
        else if (commandLine.find("Replace(") != string::npos) {
            // find the two numbers separated by comma
            int start = commandLine.find('(') + 1;
            int comma = commandLine.find(',');
            int end = commandLine.find(')');
            
            int value = stoi(commandLine.substr(start, comma - start));
            int newValue = stoi(commandLine.substr(comma + 1, end - comma - 1));
            
            if(!arr->findNum(value)){
                fout << "(" << value << ") is not in the array" << endl;
            } else {
                arr->replace(value, newValue);
            }
        }
        else if (commandLine.find("IsSorted") != string::npos) {
            fout << (arr->isSorted() ? "true" : "false") << endl;
        }
        else if (commandLine.find("Print") != string::npos) {
            arr->print(fout);
        }
    }

    delete arr;
    fin.close();
    fcmd.close();
    fout.close();

    return 0;
}