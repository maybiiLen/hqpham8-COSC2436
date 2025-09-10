//hqpham8 2285080 9/10/2025 Removing Digits.cpp

#include <iostream>
#include <string>
using namespace std;

int main() {
    int n;
    cin >> n;
    
    int counter = 0;
    
    //base case to return if number is negative
    if(n <= 0){
      return -1;
    }
    
    while(n > 0){
        //inint max digit 
        int maxDigit = 0;
        int temp = n;//set it again after every loop
        
        
        //use to find the greatest number in each digit 
        while (temp > 0) {
            int digit = temp % 10;  //this gets the last digit of the number , so if number is 153, it gets 3
            if(digit > maxDigit){ //if the digit is bigger, store that into max digit
              maxDigit = digit;
            }
            temp = temp / 10; //finds the next digit so 153/10 would give us 15, then you can go back up and find % of that
        }
        
        n = n - maxDigit; // subtract from max digit 
        counter += 1;//keep tracks of how many time we went to loop until we hit reach 0;
    }
    
    cout << counter << endl;
    return 0;
}
