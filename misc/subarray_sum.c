// --------------------------------------------
// AUTHOR: Ashish Shenoy (ashishenoyp@gmail.com)
// --------------------------------------------

// A simple program to print indices of subarray with sum as given sum
#include<stdio.h>
 
int subArraySum(int arr[], int n, int sum)
{
    int start_i = 0, curr_i = 0, curr_sum = 0;
    int found = 0;

    while (start_i < n) {
        while(curr_i < n && curr_sum < sum) {
            curr_sum += arr[curr_i];
            curr_i++;
        }
        if (curr_sum == sum) {
            printf("Found between indexes %d and %d\n", start_i, curr_i -1);
            start_i++;
            curr_i = start_i;
            curr_sum = 0;
            found = 1;
        }
        while (curr_sum > sum && start_i < n) {
            curr_sum -= arr[start_i];
            start_i++;
        }
    }

    if (! found)
        printf("No subarray found");
    return 0;
}
 
// Driver program to test above function
int main()
{
    int arr[] = {15, 2, 4, 8, 9, 5, 10, 23};
    int n = sizeof(arr)/sizeof(arr[0]);
    int sum = 15;
    subArraySum(arr, n, sum);
    return 0;
}
