#include <iostream>
using namespace std;

int countSubbarry(int size, int arr[], int target) {
  int counter = 0; // init a counter to return at the end 
  for(int i = 0;i<size;i++){ //outer loop to start at the beginning at the array 
    int sum = 0; //init somethign to add j onto 
    for(int j = i;j < size; j++){ //inner loop to check if every number compare to where i is currently at 
      sum = sum + arr[j]; //adds val of j into sum continiously for example , at arr[0]; and our array is 2 4 1 2 7
                          //it would add be sum = 0 + 2 !=7
                          //then sum = 0 + 2 + 4 != 7
                          //then sum = 0 + 2 + 4 + 1 == 7
      if(sum == target){ //when it finds the sum that addes to it
        counter = counter + 1; //increment counter to retuturn after 
      }                       //after we reach the end of the inner for loop , we gone through arr[0] ,now it goes through arr[1]
                              //and does the same process 
                              // arr[i] = 4, so arr[j] also = 4 
                              //then sum = 0 + 4 != 7
                              //sum = 0 + 4 + 1 != 7
                              //goes on to find until it hits target, then do the rest of the array to return all subarray
      //a subarray is basically consecutive number inside an array 
      //so for this example of 2 4 1 2 7
      // 2 4 1 is a subaarray as it comes after one another
      //1 and 7 isnt as it is not come one after anohter
    }
  }
  return counter;
  
}

int main() {
    int size;
    cin >> size;
    
    int target;
    cin >> target;
    

    int arr[size];
    for (int i = 0; i < size; i++) {
        cin >> arr[i];
    }

    int answer = countSubbarry(size, arr, target);
    cout << answer << endl;
    return 0;
}
