//hw0 Henry Pham 2285080//

#include <iostream>
#include <fstream>
#include <string>
#include "ArgumentManager.h"
#include <sstream>
using namespace std;

void flip_h(int arr[100][100], int ROW, int COL){
    for(int i = 0; i < ROW;i++){
        for(int j = 0; j < COL / 2; j++){
            int temp = arr[i][j];
            arr[i][j] = arr[i][COL - 1 - j];
            arr[i][COL - 1 - j] = temp;
        }
    }

}

void flip_v(int arr[100][100], int ROW, int COL){
    for(int i = 0; i < ROW / 2;i++){
        for(int j = 0; j < COL;j++){
            int temp = arr[i][j];
            arr[i][j] = arr[ROW - 1 - i][j];
            arr[ROW - 1 - i][j] = temp; 
        }
    }
}

void rotate_r(int arr[100][100], int &ROW, int &COL){
    int tempArr[100][100];

    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            tempArr[j][ROW - 1 -i] = arr[i][j];
        }
    }
    int newRow = COL, newCOL = ROW; 

    for(int i = 0; i < newRow;i++){
        for(int j = 0; j < newCOL;j++){
            arr[i][j] = tempArr[i][j];
        }
    }
    ROW = newRow;
    COL = newCOL;

}


int main(int argc, char* argv[]) {
    ArgumentManager am(argc, argv);

    string inputFile = am.get("input");
    string outputFile = am.get("output");

    ifstream fin(inputFile);
    ofstream fout(outputFile);

    int ROW, COL;
    fin >> ROW >> COL;

    int arr[100][100];
    for(int i = 0; i < ROW; i++){
        for(int j = 0; j < COL; j++){
            fin >> arr[i][j];
        }
    }
    
    string line;
    fin.ignore();
    getline(fin, line);

   stringstream ss(line); 
   string matrixChange;
   while(ss >> matrixChange){
    if (matrixChange == "FLIP_H"){
        flip_h(arr, ROW, COL);
    }
    else if (matrixChange == "FLIP_V"){
        flip_v(arr, ROW , COL);
    }
    else if (matrixChange == "ROTATE_R"){
        rotate_r(arr, ROW, COL);
    }
    }
    

    for(int i = 0; i < ROW;i ++){
        for(int j = 0; j < COL; j++){
            fout << arr[i][j] << " ";
        }
        if(i + 1 < ROW) fout << "\n";
    }


    return 0;
}

 