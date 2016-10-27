#include "Mesh.h"
#include <cassert>
#include "includes.h"
#include "Triangle.h"


Mesh::Mesh()
{
	vertices_vbo_id = 0;
	normals_vbo_id = 0;
	uvs_vbo_id = 0;
	colors_vbo_id = 0;
}

Mesh::Mesh( const Mesh& m )
{
	vertices = m.vertices;
	normals = m.normals;
	uvs = m.uvs;
	colors = m.colors;
}

Mesh::~Mesh()
{
	if( vertices_vbo_id ) glDeleteBuffersARB( 1, &vertices_vbo_id );
	if( normals_vbo_id ) glDeleteBuffersARB( 1, &normals_vbo_id );
	if( uvs_vbo_id ) glDeleteBuffersARB( 1, &uvs_vbo_id );
	if( colors_vbo_id ) glDeleteBuffersARB( 1, &colors_vbo_id );
}

void Mesh::clear()
{
	vertices.clear();
	normals.clear();
	uvs.clear();
	colors.clear();
}


void Mesh::render( int primitive )
{

	
	assert( vertices.size() && "No vertices in this mesh" );

	glEnableClientState( GL_VERTEX_ARRAY );

	if( vertices_vbo_id )
	{
		glBindBufferARB( GL_ARRAY_BUFFER_ARB, vertices_vbo_id );
		glVertexPointer( 3, GL_FLOAT, 0, NULL );
	}
	else
		glVertexPointer( 3, GL_FLOAT, 0, &fvertices[ 0 ] );

	if( normals.size() )
	{
		glEnableClientState( GL_NORMAL_ARRAY );
		if( normals_vbo_id )
		{
			glBindBufferARB( GL_ARRAY_BUFFER_ARB, normals_vbo_id );
			glNormalPointer( GL_FLOAT, 0, NULL );
		}
		else
			glNormalPointer( GL_FLOAT, 0, &normals[ 0 ] );
	}

	if( uvs.size() )
	{
		glEnableClientState( GL_TEXTURE_COORD_ARRAY );
		if( uvs_vbo_id )
		{
			glBindBufferARB( GL_ARRAY_BUFFER_ARB, uvs_vbo_id );
			glTexCoordPointer( 2, GL_FLOAT, 0, NULL );
		}
		else
			glTexCoordPointer( 2, GL_FLOAT, 0, &fuvs[ 0 ] );
	}

	if( colors.size() )
	{
		glEnableClientState( GL_COLOR_ARRAY );
		if( colors_vbo_id )
		{
			glBindBufferARB( GL_ARRAY_BUFFER_ARB, colors_vbo_id );
			glColorPointer( 4, GL_FLOAT, 0, NULL );
		}
		else
			glColorPointer( 4, GL_FLOAT, 0, &colors[ 0 ] );
	}

	glDrawArrays( primitive, 0, (GLsizei)fvertices.size() );
	glDisableClientState( GL_VERTEX_ARRAY );

	if( normals.size() )
		glDisableClientState( GL_NORMAL_ARRAY );
	if( uvs.size() )
		glDisableClientState( GL_TEXTURE_COORD_ARRAY );
	if( colors.size() )
		glDisableClientState( GL_COLOR_ARRAY );
	glBindBufferARB( GL_ARRAY_BUFFER_ARB, 0 );

	






}

