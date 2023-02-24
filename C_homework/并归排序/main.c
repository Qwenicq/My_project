#include <stdio.h>
#include <stdlib.h>
#include<string.h>
void _MergeSort(int* arr, int left, int right,int* tmp)
{
	if (left >= right)//=为只有一个数，＞为区间存在
	{
		return;
	}

	//左右区间如果没有序，分治递归分割区间，直到最小，
	int mid = (left + right) >> 1;
	//区间被分为[left,mid] 和 [mid+1,right]
	//开始递归
	_MergeSort(arr, left, mid, tmp);
	_MergeSort(arr, mid + 1, right, tmp);

	//此时通过递归已经能保证左右子区间有序
	//开始归并
	int begin1 = left;
	int end1 = mid;
	int begin2 = mid + 1;
	int end2 = right;
	//归并时放入临时数组的位置从left开始
	int index = left;

	while (begin1 <= end1 && begin2 <= end2)
	{
		if (arr[begin1] < arr[begin2])
		{
			tmp[index] = arr[begin1];
			index++;
			begin1++;
			//这三行代码可以写成一行
			//tmp[index++] = arr[begin1++];
		}
		else
		{
			tmp[index++] = arr[begin2++];
		}
	}

	//循环结束，将还没遍历完的那个区间剩下的数拷贝下来
	while (begin1 <= end1)
	{
		tmp[index++] = arr[begin1++];
	}
	while (begin2 <= end2)
	{
		tmp[index++] = arr[begin2++];
	}

	//将排归并完的数拷贝回原数组
	for (int i = left; i <=right ; i++)
	{
		arr[i] = tmp[i];
	}
}

void MergeSort(int* arr, int n)
{
	//申请一个空间用来临时存放数据
	int* tmp = (int*)malloc(sizeof(int)*n);

	//归并排序
	_MergeSort(arr, 0, n - 1, tmp);

	//释放空间
	free(tmp);
}

int main()
{
   int a[100010],n,i;
   scanf("%d",&n);
   for(i=0;i<n;i++)
   scanf("%d",&a[i]);
   MergeSort(a,n);

   for(i=0;i<n;i++)
    printf("%2d",a[i]);
   printf("\n");
   system("pause");
    return 0;
}
