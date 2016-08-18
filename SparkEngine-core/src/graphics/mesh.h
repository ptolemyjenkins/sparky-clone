#pragma once
#include "../ResourceManagment/MeshResource.h"
#include "../ResourceManagment/SpriteResource.h"
#include "../util/meshLoading/meshLoading.h"
#include "transform.h"
namespace sparky { namespace graphics {

#define RENDERER_MAX_SPRITES	60000
#define RENDERER_VERTEX_SIZE	sizeof(SpriteVertexData)
#define RENDERER_SPRITE_SIZE	RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE	RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE	RENDERER_MAX_SPRITES * 6

#define SHADER_POSITION_INDEX	0
#define SHADER_COLOUR_INDEX		1
#define SHADER_TEXCOORD_INDEX	2
#define SHADER_TID_INDEX		3

	struct SpriteVertexData
	{
		maths::vec4 vertex;
		maths::vec4 color;
		maths::vec2 tex;
		int textureNumber;
	};


	class Mesh {
	private:
		static std::unordered_map<std::string, resource::MeshResource> loadedModels;
		resource::MeshResource * resource;
		resource::SpriteResource* spriteResource;
		std::string fileName;
		SpriteVertexData* m_Buffer;
	public:
		Mesh();
		Mesh(const std::string& fileName);
		~Mesh();
	private:
		void uploadModel(util::IndexedModel* model);
		void loadMesh(std::string filename);
	public:
		void initSpriteSheet();
		void initModel(util::IndexedModel* model);

		void beginSprite();
		void submitSprite(Transform* transform, maths::vec4& colour, maths::vec2& bleft, maths::vec2& tright, int texID);
		void endSprite();

		void draw();
		void drawSprites();
	};
} }