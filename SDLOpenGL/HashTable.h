#pragma once
#include <unordered_map>

template <class K, class V> class Hashtable {

public:

	std::unordered_map<K, V> htmap;

	void put(K key, V value) {
			htmap[key] = value;
	}

	V get(K key) {
			return htmap[key];
	}

};
