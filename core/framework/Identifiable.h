#pragma once

//These templates provide typesafe runtime lookup for locally-unique instances of open discriminated unions.
//It isn't particularly fast or slow - fine for composition and load-time lookups, but should not be in an inner loop.

//name-mangling produces ids of type Identifiable<T>::ID, unique to the base type and subtype
template<typename TIdentifiable>
class Identification
{
public:
    std::string value;

    Identification(const char* base, const char* sub) : value(std::string(base) + std::string(sub)) {}
    Identification(const Identification& that) : value(that.value) {}

    //allows use as a map key
    bool operator<(const Identification& that) const { return value < that.value; }
};

//a base type T is Identifiable<T>
template<typename TIdentifiable>
class Identifiable
{	
public:
    typedef Identification<TIdentifiable> ID;

    virtual ~Identifiable() {}

    //runtime id lookup base
    virtual const ID id() const = 0;

    //returns ids which can be compared to Identified<S,T>.id or to Identified<S,T>::sid.
    //These can be variadic, once I have a compiler that supports it
    static std::vector<ID> require()
    {
        return std::vector<ID>();
    }
    template <typename Ta>
    static std::vector<ID> require()
    {
        std::vector<ID> requirements;
        requirements.emplace_back(Ta::sid());
        return requirements;
    }
    template <typename Ta, typename Tb>
    static std::vector<ID> require()
    {
        std::vector<ID> requirements;
        requirements.push_back(Ta::sid());
        requirements.push_back(Tb::sid());
        return requirements;
    }
    template <typename Ta, typename Tb, typename Tc>
    static std::vector<ID> require()
    {
        std::vector<ID> requirements;
        requirements.push_back(Ta::sid());
        requirements.push_back(Tb::sid());
        requirements.push_back(Tc::sid());
        return requirements;
    }
    template <typename Ta, typename Tb, typename Tc, typename Td>
    static std::vector<ID> require()
    {
        std::vector<ID> requirements;
        requirements.push_back(Ta::sid());
        requirements.push_back(Tb::sid());
        requirements.push_back(Tc::sid());
        requirements.push_back(Td::sid());
        return requirements;
    }
};

//subtypes S are Identified<S,T> or optionally Identified<S,T,BaseClass>
template<typename TIdentified, typename TIdentifiable, typename TBase = TIdentifiable>
class Identified : public TBase
{	
public:
    virtual ~Identified() {}

    //compiletime id lookup impl
    static const typename TIdentifiable::ID sid() { return Identification<TIdentifiable>(typeid(TIdentifiable).name(), typeid(TIdentified).name()); }

    //runtime id lookup impl
    const typename TIdentifiable::ID id() const override { return TIdentified::sid(); }
};
