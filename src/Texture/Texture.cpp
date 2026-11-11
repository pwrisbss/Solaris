#include "Texture.hpp"

namespace Solaris {

Texture::Texture() : 
	data(NoTexture) {}

Texture::Texture(const CastedResource<unsigned char>& data) :
	data(data) {}

Texture::~Texture() {}

template<typename _param_type>
_param_type Texture::GetParam(GLenum name) {
	return std::get<_param_type>(this->params[name]);
}

template int 	Texture::GetParam(GLenum);
template float 	Texture::GetParam(GLenum);

CastedResource<unsigned char> Texture::GetTexData() {
	return this->data;
}

void Texture::SetTexData(const CastedResource<unsigned char> &data) {
	this->data = data;
}

void Texture::SetParam(GLenum name, TextureParameterValue value) {
	this->params[name] = value;
}

void Texture::DeleteParam(GLenum name) {
	this->params.erase(name);
}

}