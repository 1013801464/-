//
// Created by dunkle on 19-9-9.
//

// C++ program to Count
// Inversions in an array
// using Merge Sort
#include <iostream>
using namespace std;

int _mergeSort(int arr[], int temp[], int left, int right);
int merge(int arr[], int temp[], int left, int mid, int right);

/* This function sorts the input array and returns the
number of inversions in the array */
int mergeSort(int arr[], int array_size)
{
	int* temp = new int[array_size];								// 分配内存
	int val = _mergeSort(arr, temp, 0, array_size - 1);	// 返回不符合条件的数量
	delete temp;	//delete[]会触发析构函数 没有必要
	return val;
}

/* An auxiliary recursive function that sorts the input array and
returns the number of inversions in the array. */
int _mergeSort(int arr[], int temp[], int left, int right)
{
	int mid, inv_count = 0;
	if (right > left) {
		/* Divide the array into two parts and
		call _mergeSortAndCountInv()
		for each of the parts */
		mid = (right + left) / 2;

		/* Inversion count will be sum of
		inversions in left-part, right-part
		and number of inversions in merging */
		inv_count = _mergeSort(arr, temp, left, mid);
		inv_count += _mergeSort(arr, temp, mid + 1, right);

		/*Merge the two parts*/
		inv_count += merge(arr, temp, left, mid + 1, right);
	}
	return inv_count;
}

/* This funt merges two sorted arrays
and returns inversion count in the arrays.*/
int merge(int arr[], int temp[], int left, int mid, int right)
{
	int i, j, k;
	int inv_count = 0;

	i = left; /* i is index for left subarray*/
	j = mid; /* j is index for right subarray*/
	k = left; /* k is index for resultant merged subarray*/
	while ((i <= mid - 1) && (j <= right)) {
		if (arr[i] <= arr[j]) {
			temp[k++] = arr[i++];
		}
		else {		// else arr[i] > arr[j]
			temp[k] = arr[j];

			for (int new_i = i; new_i < mid; new_i++) {
				if (arr[new_i] > 3 * arr[j]) {		// 之前是inv_count += mid - i
					inv_count += mid - new_i;
					break;
				}
			}
			k++;
			j++;
		}
	}

	/* Copy the remaining elements of left subarray
	(if there are any) to temp*/
	while (i <= mid - 1)
		temp[k++] = arr[i++];

	/* Copy the remaining elements of right subarray
	(if there are any) to temp*/
	while (j <= right)
		temp[k++] = arr[j++];

	/*Copy back the merged elements to original array*/
	for (i = left; i <= right; i++)
		arr[i] = temp[i];

	return inv_count;
}

int arr[100011];

int main()
{
	for (int i = 0; i < 100000; ++i) {
		arr[i] = 100000 - i;
	}
	int n = 100000;
	int count = 0;		// 必须改成long long int !! 因为完全逆序的数对有C(10000, 10000)
	// cin >> n;
	//for (int i = 0; i < n; ++i) {
	//	cin >> arr[i];
	//}
	long long ans = mergeSort(arr, n);
	cout << ans;
	return 0;
}
