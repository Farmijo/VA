#include "Texture.h"
#include "extra/ImageLoader.h"
#include "Utils.h"
#include <memory>

Texture::Texture( void )
    : m_GLTexture( -1 )
{

}

Texture::Texture( const std::string& p_oFileName )
	: m_GLTexture( -1 )
{
	load( p_oFileName );
}

Texture::~Texture( void )
{
    releaseTexture();
}

void Texture::releaseTexture( void )
{
    if( m_GLTexture > -1 )
    {
        glDeleteTextures( 1, &m_GLTexture );
        glFinish();
    }
}

void Texture::load( const std::string& p_oFileName )
{
	// EXERCISE PRACT 3

	// EXERCISE PRACT 3
}

