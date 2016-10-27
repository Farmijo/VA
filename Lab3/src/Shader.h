/*  by Javi Agenjo 2013 UPF  javi.agenjo@gmail.com
	This allows to use compile and use shaders when rendering. Used for advanced lighting.
*/

#ifndef SHADER_H
#define SHADER_H

#include "includes.h"
#include <string>
#include <map>
#include "Maths.h"

#ifdef _DEBUG
#define CHECK_SHADER_VAR(a,b) if (a == -1) return
//#define CHECK_SHADER_VAR(a,b) if (a == -1) { std::cout << "Shader error: Var not found in shader: " << b << std::endl; return; } 
#else
#define CHECK_SHADER_VAR(a,b) if (a == -1) return
#endif

class Texture;

class Shader
{
	int last_slot;

	static bool s_ready; //used to initialize shader vars

public:
	Shader();
	virtual ~Shader();

	virtual void setFilenames( const std::string& vsf, const std::string& psf ); //set but not compile
	virtual bool compile();
	virtual bool recompile();

	virtual bool load( const std::string& vsf, const std::string& psf );

	//internal functions
	virtual bool compileFromMemory( const std::string& vsm, const std::string& psm );
	virtual void release();
	virtual void enable();
	virtual void disable();

	static void init();
	static void disableShaders();

	//uniform exist
	virtual bool IsVar( const std::string& varname ) { return ( getUniformLocation( varname ) != -1 ); }

	//upload
	virtual void setFloat( const std::string& varname, const float& input ) { setUniform1( varname, input ); }
	virtual void setVector3( const std::string& varname, const Vector3& input ) { setUniform3( varname, input.x, input.y, input.z ); }
	virtual void setMatrix44( const std::string& varname, const float* m );
	virtual void setMatrix44( const std::string& varname, const Matrix44 &m );

	virtual void setUniform1Array( const std::string& varname, const float* input, const int count );
	virtual void setUniform2Array( const std::string& varname, const float* input, const int count );
	virtual void setUniform3Array( const std::string& varname, const float* input, const int count );
	virtual void setUniform4Array( const std::string& varname, const float* input, const int count );

	virtual void setUniform1Array( const std::string& varname, const int* input, const int count );
	virtual void setUniform2Array( const std::string& varname, const int* input, const int count );
	virtual void setUniform3Array( const std::string& varname, const int* input, const int count );
	virtual void setUniform4Array( const std::string& varname, const int* input, const int count );

	virtual void setUniform1( const std::string& varname, const int input1 );
	virtual void setUniform2( const std::string& varname, const int input1, const int input2 );
	virtual void setUniform3( const std::string& varname, const int input1, const int input2, const int input3 );
	virtual void setUniform3( const std::string& varname, const Vector3& input ) { setUniform3( varname, input.x, input.y, input.z ); }
	virtual void setUniform4( const std::string& varname, const int input1, const int input2, const int input3, const int input4 );

	virtual void setUniform1( const std::string& varname, const float input );
	virtual void setUniform2( const std::string& varname, const float input1, const float input2 );
	virtual void setUniform3( const std::string& varname, const float input1, const float input2, const float input3 );
	virtual void setUniform4( const std::string& varname, const float input1, const float input2, const float input3, const float input4 );

	virtual void setTexture( const std::string& varname, const unsigned int tex );
	virtual void setTexture( const std::string& varname, const Texture& texture );

	virtual int getAttribLocation( const std::string& varname );
	virtual int getUniformLocation( const std::string& varname );

	std::string getInfoLog() const;
	bool hasInfoLog() const;
	bool compiled;

	static Shader* Load( const std::string& vsf, const std::string& psf );
	static void ReloadAll();
	static std::map<std::string, Shader*> s_Shaders;

protected:

	bool readFile( const std::string& filename, std::string& content );

	std::string info_log;
	std::string vs_filename;
	std::string ps_filename;

	bool createVertexShaderObject( const std::string& shader );
	bool createFragmentShaderObject( const std::string& shader );
	bool createShaderObject( unsigned int type, GLuint& handle, const std::string& shader );
	void saveShaderInfoLog( GLuint obj );
	void saveProgramInfoLog( GLuint obj );

	bool validate();

	GLuint vs;
	GLuint fs;
	GLuint program;
	std::string log;

	//this is a hack to speed up shader usage (save info locally)
private:

	typedef std::map<const std::string, int> loctable;

	loctable locations;

public:
	GLint getLocation( const std::string& varname );
};

#endif