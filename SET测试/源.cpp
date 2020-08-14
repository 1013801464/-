#include <iostream>
#include <set>
using namespace std;

int main() {
	set<int> s;
	s.insert(1);
	cout << *s.find(1) << endl;
	
	return 0;
}