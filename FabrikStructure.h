#pragma once
#include <vector>

template<typename T>
class FabrikStructure {
private:
	std::vector<&T> mchains;
public:
	FabrikStructure();
	virtual ~FabrikStructure();
};

template<typename T>
FabrikStructure<T>::FabrikStructure() {
	// Do we need to know a base position vector?
}