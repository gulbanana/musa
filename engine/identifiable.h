#pragma once

#define IDENTIFIABLE(...) \
public:                   \
    enum class ID         \
    {                     \
        __VA_ARGS__       \
    }

#define IDENTIFIABLE_COLLECTION(itype, iname, iplural) \
public:                                                \
    template<typename T>                               \
    void add_##iname(std::unique_ptr<T> iname)         \
    {                                                  \
        iplural[T::ID] = std::move(iname);             \
    }                                                  \
                                                       \
    template<typename T>                               \
    inline bool has_##iname()                          \
    {                                                  \
        return has_##iname(T::ID);                     \
	}                                                  \
                                                       \
    bool has_##iname(itype::ID id)                     \
    {                                                  \
        return iplural.count(id) > 0;                  \
    }                                                  \
                                                       \
    template<typename T> T* get_##iname()              \
    {                                                  \
        return static_cast<T*>(iplural[T::ID].get());  \
    }                                                  \
protected:                                             \
    std::map<itype::ID, std::unique_ptr<itype>> iplural	
