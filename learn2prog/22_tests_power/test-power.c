#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

unsigned power(unsigned x, unsigned y);  // Prototype

void run_check(unsigned x, unsigned y, unsigned expected_ans) {
    unsigned result = power(x, y);
    if (result != expected_ans) {
        printf("Test failed: power(%u, %u) = %u, expected %u\n", x, y, result, expected_ans);
        exit(EXIT_FAILURE);
    }
}

int main(void) {
    // Existing test cases
    run_check(0, 0, 1);          
    run_check(1, 0, 1);          
    run_check(0, 5, 0);          
    run_check(5, 0, 1);          
    run_check(2, 3, 8);          
    run_check(3, 2, 9);          
    run_check(5, 3, 125);        
    run_check(10, 2, 100);       
    run_check(2, 10, 1024);      
    run_check(3, 5, 243);        
    run_check(7, 4, 2401);       

    // Additional test cases to detect subtle issues
    run_check(2, 31, 2147483648);     // 2^31 for overflow check in unsigned int
    run_check(1, UINT_MAX, 1);        // 1^y for maximum y value (should always return 1)
    run_check(UINT_MAX, 0, 1);        // x^0 for maximum x value (should return 1)
    run_check(2, 16, 65536);          // 2^16 for larger power

    printf("All tests passed!\n");
    return EXIT_SUCCESS;
}
