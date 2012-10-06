#pragma once

template<typename T, typename T::ID cid, typename TBase = T>
class Identified : public TBase
{
	virtual typename T::ID _id() const override { return cid; }
public:
    virtual ~Identified() {}
    static typename T::ID id() { return cid; }
};

template<typename TEnumClass>
class Identifiable
{
protected:
	virtual TEnumClass _id() const = 0;
public:
    virtual ~Identifiable() {}
    typedef TEnumClass ID;
};

#define IDENTIFIABLE_COLLECTION(itype, iname, iplural) \
public:                                                \
    template<typename T>                               \
    void add_##iname(std::unique_ptr<T> iname)         \
    {                                                  \
        iplural[T::id()] = std::move(iname);             \
    }                                                  \
                                                       \
    template<typename T>                               \
    inline bool has_##iname()                          \
    {                                                  \
        return has_##iname(T::id());                     \
    }                                                  \
                                                       \
    bool has_##iname(itype::ID id)                     \
    {                                                  \
        return iplural.count(id) > 0;                  \
    }                                                  \
                                                       \
    template<typename T> T* get_##iname()              \
    {                                                  \
        return static_cast<T*>(iplural[T::id()].get());  \
    }                                                  \
protected:                                             \
    std::map<itype::ID, std::unique_ptr<itype>> iplural	
