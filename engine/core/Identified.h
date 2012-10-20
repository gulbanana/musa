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
    virtual ~Identifiable() {}
	virtual TEnumClass id() const = 0;
    typedef TEnumClass ID;
};
