#include <bits/stdc++.h>
using namespace std;
vector<int> first_fit(vector<int> blocks, vector<int> process,vector<int> &fragments)
{
    vector<int> allocations(process.size(), -1);
    vector<bool> occupied(blocks.size(), false);
    for (int i = 0; i < process.size(); i++)
    {
        for (int j = 0; j < blocks.size(); j++)
        {
            if (blocks[j] >= process[i] && occupied[j] == false)
            {
                allocations[i] = j;
                occupied[j] = true;
                fragments[i] = blocks[j] - process[i];
                break;
            }
        }
    }
    return allocations;
}
vector<int> next_fit(vector<int> blocks, vector<int> process,vector<int> &fragments)
{
    vector<int> allocations(process.size(), -1);
    vector<bool> occupied(blocks.size(), false);
    int j = 0;
    int t = blocks.size() - 1;
    for (int i = 0; i < process.size(); i++)
    {
        while (j < blocks.size())
        {
            if (blocks[j] >= process[i] && occupied[j] == false)
            {
                allocations[i] = j;
                // blocks[j] -= process[i];
                occupied[j] = true;
                fragments[i] = blocks[j] - process[i];
                t = (j - 1) % blocks.size();
                break;
            }
            if (t == j)
            {
                t = (j - 1) % blocks.size();
                break;
            }
            j = (j + 1) % blocks.size();
        }
    }
    return allocations;
}
vector<int> best_fit(vector<int> blocks, vector<int> process, vector<int> &fragments)
{
    vector<int> allocations(process.size(), -1);
    vector<bool> occupied(blocks.size(), false);
    for (int i = 0; i < process.size(); i++)
    {
        int minindex = -1;
        bool found = false;
        for (int j = 0; j < blocks.size(); j++)
        {
            if (blocks[j] >= process[i] && occupied[j] == false)
            {
                found = true;
                if (minindex == -1)
                {
                    minindex = j;
                }
                else if (blocks[j] < blocks[minindex])
                {
                    minindex = j;
                }
            }
        }
        if (found)
        {
            allocations[i] = minindex;
            fragments[i] = blocks[minindex] - process[i];
            occupied[minindex] = true;
        }
    }
    return allocations;
}
vector<int> worst_fit(vector<int> blocks, vector<int> process,vector<int> &fragments)
{
    vector<int> allocations(process.size(), -1);
    vector<bool> occupied(blocks.size(), false);
    for (int i = 0; i < process.size(); i++)
    {
        int maxindex = 0;
        bool found = false;
        for (int j = 0; j < blocks.size(); j++)
        {
            if (blocks[j] >= process[i] && occupied[j] == false)
            {
                found = true;
                if (maxindex == -1)
                {
                    maxindex = j;
                }
                else if (blocks[j] > blocks[maxindex])
                {
                    maxindex = j;
                }
                        }
        }
        if (found)
        {
            allocations[i] = maxindex;
            fragments[i] = blocks[maxindex] - process[i];
            occupied[maxindex] = true;
        }
    }
    return allocations;
}
void printAllocations(vector<int> &process, vector<int> &allocations,vector<int> &fragments)
{
    cout << "Process No\t\tProcess Size\t\tBlock Allocated\t\tFragmentSize\n";
    for (int i = 0; i < process.size(); i++)
    {
        if (allocations[i] >= 0)
            cout << i << "\t\t\t" << process[i] << "\t\t\t" << allocations[i] << "\t\t\t"<< fragments[i] << "\n";
        else
            cout << i << "\t\t\t" << process[i] << "\t\t\t"
                 << "Not Allocated"
                 << "\t\t\t"
                 << "NA"
                 << "\n";
    }
}
int main(int argc, char const *argv[])
{
    int n_blocks = 0, n_processes = 0;
    cout << "Enter the number of blocks in memory : ";
    cin >> n_blocks;
    cout << "Enter the number of processes : ";
    cin >> n_processes;
    vector<int> blocks(n_blocks, 0);
    vector<int> process(n_processes, 0);
    vector<int> fragments(n_processes,0);
    for (int i = 0; i < n_blocks; i++)
    {
        cout << "Enter size of block[" << i << "] : ";
        cin >> blocks[i];
    }
    for (int i = 0; i < n_processes; i++)
    {
        cout << "Enter size of process[" << i << "] : ";
        cin >> process[i];
    }
    int choice = 0;
    cout << "\n------------ MENU ------------\n";
    cout << "1.First Fit\n";
    cout << "2.Next Fit\n";
    cout << "3.Best Fit\n";
    cout << "4.Worst Fit\n";
    cout << "5.Exit\n";

    cout << "Enter your choice : ";
    cin >> choice;
    while (choice != 5)
    {
        switch (choice)
        {
        case 1:
        {
            vector<int> allocations = first_fit(blocks, process,fragments);
            printAllocations(process, allocations,fragments);
            break;
        }
        case 2:
        {
            vector<int> allocations = next_fit(blocks, process,fragments);
            printAllocations(process, allocations,fragments);
            break;
        }
        case 3:
        {
            vector<int> allocations = best_fit(blocks, process,fragments);
            printAllocations(process, allocations,fragments);
            break;
        }
        case 4:
        {
            vector<int> allocations = worst_fit(blocks, process,fragments);
            printAllocations(process, allocations,fragments);
            break;
        }
        default:
            cout << "Invalid option entered\n";
            break;
        }
        cout << "\n------------ MENU ------------\n";
        cout << "1.First Fit\n";
        cout << "2.Next Fit\n";
        cout << "3.Best Fit\n";
        cout << "4.Worst Fit\n";
        cout << "5.Exit\n";
        cout << "Enter your choice : ";
        cin >> choice;
    }
    return 0;
}
