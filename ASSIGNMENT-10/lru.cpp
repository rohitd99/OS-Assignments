// C++ implementation of above algorithm
#include <bits/stdc++.h>
using namespace std;

// Function to find page faults using indexes
void LRU(int pages[], int n, int capacity)
{
	unordered_set<int> s;
	map<int, int> use_time;

	int page_faults = 0;
	cout << "Request\t\t"
		 << "Frames\t\t"
		 << "Result" << endl;

	for (int i = 0; i < n; i++)
	{
		int temp = page_faults;
		if (s.size() < capacity)
		{
			if (s.find(pages[i]) == s.end())
			{
				s.insert(pages[i]);
				page_faults++;
			}
			use_time[pages[i]] = i;
		}
		else
		{
			if (s.find(pages[i]) == s.end())
			{
				int lru = INT_MAX, val;
				for (auto it = s.begin(); it != s.end(); it++)
				{
					if (use_time[*it] < lru)
					{
						lru = use_time[*it];
						val = *it;
					}
				}
				s.erase(val);
				s.insert(pages[i]);
				page_faults++;
			}
			use_time[pages[i]] = i;
		}
		cout << "  " << pages[i] << "\t\t";
		unordered_set<int>::iterator j;
		for (j = s.begin(); j != s.end(); j++)
		{
			cout << *j << " ";
		}
		for (int j = 0; j < capacity - s.size(); j++)
			cout << "  ";
		if (temp == page_faults)
			cout << "\t\tHit";
		else
			cout << "\t\tMiss";
		cout << "\n";
	}

	cout << "\nThe total no. of Page faults: " << page_faults << endl;
}

void Optimal(int pages[], int n, int capacity)
{
	set<int> s;
	vector<int> arr;
	for (int i = 0; i < n; i++)
	{
		arr.push_back(pages[i]);
	}
	map<int, int> indexes;

	int page_faults = 0;
	cout << "Request\t\t"
		 << "Frames\t\t"
		 << "Result" << endl;

	for (int i = 0; i < n; i++)
	{
		int temp = page_faults;
		if (s.size() < capacity)
		{
			if (s.find(pages[i]) == s.end())
			{
				s.insert(pages[i]);
				arr.erase(arr.begin());
				page_faults++;
			}
			indexes[pages[i]] = i;
		}
		else
		{
			if (s.find(pages[i]) == s.end())
			{
				map<int, int> mp;
				set<int>::iterator it = s.begin();
				for (it = s.begin(); it != s.end(); it++)
				{
					mp[*it] = -1;
				}
				for (int j = 0; j < arr.size(); j++)
				{
					if (mp[arr[j]] == -1)
					{
						mp[arr[j]] = j;
					}
				}
				int toBeRemoved = -1, mx = INT_MIN;
				for (auto it : mp)
				{
					if (it.second == -1)
					{
						toBeRemoved = it.first;
						break;
					}
					else
					{
						if (it.second > mx)
						{
							toBeRemoved = it.first;
							mx = it.second;
						}
					}
				}
				s.erase(toBeRemoved);
				s.insert(pages[i]);
				page_faults++;
			}
			indexes[pages[i]] = i;
		}
		cout << "  " << pages[i] << "\t\t";
		set<int>::iterator j;
		for (j = s.begin(); j != s.end(); j++)
		{
			cout << *j << " ";
		}
		for (int j = 0; j < capacity - s.size(); j++)
			cout << "  ";
		if (temp == page_faults)
			cout << "\t\tHit";
		else
			cout << "\t\tMiss";
		cout << "\n";
	}

	cout << "\nThe total no. of Page faults: " << page_faults << endl;
}

int main()
{
	int n;
	cout << "Enter the number of Processes : ";
	cin >> n;
	int pages[n];
	cout << "Enter reference string: " << endl;
	for (int i = 0; i < n; i++)
	{
		cin >> pages[i];
	}
	// int pages[] = {7, 0, 1, 2, 0, 3, 0, 4, 2, 3, 0, 3, 2};
	// n = sizeof(pages)/sizeof(pages[0]);
	int capacity = 0;
	cout << "Enter the number of frames : ";
	cin >> capacity;
	int choice = 0;
	cout << "1. LRU\n";
	cout << "2. Optimal\n";
	cout << "3. Exit\n";
	cin >> choice;
	while (choice != 3)
	{
		switch (choice)
		{
		case 1:
		{
			cout << "\n--------------- LRU -----------------\n\n";
			LRU(pages, n, capacity);
			break;
		}
		case 2:
		{
			cout << "\n\n\n--------------- Optimal -----------------\n\n";
			Optimal(pages, n, capacity);
			break;
		}
		case 3:
		{
			return 0;
			break;
		}
		default:
			cout << "Invalid option entered\n";
			break;
		}
		cout << "1. LRU\n";
		cout << "2. Optimal\n";
		cout << "3. Exit\n";
		cin >> choice;
	}

	return 0;
}
