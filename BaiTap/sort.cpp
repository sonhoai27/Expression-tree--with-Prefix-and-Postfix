#include <iostream>
using namespace std;

//gan gia tri min cho i,
//neu vi tri j be hon min thi swap nguoc lai khog
//gom co cac bien i, j va min
void swap(int *locationA, int *locationB) {
	int temp = *locationA;
	*locationA = *locationB;
	*locationB = temp;
}
void selectionSort(int arr[], int count) {
	for (int i = 0; i < count - 1;i++) {
		int min = i;
		for (int j = i + 1; j<count; j++) {
			if (arr[j] < arr[min]) {
				min = j;
			}
		}
		swap(&arr[min], &arr[i]);
	}
}

void insertionSort(int arr[], int count) {
	for (int i = 1; i < count;i++) {
		int key = arr[i];
		int j = i - 1;
		while (j >= 0 && arr[j] > key) {
			arr[j + 1] = key;
			j = j - 1;
		}

		arr[j + 1] = key;
	}
}

//sap xem ktra vs i cho j tu dau den cuoi day
void bubbleSortV1(int arr[], int count) {
	for (int i = 0; i < count;i++) {
		for (int j = 0; j < count - i - 1;j++) {
			if (arr[j] > arr[j + 1]) {
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
			}
		}
	}
}
int partition(int arr[], int l, int h) {
	int x = arr[h];//can tren
	int i = (l - 1); //vi tri nho hon l
	for (int j = l; j <= h - 1;j++) {
		if (arr[j] < x) {
			i++;
			swap(&arr[i], &arr[j]);
		}
	}
	swap(&arr[i + 1], &arr[h]);
	return (i + 1);
}
void quickSort(int arr[], int l, int h) {
	if (l < h) {
		int p = partition(arr, l, h);
		quickSort(arr, l, p - 1);
		quickSort(arr, p + 1, h);
	}
}
void printArr(int arr[], int count) {
	for (int i = 0; i < count;i++) {
		cout << arr[i] << " ";
	}
	cout << endl;
}


int main2() {
	int arr[] = { 20,15,7,11,27,21,19,30,5,35,7,9,12,10 };

	cout << "SORT\n";

	/*cout<<"SELECT SORT:\n";
	selectionSort(arr, 14);
	printArr(arr, 14);

	cout<<"INSERT SORT:\n";
	insertionSort(arr, 14);
	printArr(arr, 14);*/

	/*cout<<"Bubble SORT:\n";
	bubbleSortV1(arr, 14);
	printArr(arr, 14);*/

	cout << "Bubble SORT:\n";
	quickSort(arr, 0, sizeof(arr) / sizeof(arr[0]) - 1);
	printArr(arr, sizeof(arr) / sizeof(arr[0]));

	system("pause");
	return 0;
}
