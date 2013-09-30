#pragma once
#include <core/framework.h>
#include <tile/types.h>

class CKBMInput : public Identified<CKBMInput,IComponent>
{
public:
	CKBMInput() {}

	std::unique_ptr<IComponent> clone() const { return std::unique_ptr<IComponent>(new CKBMInput(*this)); }
};

namespace std
{
	string to_string(CKBMInput i);
}