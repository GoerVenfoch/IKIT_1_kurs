#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

vector<int> load_txt(ifstream& ist, vector<int>& arr);
int search(const vector<int>& arr, int unknown, int index, int end_part);

int main()
{
	ifstream in("Input.txt");
	if (!in)
	{
		cout << "Unable to open the file." << endl;
		return 1;
	}
	int unknown, index = 0;
	vector<int> arr;
	arr = load_txt(in, arr);
	int arr_size = arr.size();

	if (arr_size == 0)
	{
		cout << "The array is empty." << endl;
		return -1;
	}
	cout << "Enter number: ";
	cin >> unknown;

	index = search(arr, unknown, index, arr_size);

	if (index != 0)
	{
		cout << "The desired number have an index " << index << endl;
	}
	else
	{
		cout << "The desired number don't found" << endl;
	}

	return 0;
}

vector<int> load_txt(ifstream& ist, vector<int>& arr)
{
	int num;

	while (ist >> num)
	{
		arr.push_back(num);
	}
	return arr;
}

int search(const vector<int>& arr, int unknown, int index, int end_part)
{
	int middle = (end_part + index) / 2;

	if (unknown == arr[middle])
	{
		return middle + 1;
	}
	else if (end_part == middle || middle == index)
	{
		return 0;
	}
	else
	{
		if (unknown > arr[middle])
		{
			return index = search(arr, unknown, middle, end_part);
		}
		else
		{
			return index = search(arr, unknown, index, middle);
		}
	}
}