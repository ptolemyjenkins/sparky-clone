#include "basicMeshs.h"
namespace sparky { namespace util {
	void BasicMesh::planeMesh(graphics::Mesh* mesh)
	{
		IndexedModel model;
		model.positions = { maths::vec3(-1,0,-1),
							maths::vec3(1,0,-1),
							maths::vec3(-1,0,1),
							maths::vec3(1,0,1) };

		model.texCoords = { maths::vec2(0,1),
							maths::vec2(1,1),
							maths::vec2(0,0),
							maths::vec2(1,0) };
		model.indices = { 0,2,1,1,2,3 };
		model.calcNormals();
		model.calcTangents();
		mesh->init(&model);
	}

	void BasicMesh::plane2Mesh(graphics::Mesh* mesh)
	{
		IndexedModel model;
		model.positions = { maths::vec3(-1,0,-1),
							maths::vec3(1,0,-1),
							maths::vec3(-1,0,1),
							maths::vec3(1,0,1),
							maths::vec3(-1,0,-1),
							maths::vec3(1,0,-1),
							maths::vec3(-1,0,1),
							maths::vec3(1,0,1) };

		model.texCoords = { maths::vec2(0,1),
							maths::vec2(1,1),
							maths::vec2(0,0),
							maths::vec2(1,0),
							maths::vec2(1,1),
							maths::vec2(0,1),
							maths::vec2(1,0),
							maths::vec2(0,0) };
		model.indices = { 0,2,1,1,2,3,4,5,6,5,7,6 };
		model.calcNormals();
		model.calcTangents();
		mesh->init(&model);
	}

	void BasicMesh::cubeMesh(graphics::Mesh * mesh)
	{
		IndexedModel model;
		model.positions = { maths::vec3(1, -1, -1),
							maths::vec3(-1, -1, -1),
							maths::vec3(1, -1, 1),
							maths::vec3(-1, -1, 1),
							maths::vec3(-1, 1, -1),
							maths::vec3(1, 1, -1),
							maths::vec3(-1, 1, 1),
							maths::vec3(1, 1, 1),
							maths::vec3(-1, -1, -1),
							maths::vec3(1, -1, -1),
							maths::vec3(-1, 1, -1),
							maths::vec3(1, 1, -1),
							maths::vec3(1, -1, 1),
							maths::vec3(-1, -1, 1),
							maths::vec3(1, 1, 1),
							maths::vec3(-1, 1, 1),
							maths::vec3(-1, -1, 1),
							maths::vec3(-1, -1, -1),
							maths::vec3(-1, 1, 1),
							maths::vec3(-1, 1, -1),
							maths::vec3(1, -1, -1),
							maths::vec3(1, -1, 1),
							maths::vec3(1, 1, -1),
							maths::vec3(1, 1, 1) };


		model.texCoords = {
			maths::vec2(1, 0),
			maths::vec2(0, 0),
			maths::vec2(1, 1),
			maths::vec2(0, 1),
			maths::vec2(0, 1),
			maths::vec2(1, 1),
			maths::vec2(0, 0),
			maths::vec2(1, 0),
			maths::vec2(0, 1),
			maths::vec2(1, 1),
			maths::vec2(0, 0),
			maths::vec2(1, 0),
			maths::vec2(1, 0),
			maths::vec2(0, 0),
			maths::vec2(1, 1),
			maths::vec2(0, 1),
			maths::vec2(0, 1),
			maths::vec2(1, 1),
			maths::vec2(0, 0),
			maths::vec2(1, 0),
			maths::vec2(0, 1),
			maths::vec2(1, 1),
			maths::vec2(0, 0),
			maths::vec2(1, 0),
		};
		model.indices = {	0,2,1,1,2,3,
							4,6,5,5,6,7,
							8,10,9,9,10,11,
							12,14,13,13,14,15,
							16,18,17,17,18,19,
							20,22,21,21,22,23 };
		model.calcNormals();
		model.calcTangents();
		mesh->init(&model);
	}

