#include <stdio.h>

void printsort(int *arr, int len)
{
    for(int i=0; i<len; i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
}
void bubblesort(int *arr, int len)
{
    for(int i=0; i<len; i++)
    {
        for(int j=1; j<len; j++)
        {
            if(arr[j]>arr[j-1])
            {
               int temp=arr[j];
                arr[j]=arr[j-1];
                arr[j-1]=temp;
            }
        }
    }
    printsort(arr,len);
}

int main()
{
    int arr[] = {5,3,8,6,3,2};
    int len = sizeof(arr)/sizeof(arr[0]);
    printf("Before sorting: ");
    printsort(arr,len);
    printf("After sorting: ");
    bubblesort(arr,len);
    return 0;
}