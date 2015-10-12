#include<stdio.h>

/* Function to get index of floor and ceiling of x in arr[l..r] */
void func(int *arr, int l, int r, int x, int *floor, int *ceil) {
    if (l <= r) {
        int mid = (l + r)/ 2;
        if (arr[mid] == x ) {
            *floor = arr[mid];
            *ceil = arr[mid];
        } else if (arr[mid] < x) {
            *floor = arr[mid];
            func(arr, mid +1, r, x, floor, ceil);
        } else {
            *ceil = arr[mid];
            func(arr, l, mid -1, x, floor, ceil);
        }
    } 
}		 


/* Driver program to check above functions */
int main()
{
    int arr[] = {1, 2, 8, 10, 10, 12, 19};
    int n = sizeof(arr)/sizeof(arr[0]);
    int x = 0;
    int floor = -1;
    int ceil = -1;
    func(arr, 0, n-1, x, &floor, &ceil);
    if(floor == -1 && ceil == -1)
    	printf("floor & ceil of %d doesn't exist in array ", x);
    else if (floor == -1) 
        printf("ceiling: %d; floor doesn't exist", ceil);
    else if (ceil == -1)
        printf("floor: %d; ceiling doesn't exist", floor);
    else 
    	printf("floor: %d ceiling: %d\n", floor, ceil);
    getchar();
    return 0;
}
