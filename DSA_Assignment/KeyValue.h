/*
DSA T02
Group 7
Tan Si Huei Chloe S10260078
Ng Joe Yi S10262850
*/
#pragma once

template <typename KeyType, typename ValueType>
class KeyValue {
public:
    KeyType key;
    ValueType* value;

    // Constructor
    KeyValue(const KeyType& key, ValueType* value) : key(key), value(value) {}
};