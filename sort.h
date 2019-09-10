//
// Created by suro on 9/5/19.
//

#ifndef PROBLEMA_SORT_H
#define PROBLEMA_SORT_H

#include <algorithm>

using namespace std;

template <typename T>
int partition(T *arr, int start, int end){
    T pivot = arr[end];
    int i=start;
    for(int j=start; j<end; ++j){
        if(arr[j]<pivot){
            swap(arr[i],arr[j]);
            ++i;
        }
    }
    swap(arr[i],arr[end]);
    return i;
}

template <typename T>
void sortArray(T *arr, int start, int end){
    if(end>start){
        int p = partition(arr, start, end);
        sortArray(arr,start,p-1);
        sortArray(arr,p+1,end);
    }

}

#endif //PROBLEMA_SORT_H
