#pragma once

template<typename T, typename T::ID cid, typename TBase = T>
class Identified : public TBase
{	
public:
	virtual ~Identified() {}
	virtual typename T::ID id() const final { return cid; }
	static typename T::ID static_id() { return cid; }
};

template<typename TEnumClass>
class Identifiable
{	
public:
	typedef TEnumClass ID;

    virtual ~Identifiable() {}
	virtual TEnumClass id() const = 0;

    static std::vector<ID> require()
	{
		return std::vector<ID>();
	}

    static std::vector<ID> require(ID one)
	{
		std::vector<ID> requirements;
		requirements.push_back(one);
		return requirements;
	}

    static std::vector<ID> require(ID one, ID two)
	{
		std::vector<ID> requirements;
		requirements.push_back(one);
		requirements.push_back(two);
		return requirements;
	}

    static std::vector<ID> require(ID one, ID two, ID three)
	{
		std::vector<ID> requirements;
		requirements.push_back(one);
		requirements.push_back(two);
		requirements.push_back(three);
		return requirements;
	}
};
