#include <iostream>

struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
	ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
		ListNode* result = NULL;
		ListNode* cur = NULL;
		ListNode* p1 = l1;
		ListNode* p2 = l2;
		int carry = 0;		// 进位
		while (p1 != NULL && p2 != NULL) {
			int sum = p1->val + p2->val + carry;
			carry = sum >= 10;			// 新进位
			if (sum >= 10) sum -= 10;	// 新和
			// TODO put the sum to list
			if (!result) {
				result = new ListNode(sum);
				cur = result;
			}
			else {
				cur->next = new ListNode(sum);
				cur = cur->next;
			}
			p1 = p1->next;
			p2 = p2->next;
		}
		ListNode* p = NULL;
		if (p1 != NULL) {		// 此时p2必为空
			p = p1;
		}
		else if (p2 != NULL) {	// 此时p1必为空
			p = p2;
		}
		while (p != NULL) {
			int sum = carry + p->val;
			carry = sum >= 10;
			if (sum >= 10) sum -= 10;
			// TODO put sum to the list
			cur->next = new ListNode(sum);
			cur = cur->next;
			p = p->next;
		}
		// 还有最后一步::
		if (carry > 0) {
			cur->next = new ListNode(carry);
		}
		return result;
	}
};

int main() {
	Solution s;
	ListNode* l = new ListNode(2);
	ListNode* p = l;
	p->next = new ListNode(8);
	p = p->next;
	p->next = new ListNode(9);
	ListNode* r = new ListNode(5);
	p = r;
	p->next = new ListNode(1);
	p = p->next;
	p->next = new ListNode(9);
	s.addTwoNumbers(l, r);
	return 0;
}