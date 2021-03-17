#include <iostream>

using std::cout, std::cin, std::endl;

int main()
{
	int test[10] = { -12, 2, -2, 3, 5, -4, 78, -3, 19, 33};
	// the largest difference between values should be 82
	unsigned int answer = 0;
	unsigned int difference[9];//create new array holding difference value
	// loop and compare 
	for (int i = 0; i <= 8 ; i++) //only go to 8 so it will not test past the last index
	{
		 
		difference[i] = test[i] - test[i+1]; //insert new array values
	}

	for (int j = 0; j < 8; j++) //only go to 8 to no go past index
	{ //loop difference array to find largest value
		if (answer < difference[j] ) //if difference is greater than answer then it becomes answer
		{
			answer = difference[j];

		}
	}
	cout << answer << "is the answer" << endl;
	return 0;	
}
