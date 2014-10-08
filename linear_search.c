#include <stdio.h>

// --------------------------------------------
// AUTHOR: Ashish Shenoy (ashishenoyp@gmail.com)
// --------------------------------------------

typedef enum {
    LessThan = 0,
    LessThanEquals = 1,
    Equals = 2,
    GreaterThanEquals = 3,
    GreaterThan = 4
} SearchType;

typedef enum {
    NotFound = 0,
    FoundExact = 1,
    FoundGreater = 2,
    FoundLess = 3
} SearchResult;

char *search_type_chars[5] = {
    "LessThan",
    "LessThanEquals",
    "Equals",
    "GreaterThanEquals",
    "GreaterThan"
};

char *search_result_chars[4] = {
    "NotFound",
    "FoundExact",
    "FoundGreater",
    "FoundLess"
};

// Linear Search API:
// Assumptions --------------
// - The items are sorted
// - Items will be non-NULL
// - There are no duplicate items
// - n_items will be > 0
SearchResult Search(
    const int *items, 
    const int n_items, 
    const int ascending, 
    const int key, 
    const SearchType search_type,
    int * const ret_index)
{
    // Input param checks
    if (!items || n_items == 0) {
        return NotFound;
    }

    // Set the loop constraints based on whether its ascending/descending
    int curr_index, end, step_by;
    if (ascending) {
        curr_index = 0;
        end = n_items;
        step_by = 1;
    } else {
        curr_index = n_items-1;
        end = -1;
        step_by = -1;
    }

    int found_less = 0;
    while (curr_index != end) {
        switch (search_type) {
            case LessThan:
                if (items[curr_index] < key) {
                    *ret_index = curr_index;
                    found_less = 1;
                }
                break;

            case LessThanEquals:
                if (items[curr_index] == key) {
                    *ret_index = curr_index;
                    return FoundExact;
                } else if (items[curr_index] < key) {
                    *ret_index = curr_index;
                    found_less = 1;
                }
                break;

            case Equals:
                if (items[curr_index] == key) {
                    *ret_index = curr_index;
                    return FoundExact;
                }
                break;

            case GreaterThanEquals:
                if (items[curr_index] == key) {
                    *ret_index = curr_index;
                    return FoundExact;
                } else if (items[curr_index] > key) {
                    *ret_index = curr_index;
                    return FoundGreater;
                }
                break;

            case GreaterThan:
                if (items[curr_index] > key) {
                    *ret_index = curr_index;
                    return FoundGreater;
                }
                break;

            default:
                return NotFound;
                break;
        }
        curr_index += step_by;
    }

    if (found_less) {
        return FoundLess;
    }
    return NotFound;
}

// -----------------------------------------------------------------------------------------
// Helper functions for unit tests
int run_test_case(
    const int * items,
    const int n_items,
    const int ascending,
    const int key,
    const SearchType type,
    const SearchResult expected_result)
{
    SearchResult search_result;
    int ret_index;
    int error = 0;

    search_result = Search(items, n_items, ascending, key, type, &ret_index);

    // Check the return type to see if it matches expectations
    if (search_result != expected_result)
    {
        error = 1;
    } else { 
        // double check if the result makes sense
        if (search_result != NotFound) {
            switch (type) {
                case LessThan:
                    if (!(items[ret_index] < key)) 
                        error = 1;
                    break;
                case LessThanEquals:
                    if (!(items[ret_index] <= key)) 
                        error = 1;
                    break;
                case Equals:
                    if (!(items[ret_index] == key)) 
                        error = 1; 
                    break;
                case GreaterThan:
                    if (!(items[ret_index] > key)) 
                        error = 1;
                    break;
                case GreaterThanEquals:
                    if (!(items[ret_index] >= key)) 
                        error = 1;
                    break;
                default:
                    error = 1;
            }
        }
    }

    if (error) {
        char *ascending_str = (ascending != 0) ? "True" : "False"; 
        printf("TEST CASE FAILURE: expected result=%s, returned result=%s, "
               "search type=%s, returned index=%d key=%d, ascending=%s\n", 
               search_result_chars[expected_result], search_result_chars[search_result],
               search_type_chars[type], ret_index, key, ascending_str);
    }

    return error;
}

