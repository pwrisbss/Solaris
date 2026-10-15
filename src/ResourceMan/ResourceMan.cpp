#include "ResourceMan.hpp"

namespace Solaris {

ResourceMan::ResourceMan()
	: next_id(1) {}

ResourceMan::~ResourceMan() {}

unsigned ResourceMan::LoadResource(std::string file_location, bool load_as_string) {
	Resource resource;
	std::ifstream resource_file;
	unsigned resource_key;
	unsigned long resource_size;

	// open file
	resource_file.open(file_location, std::ios::binary | std::ios::ate);

	if (!resource_file.is_open()) {
		// TODO add error handling
		std::cout << "error loading file: " << file_location << std::endl;
	}

	// find size
	resource_size = resource_file.tellg();
	resource_file.seekg(0, std::ios::beg);

	// read into memory
	char * memblock;
	if (load_as_string) {
		memblock = new char[resource_size + 1];
		memblock[resource_size] = '\0';
	} else {
		memblock = new char[resource_size];
	}
	resource_file.read(memblock, resource_size);

	resource.size = resource_size;
	resource.pdata = (void*)memblock;

	resource_key = this->NewResource();
	this->resources[resource_key] = resource;

	return resource_key;
}

unsigned ResourceMan::LoadResource(std::string vse_container_location, uint64_t offset) {
	// TODO add error handling
	// aka. throw a not implemented error when this function is called
}

unsigned ResourceMan::OwnResource(void *resource_address, unsigned long resource_size) {
	unsigned resource_key = this->NewResource();

	this->resources[resource_key].pdata = resource_address;
	this->resources[resource_key].size = resource_size;

	return resource_key;
}

void ResourceMan::DestroyResource(unsigned int id, bool unload) {
	if (unload) {
		delete[] static_cast<char*>(this->resources[id].pdata);
	}
	this->resources.erase(id);

}

unsigned ResourceMan::NewResource() {
	// calculate the next `next_id'
	unsigned next = 1;
	while (next != this->next_id) {
		if (this->resources.find(next) != this->resources.end()) {
			next++;
		} else {
			this->next_id = next;
			break;
		}
	}
	
	unsigned this_next = this->next_id;
	if (next == this_next) {
		this->next_id++;
	}

	return this_next;
}

Resource ResourceMan::FetchResource(unsigned id) {
	// TODO add error handling
	return this->resources[id];
}

}