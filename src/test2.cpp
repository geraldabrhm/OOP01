// C++ program demonstrate if there
// is no virtual function used in
// the Base class
#include <iostream>
using namespace std;

class check{
private:
	int numb;
public:
	check(){
		this->numb = 10;
	}

	check& operator+=(const int& numb){
		this->numb += numb;
		return *this;
	}
	int get(){
		return this->numb;
	}
};

// Driver Code
int main()
{
	check newcheck;
	newcheck += 10;
	cout << newcheck.get() << endl;
}