void Mesh::createQuad( float center_x, float center_y, float w, float h, bool flip_uvs )
{
	vertices.clear();
	normals.clear();
	uvs.clear();
	colors.clear();

	//create six vertices (3 for upperleft triangle and 3 for lowerright)

	vertices.push_back( Vector3( center_x + w*0.5f, center_y + h*0.5f, 0.0f ) );
	vertices.push_back( Vector3( center_x - w*0.5f, center_y - h*0.5f, 0.0f ) );
	vertices.push_back( Vector3( center_x + w*0.5f, center_y - h*0.5f, 0.0f ) );
	vertices.push_back( Vector3( center_x - w*0.5f, center_y + h*0.5f, 0.0f ) );
	vertices.push_back( Vector3( center_x - w*0.5f, center_y - h*0.5f, 0.0f ) );
	vertices.push_back( Vector3( center_x + w*0.5f, center_y + h*0.5f, 0.0f ) );

	//texture coordinates
	uvs.push_back( Vector2( 1.0f, flip_uvs ? 0.0f : 1.0f ) );
	uvs.push_back( Vector2( 0.0f, flip_uvs ? 1.0f : 0.0f ) );
	uvs.push_back( Vector2( 1.0f, flip_uvs ? 1.0f : 0.0f ) );
	uvs.push_back( Vector2( 0.0f, flip_uvs ? 0.0f : 1.0f ) );
	uvs.push_back( Vector2( 0.0f, flip_uvs ? 1.0f : 0.0f ) );
	uvs.push_back( Vector2( 1.0f, flip_uvs ? 0.0f : 1.0f ) );

	//all of them have the same normal
	normals.push_back( Vector3( 0.0f, 0.0f, 1.0f ) );
	normals.push_back( Vector3( 0.0f, 0.0f, 1.0f ) );
	normals.push_back( Vector3( 0.0f, 0.0f, 1.0f ) );
	normals.push_back( Vector3( 0.0f, 0.0f, 1.0f ) );
	normals.push_back( Vector3( 0.0f, 0.0f, 1.0f ) );
	normals.push_back( Vector3( 0.0f, 0.0f, 1.0f ) );
}


void Mesh::createPlane( float size )
{
	vertices.clear();
	normals.clear();
	uvs.clear();
	colors.clear();

	//create six vertices (3 for upperleft triangle and 3 for lowerright)

	vertices.push_back( Vector3( size, 0, size ) );
	vertices.push_back( Vector3( size, 0, -size ) );
	vertices.push_back( Vector3( -size, 0, -size ) );
	vertices.push_back( Vector3( -size, 0, size ) );
	vertices.push_back( Vector3( size, 0, size ) );
	vertices.push_back( Vector3( -size, 0, -size ) );

	//all of them have the same normal
	normals.push_back( Vector3( 0, 1, 0 ) );
	normals.push_back( Vector3( 0, 1, 0 ) );
	normals.push_back( Vector3( 0, 1, 0 ) );
	normals.push_back( Vector3( 0, 1, 0 ) );
	normals.push_back( Vector3( 0, 1, 0 ) );
	normals.push_back( Vector3( 0, 1, 0 ) );

	//texture coordinates
	uvs.push_back( Vector2( 1, 1 ) );
	uvs.push_back( Vector2( 1, 0 ) );
	uvs.push_back( Vector2( 0, 0 ) );
	uvs.push_back( Vector2( 0, 1 ) );
	uvs.push_back( Vector2( 1, 1 ) );
	uvs.push_back( Vector2( 0, 0 ) );
}


