class Solution {
public:
    int maxProfit(vector<int>& prices) {
        int size = (int)prices.size();
        if(size < 2) return 0;
        int minPrice = prices[0];
        int maxProfit = 0;

        for (int i = 0; i < size ; i++) {
            if(prices[i] < minPrice){
                minPrice = prices[i]; 
            }
            else{
                int profit = prices[i] - minPrice;
                if(profit > maxProfit){
                    maxProfit = profit;
                }
            }
        }
        return maxProfit;
    }
};
#include <vector>
using namespace std;