	void BasicMesh::cube2Mesh(graphics::Mesh * mesh)
	{
		
		IndexedModel model;
		model.positions = { 
			maths::vec3(1, -1, -1),
			maths::vec3(-1, -1, -1),
			maths::vec3(1, -1, 1),
			maths::vec3(-1, -1, 1),
			maths::vec3(-1, 1, -1),
			maths::vec3(1, 1, -1),
			maths::vec3(-1, 1, 1),
			maths::vec3(1, 1, 1),
			maths::vec3(-1, -1, -1),
			maths::vec3(1, -1, -1),
			maths::vec3(-1, 1, -1),
			maths::vec3(1, 1, -1),
			maths::vec3(1, -1, 1),
			maths::vec3(-1, -1, 1),
			maths::vec3(1, 1, 1),
			maths::vec3(-1, 1, 1),
			maths::vec3(-1, -1, 1),
			maths::vec3(-1, -1, -1),
			maths::vec3(-1, 1, 1),
			maths::vec3(-1, 1, -1),
			maths::vec3(1, -1, -1),
			maths::vec3(1, -1, 1),
			maths::vec3(1, 1, -1),
			maths::vec3(1, 1, 1),
			maths::vec3(1, -1, -1),
			maths::vec3(-1, -1, -1),
			maths::vec3(1, -1, 1),
			maths::vec3(-1, -1, 1),
			maths::vec3(-1, 1, -1),
			maths::vec3(1, 1, -1),
			maths::vec3(-1, 1, 1),
			maths::vec3(1, 1, 1),
			maths::vec3(-1, -1, -1),
			maths::vec3(1, -1, -1),
			maths::vec3(-1, 1, -1),
			maths::vec3(1, 1, -1),
			maths::vec3(1, -1, 1),
			maths::vec3(-1, -1, 1),
			maths::vec3(1, 1, 1),
			maths::vec3(-1, 1, 1),
			maths::vec3(-1, -1, 1),
			maths::vec3(-1, -1, -1),
			maths::vec3(-1, 1, 1),
			maths::vec3(-1, 1, -1),
			maths::vec3(1, -1, -1),
			maths::vec3(1, -1, 1),
			maths::vec3(1, 1, -1),
			maths::vec3(1, 1, 1) };

		model.texCoords = {
			maths::vec2(1, 0),
			maths::vec2(0, 0),
			maths::vec2(1, 1),
			maths::vec2(0, 1),
			maths::vec2(0, 1),
			maths::vec2(1, 1),
			maths::vec2(0, 0),
			maths::vec2(1, 0),
			maths::vec2(0, 1),
			maths::vec2(1, 1),
			maths::vec2(0, 0),
			maths::vec2(1, 0),
			maths::vec2(1, 0),
			maths::vec2(0, 0),
			maths::vec2(1, 1),
			maths::vec2(0, 1),
			maths::vec2(0, 1),
			maths::vec2(1, 1),
			maths::vec2(0, 0),
			maths::vec2(1, 0),
			maths::vec2(0, 1),
			maths::vec2(1, 1),
			maths::vec2(0, 0),
			maths::vec2(1, 0),
			maths::vec2(1, 1),
			maths::vec2(0, 1),
			maths::vec2(1, 0),
			maths::vec2(0, 0),
			maths::vec2(0, 0),
			maths::vec2(1, 0),
			maths::vec2(0, 1),
			maths::vec2(1, 1),
			maths::vec2(0, 0),
			maths::vec2(1, 0),
			maths::vec2(0, 1),
			maths::vec2(1, 1),
			maths::vec2(1, 1),
			maths::vec2(0, 1),
			maths::vec2(1, 0),
			maths::vec2(0, 0),
			maths::vec2(1, 1),
			maths::vec2(0, 1),
			maths::vec2(1, 0),
			maths::vec2(0, 0),
			maths::vec2(1, 1),
			maths::vec2(0, 1),
			maths::vec2(1, 0),
			maths::vec2(0, 0)};

		model.indices = {
			0,2,1,1,2,3,
			4,6,5,5,6,7,
			8,10,9,9,10,11,
			12,14,13,13,14,15,
			16,18,17,17,18,19,
			20,22,21,21,22,23,

			24,25,26,25,27,26,
			28,29,30,29,31,30,
			32,33,34,33,35,34,
			36,37,38,37,39,38,
			40,41,42,41,43,42,
			44,45,46,45,47,46 };
		model.calcNormals();
		model.calcTangents();
		mesh->init(&model);
	}

	void BasicMesh::cubeApproxMesh(graphics::Mesh * mesh)
	{
		IndexedModel model;
		model.positions = {
			maths::vec3(1, -1, -1),
			maths::vec3(-1, -1, -1),
			maths::vec3(1, -1, 1),
			maths::vec3(-1, -1, 1),
			maths::vec3(1, 1, -1),
			maths::vec3(-1, 1, -1),
			maths::vec3(1, 1, 1),
			maths::vec3(-1, 1, 1)};

		model.texCoords = { 
			maths::vec2(1, 0),
			maths::vec2(0, 0),
			maths::vec2(1, 1),
			maths::vec2(0, 1),
			maths::vec2(1, 0),
			maths::vec2(0, 0),
			maths::vec2(1, 1),
			maths::vec2(0, 1)};
		model.indices = { 
			0,2,1,1,2,3,
			0,1,4,4,1,5,
			0,4,2,2,4,6,
			2,6,3,3,6,7,
			1,3,7,1,7,5,
			4,5,6,5,7,6 };
		model.calcNormals();
		model.calcTangents();
		mesh->init(&model);
	}


} }