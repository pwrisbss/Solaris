#ifndef SOLARIS_TEXTURE_H
#define SOLARIS_TEXTURE_H

#include <ResourceMan/ResourceMan.hpp>
#include <Renderer/Renderer.hpp>
#include <Objects/Model/Model.hpp>
#include <memory>

namespace Solaris {

typedef enum TextureParameterValueType {
	INTEGER = 0,
	FLOAT,
} TextureParameterValueType;

typedef struct TextureParameterValue {
	TextureParameterValueType type;
	union {
		std::shared_ptr<int> pint;
		std::shared_ptr<float> pfloat;
	};
} TextureParameterValue;

class Texture {
private:
	CastedResource<unsigned char> data;
	std::unordered_map<GLenum, TextureParameterValue> params;

public:
	Texture();
	Texture(CastedResource<unsigned char> data);
	~Texture();

	template<typename _param_type>
	_param_type GetParam(GLenum name);
	void SetParam(GLenum name, int value);
	void SetParam(GLenum name, float value);
	void DeleteParam(GLenum name);

};

}

#endif // SOLARIS_TEXTURE_H
