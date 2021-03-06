// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <unordered_set>

template<typename T>
class Node {
public:
	Node(T val) : val(val) 
	{
	}

	T val;
	std::shared_ptr<Node<T>> next;
};

template<typename T>
bool hasCycle(std::shared_ptr<Node<T>> list) {
	std::unordered_set<std::shared_ptr<Node<T>>> distinct;
	auto node = list;
	while (node != nullptr) {
		auto r = distint.insert(node);
		if (!r.second) {
			return true;
		}
	}
	return false;
}

int main(int argc, char* argv[])
{
	
}

