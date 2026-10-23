#include <stdio.h>

int binary_search(const int *arr, int len, int target)
{
    int low  = 0;
    int high = len-1;
   
    while(low<high)
    {
        int mid  = low+(high-low)/2;

        if(target>arr[mid])
        {
            low = mid+1;
        }
        else if (target<arr[mid])
        {
            high = mid-1;
        }
        else 
        {
            return mid;
        }
    }
    return -1;
}

int main()
{
    int arr[] = {1,3,5,7,9,11};
    int len = sizeof(arr)/sizeof(arr[0]);

    printf("%d\n",binary_search(arr, len, 7)); //expected 3
    printf("%d\n",binary_search(arr, len, 8)); //expected -1

    return 0;
}