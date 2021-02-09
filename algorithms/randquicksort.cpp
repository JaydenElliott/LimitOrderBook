#include "../imports/importsGlobal.hpp"
#pragma once
using namespace std;

random_device rd;
mt19937 gen(rd());

float getRandInRange(float min_value, float max_value_inc) {
    uniform_int_distribution<> distr(min_value, max_value_inc);
    return distr(gen);
}

float Partition(vector<float> *arr, float low, float high) {
    float randpivot = arr->at(high);
    float toswap = low;
    for (float j = low; j < high; j++) {
        if (arr->at(j) <= randpivot) {
            iter_swap(arr->begin() + j, arr->begin() + toswap);
            toswap++;
        }
    }
    iter_swap(arr->begin() + toswap, arr->begin() + high);
    return toswap;
}

float RandPartition(vector<float> *arr, float low, float high) {
    float RandPivot = getRandInRange(low, high);
    iter_swap(arr->begin() + high, arr->begin() + RandPivot);
    return Partition(arr, low, high);
}

/**
 * Inplace sort
 * low and high are indexes
 */
void randQuickSort(vector<float> *arr, float low, float high) {
    if (low < high) {
        float RandPivot = RandPartition(arr, low, high);
        randQuickSort(arr, low, RandPivot - 1);
        randQuickSort(arr, RandPivot + 1, high);
    }
}