void Mesh::createCube(float size)
{
	vertices.clear();
	normals.clear();
	uvs.clear();
	colors.clear();

	//create six vertices (3 for upperleft triangle and 3 for lowerright)

	vertices.push_back(Vector3(size, -size, size));
	vertices.push_back(Vector3(size, -size, -size));
	vertices.push_back(Vector3(-size, -size, -size));
	vertices.push_back(Vector3(-size, -size, size));
	vertices.push_back(Vector3(size, -size, size));
	vertices.push_back(Vector3(-size, -size, -size));

	vertices.push_back(Vector3(size, size, size));
	vertices.push_back(Vector3(size, size, -size));
	vertices.push_back(Vector3(-size, size, -size));
	vertices.push_back(Vector3(-size, size, size));
	vertices.push_back(Vector3(size, size, size));
	vertices.push_back(Vector3(-size, size, -size));
	
	vertices.push_back(Vector3(size, size, size));
	vertices.push_back(Vector3(size, size, -size));
	vertices.push_back(Vector3(size, -size, -size));
	vertices.push_back(Vector3(size, -size, size));
	vertices.push_back(Vector3(size, size, size));
	vertices.push_back(Vector3(size, -size, -size));
	
	vertices.push_back(Vector3(size, size, size));
	vertices.push_back(Vector3(-size, size, size));
	vertices.push_back(Vector3(-size, -size, size));
	vertices.push_back(Vector3(size, -size, size));
	vertices.push_back(Vector3(size, size, size));
	vertices.push_back(Vector3(-size, -size, size));
	
	vertices.push_back(Vector3(size, size, -size));
	vertices.push_back(Vector3(-size, size, -size));
	vertices.push_back(Vector3(-size, -size, -size));
	vertices.push_back(Vector3(size, -size, -size));
	vertices.push_back(Vector3(size, size, -size));
	vertices.push_back(Vector3(-size, -size, -size));

	

	vertices.push_back(Vector3(-size, -size, size) * -1);
	vertices.push_back(Vector3(-size, size, size) * -1);
	vertices.push_back(Vector3(-size, -size, -size) * -1);
	vertices.push_back(Vector3(-size, -size, -size) * -1);
	vertices.push_back(Vector3(-size, size, size) * -1);
	vertices.push_back(Vector3(-size, size, -size) * -1);

	vertices.push_back(Vector3(size, -size, size));
	vertices.push_back(Vector3(size, size, size));
	vertices.push_back(Vector3(size, -size, -size));
	vertices.push_back(Vector3(size, -size, -size));
	vertices.push_back(Vector3(size, size, size));
	vertices.push_back(Vector3(size, size, -size));
	

	//all of them have the same normal

	normals.push_back(Vector3(0, -1, 0));
	normals.push_back(Vector3(0, -1, 0));
	normals.push_back(Vector3(0, -1, 0));
	normals.push_back(Vector3(0, -1, 0));
	normals.push_back(Vector3(0, -1, 0));
	normals.push_back(Vector3(0, -1, 0));
	
	normals.push_back(Vector3(0, 1, 0));
	normals.push_back(Vector3(0, 1, 0));
	normals.push_back(Vector3(0, 1, 0));
	normals.push_back(Vector3(0, 1, 0));
	normals.push_back(Vector3(0, 1, 0));
	normals.push_back(Vector3(0, 1, 0));
	
	normals.push_back(Vector3(-1, 0, 0));
	normals.push_back(Vector3(-1, 0, 0));
	normals.push_back(Vector3(-1, 0, 0));
	normals.push_back(Vector3(-1, 0, 0));
	normals.push_back(Vector3(-1, 0, 0));
	normals.push_back(Vector3(-1, 0, 0));
	/*
	normals.push_back(Vector3(0, 0, 1));
	normals.push_back(Vector3(0, 0, 1));
	normals.push_back(Vector3(0, 0, 1));
	normals.push_back(Vector3(0, 0, 1));
	normals.push_back(Vector3(0, 0, 1));
	normals.push_back(Vector3(0, 0, 1));
	*/
	

	//texture coordinates
	uvs.push_back(Vector2(1, 1));
	uvs.push_back(Vector2(1, 0));
	uvs.push_back(Vector2(0, 0));
	uvs.push_back(Vector2(0, 1));
	uvs.push_back(Vector2(1, 1));
	uvs.push_back(Vector2(0, 0));

	uvs.push_back(Vector2(1, 1));
	uvs.push_back(Vector2(1, 0));
	uvs.push_back(Vector2(0, 0));
	uvs.push_back(Vector2(0, 1));
	uvs.push_back(Vector2(1, 1));
	uvs.push_back(Vector2(0, 0));

	uvs.push_back(Vector2(1, 1));
	uvs.push_back(Vector2(1, 0));
	uvs.push_back(Vector2(0, 0));
	uvs.push_back(Vector2(0, 1));
	uvs.push_back(Vector2(1, 1));
	uvs.push_back(Vector2(0, 0));

	uvs.push_back(Vector2(1, 1));
	uvs.push_back(Vector2(1, 0));
	uvs.push_back(Vector2(0, 0));
	uvs.push_back(Vector2(0, 1));
	uvs.push_back(Vector2(1, 1));
	uvs.push_back(Vector2(0, 0));

	uvs.push_back(Vector2(1, 1));
	uvs.push_back(Vector2(1, 0));
	uvs.push_back(Vector2(0, 0));
	uvs.push_back(Vector2(0, 1));
	uvs.push_back(Vector2(1, 1));
	uvs.push_back(Vector2(0, 0));
}

