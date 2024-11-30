#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int getRandomNum(int min, int max)
{
	return rand() % max + min;
}

bool dodgeSuccessfully(int speed)
{
	int x = getRandomNum(1, 100);
	
	cout << x << " ";
	
	return speed >= x ?  1 : 0;
}

int main() 
{
	srand( time(nullptr) * 703);
//	srand(123); //debug
//	for(int i = 0; i < 10; i++)
//	{
//		int x = getRandomNum(1, 100);
//		cout << x << " "; 
//	}
	
	int count = 0;
	
	for(int i = 0; i < 500; i++)
	{
		if(dodgeSuccessfully(50) == 1)
			count ++;
	}
		
	
	
	
	cout << "\n" << count;
    
    return 0;
}




