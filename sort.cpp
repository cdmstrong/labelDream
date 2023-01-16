#include <iostream>
using namespace std;


void quickSort(int (&arr)[9],int sort) {
    int i = 0;
    int j = 0;
    int size = sizeof(arr)/sizeof(arr[0]);
    j = size - 1;
    cout <<size << endl;
//    比对的数字
    int comNum = arr[i];
    while(i != j) {
//        从后寻找比i小的数
        cout << "compare" << i <<"idx" << arr[i] << endl;
        if(arr[j] < comNum) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            i++;
        } else if(arr[i] > comNum) {
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
            j--;
        } else {
            j--;
        }

    }
    for(int i =0; i < size; i ++) {
        cout << arr[i] << " ";
    }

}
//int list[9] = {22, 33, 52, 76, 21, 2, 12, 9, 13};
