/**
 * @file ResourceMan.hpp
 * @author pwr (pwr.is.bss@tuta.io)
 * @brief Solaris Resource Manager
 * @version alpha-0.0
 * @date 2026-10-19
 * 
 * @copyright GNU General Public License (see COPYING) 
 * 
 */

/**
 * @page resourceman Resource Management
 *
 * Resources and resource management are both very crucial components of Solaris. You will encounter a lot of Solaris
 * components which you'll need to assign resource(s) to for them to function properly.
 *
 * @section resourceman-resource Resources
 *
 * A resource is any memory block which Solaris does not explicitly define its size. Some of the things that fall in
 * this category are: texture data, mesh data, an array of integers, shader source code, etc. to name a few.
 *
 * To define a resource in Solaris, you must use the `Resource` or `CastedResource` type. The difference between these
 * two resource types will be explained further on.
 *
 * @code {.cpp}
 * #include <ResourceMan/ResourceMan.hpp>
 *
 * int arr[] = { 0, 1, 2, 3, 4, 5 };
 * Resource foo = {
 *     .size = sizeof(arr),     // size of the resource in bytes
 *     .pdata = (void*)arr      // a void pointer to the beginning of the resource
 * };
 *
 * char some_cstring[] = "Hello World!";
 * CastedResource<char> bar = {
 *     .len = sizeof(some_cstring) / sizeof(char),     // number of `char' elements in this resource
 *     .pdata = some_cstring                           // a `char*' pointer to the beginning of the
 *                                                     // resource (no casting needed here)
 * };
 * @endcode
 *
 * @subsection resourceman-typename-resource The Resource Type
 *
 * The `Resource` type is conventionally used for resources with unspecified data types, or as a generic resource type.
 * Most Solaris functions will expect a resource with a known data type (e.g., the `Model` @ref renderobject "render object"
 * expects a `CastedResource<float>` as its mesh data, and `CastedResource<unsigned char>` as its texture). As such, one
 * could say that the `Resource` type acts mostly as an intermediary type.
 *
 * @subsection resourceman-typename-castedresource The CastedResource Type
 *
 * The `CastedResource` type is used for resources with known data types. `CastedResource` accepts a `typename` template
 * parameter, the value of which is used to determine the pointer type of the resource.
 *
 * The two key differences between a `CastedResource` and a `Resource` is that, first, unlike the `Resource` type,
 * `CastedResource` isn't necessarily supposed to hold a `void` pointer to the resource; rather, it is up to the programmer
 * to specify what type of resource the `CastedResource` is pointing to; and second, instead of a `size` property,
 * `CastedResource` holds a `len` property which determines how many values the resource is holding. i.e., assuming the
 * resource is an array, `len` is how many elements the array is holding
 *
 * @subsubsection resourceman-casting-resources Casting Resources
 *
 * Consider the following example of manually
 * casting a `Resource` to a `CastedResource<int>`.
 *
 * @attention It's not recommended and heavily discouraged to manually cast a `Resource` type. Instead, one must use the
 * `CastResource` function to do so, which will be expanded upon later.
 *
 * @code {.cpp}
 * #include <ResourceMan/ResourceMan.hpp>
 * int data[] = { 0, 1, 2, 3, 4, 5 };
 *
 * Resource uncasted = {
 *     .size = sizeof(data),
 *     .pdata = (void*)data
 * };
 *
 * CastedResource<int> casted = {
 *     .len = uncasted.size / sizeof(int),     // get the # of elements in array
 *     .pdata = data                           // no need for casting -- resource is already
 *                                             // of the expected type
 * };
 * @endcode
 *
 * As specified above, this is a highly discouraged practice. One must instead use Solaris's own casting function,
 * `CastResource`:
 *
 * @code {.cpp}
 * ...
 * CastedResource<int> casted = CastResource<int>(uncasted);
 * @endcode
 *
 * In the example above, we used the previously-defined resource `uncasted`, but instead of casting it manually, we used
 * the `CastResource` function. `CastResource` accepts a single `typename` template parameter, a single `Resource` parameter
 * , and returns a `CastedResource` casted to the specified typename.
 *
 * @section resourceman-the-resource-manager The Resource Manager
 * @todo find someone to document ts for u cuz i aint doing this
 *
 * @see Solaris::ResourceMan
 * @see Solaris::Resource
 * @see Solaris::CastedResource
 * @see Solaris::CastResource
 *
 */

