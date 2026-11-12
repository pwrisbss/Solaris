#ifndef SOLARIS_TEXTURE_H
#define SOLARIS_TEXTURE_H

#include <ResourceMan/ResourceMan.hpp>
#include <Renderer/Renderer.hpp>
#include <memory>
#include <variant>

namespace Solaris {

const CastedResource<unsigned char> NoTexture = {0, nullptr};

typedef std::variant<int, float> TextureParameterValue;

class Texture {
private:
	CastedResource<unsigned char> data;
	
public:
	std::unordered_map<GLenum, TextureParameterValue> params;
	Texture();
	Texture(const CastedResource<unsigned char>& data);
	~Texture();

	template<typename _param_type>
	_param_type GetParam(GLenum name);
	CastedResource<unsigned char> GetTexData();
	void SetTexData(const CastedResource<unsigned char>& data);
	void SetParam(GLenum name, TextureParameterValue value);
	void DeleteParam(GLenum name);
};

}

#endif // SOLARIS_TEXTURE_H
