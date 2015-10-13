int mySqrt(int x) {
    // Implement a binary search solution
    int start = 0;
    int end = x;
    
    int sqrt_floor = 0;
    while (start <= end) {
        int mid = start + ((end - start) >> 1);
        
        int square = mid * mid;
        // To account for square overflows:
        if (mid !=0 && square/mid != mid) {
            end = mid - 1;
            continue;
        }
        
        if (square == x) {
            return mid;
        } else if (square < x) {
            sqrt_floor = mid;
            start = mid + 1;
        } else {
            end = mid - 1;
        }
    }
    return sqrt_floor;
}
