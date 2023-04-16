#include <bits/stdc++.h>
using namespace std;

void FCFS(vector<int> requests, int disk_size, int head)
{
    cout << "\n\n";
    int sum = 0;
    cout << head << "-->";
    for (int i = 0; i < requests.size(); i++)
    {
        sum += abs(head - requests[i]);
        head = requests[i];
        if (i != requests.size() - 1)
            cout << requests[i] << "-->";
        else
            cout << requests[i];
    }
    cout << "\n";
    cout << "Total head movements : " << sum << "\n";
}
void SSTF(vector<int> requests, int disk_size, int head)
{
    map<int, int> mp;
    for (int i = 0; i < requests.size(); i++)
    {
        mp[requests[i]]++;
    }
    int count = 0;
    vector<int> res;
    int temp = head;
    int ele;
    res.push_back(head);
    while (count < requests.size())
    {
        int diff = INT_MAX;

        // traversing in map to find the least difference
        for (auto q : mp)
        {
            if (abs(q.first - temp) < diff)
            {
                ele = q.first;
                diff = abs(q.first - temp);
            }
        }
        mp[ele]--;
        if (mp[ele] == 0)
        {
            mp.erase(ele);
        }
        res.push_back(ele);
        temp = ele;
        count++;
    }
    cout << res[0];
    temp = res[0];
    int sum = 0;
    for (int i = 1; i < res.size(); i++)
    {
        cout << " -> " << res[i];
        sum += abs(res[i] - temp);
        temp = res[i];
    }
    cout << "\n";
    cout << "Total head movements : " << sum << "\n";
}
void SCAN(vector<int> requests, int disk_size, int head)
{
    int i = 0, k = 0, n = requests.size();
    int sum = 0;
    vector<int> res;
    int temp = head;
    requests.push_back(head);
    requests.push_back(disk_size);
    requests.push_back(0);
    sort(requests.begin(), requests.end());
    for (i = 0; i < requests.size(); i++)
    {
        if (head == requests[i])
            break;
    }
    k = i;
    if (k < n / 2)
    {
        for (i = k; i < requests.size(); i++)
        {
            res.push_back(requests[i]);
        }
        for (i = k - 1; i >= 0; i--)
        {
            res.push_back(requests[i]);
        }
    }
    else
    {
        for (i = k; i >= 0; i--)
        {
            res.push_back(requests[i]);
        }
        for (i = k + 1; i < requests.size(); i++)
        {
            res.push_back(requests[i]);
        }
    }
    temp = res[0];
    cout << temp;
    for (i = 1; i < res.size(); i++)
    {
        cout << " -> " << res[i];
        sum += abs(res[i] - temp);
        temp = res[i];
    }
    cout << '\n';
    cout << "Total head movements : " << sum << '\n';
}

