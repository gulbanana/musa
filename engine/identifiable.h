#pragma once

#define IDENTIFIABLE(itype, idtype, ...)\
enum class idtype						\
{										\
	__VA_ARGS__							\
};										\
										\
class itype								\
{										\
public:									\
	virtual ~itype() {}					\
};

#define IDENTIFIABLE_COLLECTION(iname, iplural, itype, idtype)	\
																\
protected:														\
	std::map<idtype, std::unique_ptr<itype>> iplural;			\
	template<typename itype>									\
	void add_iname(std::unique_ptr<itype> iname)				\
	{															\
		iplural[type::ID] = std::move(iname);					\
	}															\
																\
public:															\
	template<typename itype>									\
	inline bool has_iname()										\
	{															\
		return has_iname(itype::ID);							\
	}															\
																\
	bool has_iname(int id)										\
	{															\
		return iplural.count(id) > 0;							\
	}															\
																\
	template<typename itype> itype* get_iname()					\
	{															\
		return static_cast<itype*>(components[itype::ID].get());\
	}													