#ifndef SOLARIS_RESOURCEMAN_H
#define SOLARIS_RESOURCEMAN_H

#include <cstdint>
#include <iostream>
#include <fstream>
#include <unordered_map>

namespace Solaris {

/**
 * @struct Resource
 * @brief Holds information about a specific resource.
 *
 * @details In other words, an object of type Resource is a vector pointing to a memory block (that is, the size of
 * the memory block and a pointer to the start of said memory block). Comparing Resource objects are supported.
 * 
 */
struct Resource {
	/**
	 * @brief Size of the resource data in bytes
	 * 
	 */
	unsigned long size;

	/**
	 * @brief Pointer to resource data
	 * 
	 */
	void * pdata;

	/**
	 * @brief Check if the other Resource points to the same memory block with the same size as this Resource.
	 * 
	 * @param other Reference to the Resource object being compared against.
	 * @return true if the two `Resource`s point to the same memory block with the same size.
	 * @return false if otherwise.
	 */
	bool operator==(const Resource& other) {
		return (this->size  == other.size) &&
		       (this->pdata == other.pdata);
	};

	/**
	 * @brief Check if the other Resource doesn't point to the same memory block and/or isn't the same size as
	 * this Resource.
	 * 
	 * @param other Reference to the Resource object being compared against.
	 * @return true if the other Resource doesn't point to the same memory block and/or isn't the same size as
	 * this Resource
	 * @return false if otherwise 
	 */
	bool operator!=(const Resource& other) {
		return (this->size  != other.size) ||
		       (this->pdata != other.pdata);
	};
};

/**
 * @struct CastedResource
 * @brief Holds information about a specific resource with known data type.
 *
 * @details Same as Resource except for resources with known data types. 
 * @tparam _data_type Typename of the resource's data.
 * @attention The _data_type template parameter is the type of the data the CastedResource points to, not the
 * type of the pointer itself (e.g. if you have an array of `unsigned char`s, its appropriate CastedResource
 * pointing to said array would be `CastedResource<unsigned char>`, not `CastedResource<unsigned char*>`)
 * @see Resource
 */
template<typename _data_type>
struct CastedResource {
	/**
	 * @brief Length of the resource data. i.e., number of @ref CastedResource "_data_type" elements in this
	 * specific resource. Not to be confused with `Resource::size`.
	 * 
	 */
	unsigned long len;

	/**
	 * @brief Pointer to resource data.
	 * 
	 */
	_data_type * pdata;

	/**
	 * @brief Same as `Resource::operator==()`, except accepts a CastedResource of the same type.
	 * 
	 * @param other The other CastedResource being compared against.
	 * @see Resource::operator==()
	 */
	bool operator==(const CastedResource<_data_type>& other) {
		return (this->len   == other.len) &&
		       (this->pdata == other.pdata);
	};

	/**
	 * @brief Same as `Resource::operator!=()`, except accepts a CastedResource of the same type.
	 * 
	 * @param other The other CastedResource being compared against.
	 * @see Resource::operator!=()
	 */
	bool operator!=(const CastedResource<_data_type>& other) {
		return (this->len   != other.len) ||
		       (this->pdata != other.pdata);
	};
};

/**
 * @brief Casts a Resource object to a CastedResource<_cast_type>.
 * 
 * @details Conventionally, a Resource object points to a resource whom its data type is unknown. Mainly, it only
 * exists so that a resource manager can store, process and manage resources of any type. As such, most Solaris
 * components will ask for resources with known data types. See @ref resourceman "Resource Management".
 * @tparam _cast_type Data type to cast the Resource to.
 * @param resource Resource to be casted.
 * @return CastedResource<_cast_type>
 */
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

/**
 * @class ResourceMan
 * @brief Resource Manager class
 *
 * @details Manages your program's assets and resources.
 * @see @ref resourceman
 * 
 */
class ResourceMan {
private:
	unsigned next_id;
	unsigned NewResource();

public:
	/**
	 * @brief Hashmap of the resources managed by this ResourceMan.
	 * 
	 */
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