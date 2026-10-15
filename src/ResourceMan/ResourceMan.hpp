// resource manager

#ifndef SOLARIS_RESOURCEMAN_H
#define SOLARIS_RESOURCEMAN_H

#include <cstdint>
#include <iostream>
#include <fstream>
#include <unordered_map>

namespace Solaris {

struct Resource {
	unsigned long size;
	void * pdata;
};

template<typename _data_type>
struct CastedResource {
	unsigned long len;
	_data_type * pdata;
};

template<typename _cast_type> CastedResource<_cast_type> CastResource(Resource& resource) {
	CastedResource<_cast_type> casted;
	unsigned type_size = sizeof(_cast_type);
	unsigned resource_size;

	// TODO add error handling
	// for when resource_size isnt divisible by type_size

	resource_size = resource.size;
	casted.len = resource_size / type_size;
	casted.pdata = (_cast_type*)resource.pdata;

	return casted;
}

class ResourceMan {
private:
unsigned next_id;
unsigned NewResource();

public:
std::unordered_map<unsigned, Resource> resources;
	ResourceMan();
	~ResourceMan();

	Resource FetchResource(unsigned id);
	unsigned LoadResource(std::string file_location, bool load_as_string = false);
	unsigned LoadResource(std::string vse_container_location, uint64_t offset);	// NOT IMPLEMENTED
	unsigned OwnResource(void * resource_address, unsigned long resource_size);
	void DestroyResource(unsigned id, bool unload = true);



	template<typename _cast_type> CastedResource<_cast_type>
	FetchCasted(unsigned id) { return CastResource<_cast_type>(this->resources[id]); };
};

}

#endif // SOLARIS_RESOURCEMAN_H