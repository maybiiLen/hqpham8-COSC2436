#include <iostream>
using namespace std;

int increasingArr(int n, int arr[]) {
    int moves = 0;
    int difference = 0;
  
    //traverse from left to right, comparing current to previous
    for (int i = 1; i < n; i++) {
      if(arr[i] < arr[i-1]){
        difference = arr[i -1] - arr[i];//get the difference
        arr[i] = arr[i-1];//checks to see which number of the pair is bigger, than raise it to that number
      }
      moves += difference;
      arr[i] = arr[i-1];//set number so whole array doesnt get modify
    }

    return moves;
}

int main() {
    int n;
    cin >> n;

    int arr[n];
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    int answer = increasingArr(n, arr);
    cout << answer << endl;
    return 0;
}