void CSCAN(vector<int> requests, int disk_size, int head)
{
    int i = 0, k = 0, n = requests.size();
    int sum = 0;
    vector<int> res;
    int temp = head;
    requests.push_back(head);
    requests.push_back(disk_size);
    requests.push_back(0);
    sort(requests.begin(), requests.end());
    for (i = 0; i < requests.size(); i++)
    {
        if (head == requests[i])
            break;
    }
    k = i;
    if (k < n / 2)
    {
        for (i = k; i < requests.size(); i++)
        {
            res.push_back(requests[i]);
        }
        for (i = 0; i <= k - 1; i++)
        {
            res.push_back(requests[i]);
        }
    }
    else
    {
        for (i = k; i >= 0; i--)
        {
            res.push_back(requests[i]);
        }
        for (i = requests.size() - 1; i >= k + 1; i--)
        {
            res.push_back(requests[i]);
        }
    }
    temp = res[0];
    cout << temp;
    for (i = 1; i < res.size(); i++)
    {
        cout << " -> " << res[i];
        sum += abs(res[i] - temp);
        temp = res[i];
    }
    cout << '\n';
    cout << "Total head movements = " << sum << '\n';
}
void LOOK(vector<int> requests, int disk_size, int head)
{
    int i = 0, k = 0, n = requests.size();
    int sum = 0;
    vector<int> res;
    requests.push_back(head);
    sort(requests.begin(), requests.end());
    for (i = 0; i < requests.size(); i++)
    {
        if (head == requests[i])
            break;
    }
    k = i;
    if (k < n / 2)
    {
        for (i = k; i < requests.size(); i++)
        {
            res.push_back(requests[i]);
        }
        for (i = k - 1; i >= 0; i--)
        {
            res.push_back(requests[i]);
        }
    }
    else
    {
        for (i = k; i >= 0; i--)
        {
            res.push_back(requests[i]);
        }
        for (i = k + 1; i < requests.size(); i++)
        {
            res.push_back(requests[i]);
        }
    }
    int temp = res[0];
    cout << temp;
    for (i = 1; i < res.size(); i++)
    {
        cout << " -> " << res[i] << ' ';
        sum += abs(res[i] - temp);
        temp = requests[i];
    }
    cout << '\n';
    cout << "Total head movements = " << sum << '\n';
}
void CLOOK(vector<int> requests, int disk_size, int head)
{
    int i = 0, k = 0, n = requests.size();
    int sum = 0;
    vector<int> res;
    requests.push_back(head);
    sort(requests.begin(), requests.end());
    for (i = 0; i < requests.size(); i++)
    {
        if (head == requests[i])
            break;
    }
    k = i;
    if (k < n / 2)
    {
        for (i = k; i < requests.size(); i++)
        {
            res.push_back(requests[i]);
        }
        for (i = 0; i < k; i++)
        {
            res.push_back(requests[i]);
        }
    }
    else
    {
        for (i = k; i >= 0; i--)
        {
            res.push_back(requests[i]);
        }
        for (i = requests.size() - 1; i > k; i--)
        {
            res.push_back(requests[i]);
        }
    }
    int temp = res[0];
    cout << temp;
    for (i = 1; i < res.size(); i++)
    {
        cout << " -> " << res[i] << ' ';
        sum += abs(res[i] - temp);
        temp = requests[i];
    }
    cout << '\n';
    cout << "Total head movements = " << sum << '\n';
}

int main(int argc, char const *argv[])
{

    int disk_size = 0;
    cout << "Enter the disk size : ";
    cin >> disk_size;
    if (disk_size < 0)
    {
        cout << "Disk size cannot be negative\n";
        return -1;
    }
    disk_size--;
    int head = 0;
    cout << "Enter the position of head : ";
    cin >> head;
    if (head > disk_size || head < 0)
    {
        cout << "Invalid position\n";
        return -1;
    }
    int n_req = 0;
    cout << "Enter the no of requests : ";
    cin >> n_req;
    if (n_req < 0)
    {
        cout << "Requests cannot be negative\n";
        return -1;
    }
    vector<int> requests(n_req, 0);
    cout << "Enter the requests : ";
    for (int i = 0; i < requests.size(); i++)
    {
        cin >> requests[i];
        if (requests[i] > disk_size || requests[i] < 0)
        {
            cout << "Invalid position\n";
            return -1;
        }
    }
    int choice = 0;
    while (choice != 7)
    {
        cout << "\n";
        cout << "1.FCFS\n";
        cout << "2.SSTF\n";
        cout << "3.SCAN\n";
        cout << "4.CSCAN\n";
        cout << "5.LOOK\n";
        cout << "6.CLOOK\n";
        cout << "7.EXIT\n";
        cout << "Enter your choice : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            FCFS(requests, disk_size, head);
            break;
        case 2:
            SSTF(requests, disk_size, head);
            break;
        case 3:
            SCAN(requests, disk_size, head);
            break;
        case 4:
            CSCAN(requests, disk_size, head);
            break;
        case 5:
            LOOK(requests, disk_size, head);
            break;
        case 6:
            CLOOK(requests, disk_size, head);
            break;
        case 7:
            return 0;
        default:
            cout << "Invalid option entered \n";
            break;
        }
    }
    return 0;
}
// 82 170 43 140 24 16 190