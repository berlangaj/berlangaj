#include <iostream>
#include <cmath>
#include "./nth_root.h"

int main() {
    {   // MINIMUM REQUIREMENT (for this lab)
        // just call the function with various values of n and x
        nth_root(1,1);
        nth_root(2,0);
        nth_root(-7,-2);
        nth_root(7,-2);
        nth_root(-1,3);
        nth_root(2,1);
        nth_root(-3,3.7);

        try {
          nth_root(0,2);  
        }
        catch (std::domain_error) {
        }

        try { 
            nth_root(2,-1);
        }
        catch(std::domain_error) {     
        }
        try {
            nth_root(-1,0);
        }
        catch(std::domain_error) {

        }

    }

    {   // TRY HARD
        // report the value
        double actual = nth_root(2, 1);
        std::cout << "nth_root(2, 1) = " << actual << std::endl;
        std::cout << "nth_root(1,1) = " << nth_root(1,1) << std::endl;
        std::cout << "nth_root(2,0) = " << nth_root(2,0) << std::endl;
        std::cout << "nth_root(-7,-2) = " << nth_root(-7,-2) << std::endl;
        std::cout << "nth_root(7,-2) = " << nth_root(7,-2) << std::endl;
        std::cout << "nth_root(-1,3) = " << nth_root(-1,3) << std::endl;
        std::cout << "nth_root(2,1) = " << nth_root(2,1) << std::endl;
        std::cout << "nth_root(-3,3.7) = " << nth_root(-3, 3.7) << std::endl; 
    }

    {   // TRY HARDER
        // compare the actual value to the expected value
        double actual = nth_root(2, 1);
        double expected = 1;
        if (std::fabs(actual - expected) > 0.00005) {
            std::cout << "[FAIL] (n=2, x=1)" << std::endl;
            std::cout << "  expected nth_root(2, 1) to be " << expected << std::endl;
            std::cout << "  got " << actual << std::endl;
        } else {
            std::cout << "[PASS] (n=2, x=1)" << std::endl;
        }

        double actual2 = nth_root(1,1);
        double expected2 = 1;
        if (std::fabs(actual - expected) > 0.00005) {
            std::cout << "[FAIL] (n=1, x=1)" << std::endl;
            std::cout << "  expected nth_root(1, 1) to be " << expected << std::endl;
            std::cout << "  got " << actual << std::endl;
        } else {
            std::cout << "[PASS] (n=1, x=1)" << std::endl;
        }   
    }
}