void Mesh::loadASE(const std::string& fileName, float scale) {

	
	TextParser t(addCurrentPath(fileName).c_str());

	//Buscamos por palabra clave y guardamos longitud
	t.seek("*MESH_NUMVERTEX");
	int numVertices = t.getint();

	t.seek("*MESH_NUMFACES");
	int numFaces = t.getint();

	//Tenemos en cuenta las caras para la lista de triangulos
	faces.resize(numFaces);


	for (int i = 0; i < numVertices; i++) {

		t.seek("*MESH_VERTEX");
		t.getword();

		float v1 = t.getfloat();
		float v2 = t.getfloat();
		float v3 = t.getfloat();

		Vector3 v = Vector3(v1*scale, v2*scale, v3*scale);
		//************
		vertices.push_back(Vector3(v.x, v.z ,v.y)); 
		//*********************
	}

	//Guardamos triangulos, en cada posicion de las instancias de la lista, un vertice
		for (int i = 0; i< numFaces; i++) {


			t.seek("*MESH_FACE");
			t.getword();

			t.seek("A:");
			faces[i].a = t.getint();

			t.seek("B:");
			faces[i].b = t.getint();

			t.seek("C:");
			faces[i].c = t.getint();

		}

		//Push a un vector
		for (int i = 0; i < numFaces; i++) {

			const Triangle & t = faces[i];
			fvertices.push_back(vertices[t.a]);
			fvertices.push_back(vertices[t.b]);
			fvertices.push_back(vertices[t.c]);

		}

		t.seek("*MESH_NUMTVERTEX");
		int numTextures = t.getint();

			//Conseguir las coordenadas de textura
			for (int i = 0; i < numTextures; i++) {

				t.seek("*MESH_TVERT");
				t.getword();

				float f1 = t.getfloat();
				float f2 = t.getfloat();
				float f3 = t.getfloat();

				Vector2 uv = Vector2(f1, f2);
				uvs.push_back(Vector2(uv.x, uv.y));
			}


			t.seek("*MESH_NUMTVFACES");
			int numTextureFaces = t.getint();
			faces.resize(numTextureFaces);
			// Conseguimos las texturas de cada una de las caras
			for (int i = 0; i < numTextureFaces; i++) {

				t.seek("*MESH_TFACE");
				t.getword();

				faces[i].a = t.getint();
				faces[i].b = t.getint();
				faces[i].c = t.getint();

			}

			//en fuvs, cargamos la info
			for (int i = 0; i < numTextureFaces; i++) {

				const Triangle & tv = faces[i];
				fuvs.push_back(uvs[tv.a]);
				fuvs.push_back(uvs[tv.b]);
				fuvs.push_back(uvs[tv.c]);

			}


			//Idem, pero con las normales.
			for (int i = 0; i < numTextureFaces; i++) {

				t.seek("*MESH_FACENORMAL");
				normals.push_back(Vector3(t.getfloat(), t.getfloat(), t.getfloat()));// Floats pq son coordenadas directas

			}

		

	}






