#pragma once

template <typename KeyType, typename ValueType>
class KeyValue {
public:
    KeyType key;
    ValueType* value;

    // Constructor
    KeyValue(const KeyType& key, ValueType* value) : key(key), value(value) {}
};