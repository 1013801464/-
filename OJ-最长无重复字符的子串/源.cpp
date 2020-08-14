#include <iostream>
#include <string>
using namespace std;

class Solution {
public:
	int lengthOfLongestSubstring(string s) {
		// �ַ�������
		// s[i] ȡ��i���ַ�
		// s.length() ���ַ�������
		int len = s.length();
		int* lastIndex = new int[len];
		// �����뱾�ַ���ͬ����һ���ַ���λ��
		for (int i = 0; i < len; ++i) {
			lastIndex[i] = -1;
			for (int j = i - 1; j >= 0; --j) {
				if (s[j] == s[i]) {
					lastIndex[i] = j;
					break;
				}
			}
		}
		// ���ÿ���ַ�, �������п��ܽ�, ��ȡ������̵Ľ�
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
			// ����һ��, ���ַ��ĳ�����cLength
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
					break;		// �ر�����, ֻ�����ڵ�
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