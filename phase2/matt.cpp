#include <iostream>
#include <cassert>

using namespace std;

//int countOccurrences(int a[], int len, int k); //function prototype. If you want to include it, 
						//then make sure to copy and paste int main in between the function and the function prototype

int countOccurrences(int a[], int len, int k)
{       
        int count = 0;	//you were missing the int infront of the count to signify the data type it is
        for (int i = 0; i < len; ++i) //for-loop that is checking up len which is the length of the array
        {
            if (a[i] == k) {	//conditional statement
                count++;	//increment count
            }
            
        }
        return count;	//returns an int for this function
}

int main()
{
    int a[]= {1,2,1,3,2};
    assert(countOccurrences(a,5,1) == 2);	//mimics the the function you had; but assert is just a fancy way to have different test cases
    cout << "All tests have successfully passed." << endl;
    return 0;
}
