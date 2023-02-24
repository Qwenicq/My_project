#include <stdio.h>
#include <stdlib.h>
#include<string.h>
void _MergeSort(int* arr, int left, int right,int* tmp)
{
	if (left >= right)//=Ϊֻ��һ��������Ϊ�������
	{
		return;
	}

	//�����������û���򣬷��εݹ�ָ����䣬ֱ����С��
	int mid = (left + right) >> 1;
	//���䱻��Ϊ[left,mid] �� [mid+1,right]
	//��ʼ�ݹ�
	_MergeSort(arr, left, mid, tmp);
	_MergeSort(arr, mid + 1, right, tmp);

	//��ʱͨ���ݹ��Ѿ��ܱ�֤��������������
	//��ʼ�鲢
	int begin1 = left;
	int end1 = mid;
	int begin2 = mid + 1;
	int end2 = right;
	//�鲢ʱ������ʱ�����λ�ô�left��ʼ
	int index = left;

	while (begin1 <= end1 && begin2 <= end2)
	{
		if (arr[begin1] < arr[begin2])
		{
			tmp[index] = arr[begin1];
			index++;
			begin1++;
			//�����д������д��һ��
			//tmp[index++] = arr[begin1++];
		}
		else
		{
			tmp[index++] = arr[begin2++];
		}
	}

	//ѭ������������û��������Ǹ�����ʣ�µ�����������
	while (begin1 <= end1)
	{
		tmp[index++] = arr[begin1++];
	}
	while (begin2 <= end2)
	{
		tmp[index++] = arr[begin2++];
	}

	//���Ź鲢�����������ԭ����
	for (int i = left; i <=right ; i++)
	{
		arr[i] = tmp[i];
	}
}

void MergeSort(int* arr, int n)
{
	//����һ���ռ�������ʱ�������
	int* tmp = (int*)malloc(sizeof(int)*n);

	//�鲢����
	_MergeSort(arr, 0, n - 1, tmp);

	//�ͷſռ�
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
