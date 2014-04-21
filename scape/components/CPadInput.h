#pragma once
#include <core/framework.h>
#include <tile/types.h>

class CPadInput : public Identified<CPadInput,IComponent>
{
public:
	CPadInput() {}

	std::unique_ptr<IComponent> clone() const { return std::unique_ptr<IComponent>(new CPadInput(*this)); }
};

namespace std
{
	string to_string(CPadInput i);
}