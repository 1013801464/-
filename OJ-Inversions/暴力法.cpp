/*
#include <iostream>
using namespace std;

// 关闭同步的命令??

int num[100000];

int main() {
	int n;
	int count = 0;
	cin >> n;
	for (int i = 0; i < n; ++i) {
		cin >> num[i];
	}
	for (int i = 0; i < n; ++i) {
		for (int j = i + 1; j < n; ++j) {
			if (num[i] > 3 * num[j]) {
				++count;
			}
		}
	}
	cout << count;
	return 0;
}

*/