int run_test_cases(
    const int * items,
    const int n_items,
    const int ascending)
{
    int num_errors = 0;

    // test cases for LessThan
    num_errors += run_test_case(items, n_items, ascending, 9, LessThan, FoundLess);
    num_errors += run_test_case(items, n_items, ascending, 8, LessThan, FoundLess);
    num_errors += run_test_case(items, n_items, ascending, 4, LessThan, FoundLess);
    num_errors += run_test_case(items, n_items, ascending, 5, LessThan, FoundLess);
    num_errors += run_test_case(items, n_items, ascending, 1, LessThan, NotFound);
    
    // test cases for LessThanEquals
    num_errors += run_test_case(items, n_items, ascending, 4, LessThanEquals, FoundLess);
    num_errors += run_test_case(items, n_items, ascending, 9, LessThanEquals, FoundLess);
    num_errors += run_test_case(items, n_items, ascending, 1, LessThanEquals, FoundExact);
    num_errors += run_test_case(items, n_items, ascending, 8, LessThanEquals, FoundExact);
    num_errors += run_test_case(items, n_items, ascending, 5, LessThanEquals, FoundExact);
    num_errors += run_test_case(items, n_items, ascending, 0, LessThanEquals, NotFound);

    // test cases for Equals
    num_errors += run_test_case(items, n_items, ascending, 1, Equals, FoundExact);
    num_errors += run_test_case(items, n_items, ascending, 5, Equals, FoundExact);
    num_errors += run_test_case(items, n_items, ascending, 8, Equals, FoundExact);
    num_errors += run_test_case(items, n_items, ascending, 0, Equals, NotFound);
    num_errors += run_test_case(items, n_items, ascending, 4, Equals, NotFound);

    // test cases for GreaterThan
    num_errors += run_test_case(items, n_items, ascending, 0, GreaterThan, FoundGreater);
    num_errors += run_test_case(items, n_items, ascending, 2, GreaterThan, FoundGreater);
    num_errors += run_test_case(items, n_items, ascending, 4, GreaterThan, FoundGreater);
    num_errors += run_test_case(items, n_items, ascending, 9, GreaterThan, NotFound);
    num_errors += run_test_case(items, n_items, ascending, 8, GreaterThan, NotFound);

    // test cases for GreaterThanEquals
    num_errors += run_test_case(items, n_items, ascending, 8, GreaterThanEquals, FoundExact);
    num_errors += run_test_case(items, n_items, ascending, 1, GreaterThanEquals, FoundExact);
    num_errors += run_test_case(items, n_items, ascending, 4, GreaterThanEquals, FoundGreater);
    num_errors += run_test_case(items, n_items, ascending, 0, GreaterThanEquals, FoundGreater);
    num_errors += run_test_case(items, n_items, ascending, 9, GreaterThanEquals, NotFound);

    return num_errors;
}

int test_ascending_search()
{
    int ascending[7] = {1, 2, 3, 5, 6, 7, 8}; // Note 4 is missing from array 
    int ascending_size = sizeof(ascending) / sizeof(int);
    int num_errors = 0;

    num_errors = run_test_cases(ascending, ascending_size, 1);
    return num_errors;
}

int test_descending_search()
{
    int descending[7] = {8, 7, 6, 5, 3, 2, 1}; // Note 4 is missing from array
    int descending_size = sizeof(descending) / sizeof(int);
    int num_errors = 0;

    num_errors = run_test_cases(descending, descending_size, 0);
    return num_errors;
}

int test_corner_cases()
{
    int array[1] = {1};
    int array_size = sizeof(array) / sizeof(int);
    int num_errors = 0;
    // array size is passed as 0:
    num_errors += run_test_case(array, 0, 1, 0, LessThan, NotFound);
    // Other tests for when the size of the array is 1:
    num_errors += run_test_case(array, array_size, 1, 0, LessThan, NotFound);
    num_errors += run_test_case(array, array_size, 1, 1, LessThanEquals, FoundExact);
    num_errors += run_test_case(array, array_size, 1, 0, GreaterThan, FoundGreater);
    num_errors += run_test_case(array, array_size, 1, 2, GreaterThan, NotFound);
    num_errors += run_test_case(array, array_size, 1, 2, LessThan, FoundLess);

    return num_errors;
}

// Unit test:
int main()
{
    int num_errors = 0;
    num_errors += test_corner_cases();
    num_errors += test_ascending_search();
    num_errors += test_descending_search();
    if (num_errors) {
        printf("Number of tests that failed: %d\n", num_errors); 
    } else {
        printf("All tests passed !!!\n");
    }
    return 0;
} 
