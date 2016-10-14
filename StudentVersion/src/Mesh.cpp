#include "Mesh.h"
#include <cassert>
#include "includes.h"

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
		glVertexPointer( 3, GL_FLOAT, 0, &vertices[ 0 ] );

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
			glTexCoordPointer( 2, GL_FLOAT, 0, &uvs[ 0 ] );
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

	glDrawArrays( primitive, 0, (GLsizei)vertices.size() );
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



