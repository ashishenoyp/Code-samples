#include<stdio.h>

int maxProfit(int arr[], int arr_size)
{
    int buy = arr[0];
    int profit = 0;
    int i;
    for(i = 1; i < arr_size; i++)
    {	 
    	if (arr[i] < arr[i-1]) {
    	    profit += arr[i-1] - buy;
    	    buy = arr[i];
    	}					 
    }
    if (arr[arr_size - 1] > buy) {
        profit += arr[arr_size - 1] - buy;
    }
    return profit;
} 

/* Driver program to test above function */
int main()
{
    int arr[] = {100, 90, 80, 70, 60};
    int size = sizeof(arr)/sizeof(arr[0]);
    printf("Maximum profit is %d", maxDiff(arr, size));
    getchar();
    return 0;
}
