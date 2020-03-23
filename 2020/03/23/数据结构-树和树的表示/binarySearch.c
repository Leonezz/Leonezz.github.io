#define ElementType int
int binarySearch(ElementType *list, int listLength, ElementType target)
{
    int left = 0;
    int right = listLength - 1;
    int mid = 0;
    while (left <= right)
    {
        mid = (left + right) / 2;
        if (list[mid] == target)
            return mid;
        else if (list[mid] > target)
            right = mid - 1;
        else
            left = mid + 1;
    }
    return -1; //means not frond!
}