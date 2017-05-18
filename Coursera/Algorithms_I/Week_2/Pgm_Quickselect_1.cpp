#include <iostream>
#include <iomanip>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

typedef vector<uint32_t> IntegerArray;
uint32_t comparisons(0);

uint32_t ChoosePivot(IntegerArray& arr, size_t left, size_t right)
{
    return arr[left];
}


void Display(IntegerArray& arr)
{
    for (auto i(0); i < arr.size();)
    {
        cout << setw(3) << arr[i] << " ";
        if ((++i % 20) == 0)
            cout << endl;
    }
    cout << endl;
}


size_t Partition(IntegerArray& arr, size_t left, size_t right, uint32_t pivot)
{
    auto temp(0);
    auto i(left);
    for (auto j(left+1); j < right; ++j) {
        if (arr[j] < pivot) {
            ++i;
            temp   = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
    }

    temp      = arr[left];
    arr[left] = arr[i];
    arr[i]    = temp;

    return i;
}


int QuickSelect(IntegerArray& arr, size_t left, size_t right, size_t kth)
{
    if (left < right)
    {
        auto pivot = ChoosePivot(arr, left, right);

        auto p = Partition(arr, left, right, pivot);

        comparisons += (right - left - 1);

        size_t nth = p - left + 1;
        if (kth == nth) {
            return arr[p];
        } else if (kth < nth) {
            return QuickSelect(arr, left, p, kth);
        } else {
            return QuickSelect(arr, p + 1, right, kth - nth);
        }
    } else {
        return arr[left];
    }
}


int main(int argc, char** argv)
{
    if (argc != 2) {
        return 0;
    }
    IntegerArray numVect;
    ifstream inFile(argv[1]);
    // ifstream inFile("IntegerArray_100_FullySorted.txt");
    // ifstream inFile("IntegerArray_100.txt");
    // ifstream inFile("IntegerArray_100_FullyUnsorted.txt");
    if (inFile.is_open())
    {
        while (inFile)
        {
            uint32_t number;
            inFile >> number;
            if (inFile.eof())
            {
                break;
            }
            // cout << number << endl;
            numVect.push_back(number);
        }
        inFile.close();
    }

    // for_each(numVect.cbegin(), numVect.cend(), [] (uint32_t n) {cout << n << endl;} );
    cout << "Array Size : " << numVect.size() << endl;
    cout << "Element at 8 place : " << QuickSelect(numVect, 0, numVect.size(), 10) << endl;
    // Display(numVect);
    cout << "Count : " << comparisons << endl;
    return 0;
}

