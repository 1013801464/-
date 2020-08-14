#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		// 字符串操作
		// s[i] 取第i个字符
		// s.length() 求字符串长度
		int len = s.length();
		int* lastIndex = new int[len];
		// 查找与本字符相同的上一个字符的位置
		for (int i = 0; i < len; ++i) {
			lastIndex[i] = -1;
			for (int j = i - 1; j >= 0; --j) {
				if (s[j] == s[i]) {
					lastIndex[i] = j;
					break;
				}
			}
		}
		// 针对每个字符, 计算所有可能解, 并取其中最短的解
		int maxLength = 0;
		for (int i = 0; i < len; ++i) {
			int limit = lastIndex[i];
			int cLength = len;
			int weight = 0;
			for (int j = i; j > limit; --j) {
				int l = j - lastIndex[j] + weight;
				if (l < cLength) cLength = l;
				int newLimit = lastIndex[j];
				if (newLimit > limit) limit = newLimit;
				weight++;
			}
			// 到这一步, 本字符的长度是cLength
			if (cLength > maxLength) maxLength = cLength;
		}
		delete[] lastIndex;
		return maxLength;
	}

	int lengthOfLongestSubstring2(string s) {
		int  size, i = 0, j, k, max = 0;
		size = s.size();
		for (j = 0; j < size; j++) {
			for (k = i; k < j; k++)
				if (s[k] == s[j]) {
					i = k + 1;
					break;		// 特别巧妙, 只找相邻的
				}
			if (j - i + 1> max)
				max = j - i + 1;
		}
		return max;
	}
};

int main() {
	Solution s;
	int z = s.lengthOfLongestSubstring2("kkkkkkk");
	return 0;
}