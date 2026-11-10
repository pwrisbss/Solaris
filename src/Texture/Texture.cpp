#include "Texture.hpp"

namespace Solaris {

Texture::Texture() : 
	data(NoTexture) {}

Texture::Texture(CastedResource<unsigned char> data) :
	data(data) {}

Texture::~Texture() {}

template<typename _param_type>
_param_type Texture::GetParam(GLenum name) {
	return (this->params[name].type == INTEGER) ?
		(*this->params[name].pint) :
		(*this->params[name].pfloat);
}

template int 	Texture::GetParam(GLenum);
template float 	Texture::GetParam(GLenum);

void Texture::SetParam(GLenum name, float value) {
	this->params[name].type = FLOAT;
	this->params[name].pfloat = std::make_shared<float>(value);
}

void Texture::SetParam(GLenum name, int value) {
	this->params[name].type = INTEGER;
	this->params[name].pint = std::make_shared<int>(value);
}

void Texture::DeleteParam(GLenum name) {
	this->params.erase(name);
}

}