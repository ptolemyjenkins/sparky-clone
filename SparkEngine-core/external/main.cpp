#include "..\src\core.h"
#include "DebugScene.h"
#include "../src/physics/physics.h"
const int WIDTH = (int) (1900);
const int HEIGHT = (int)(1050);
using namespace sparky;
using namespace maths;
int main()
{
	/*sparky::DebugScene scene;
	sparky::CoreEngine engine("SparkEngine v0.1",&scene, WIDTH, HEIGHT, 60 );
	engine.start(&sparky::graphics::RenderingEngine());
	return 0;*/
	
	fileLoader a = fileLoader("./res/models/COMTest.obj");
	vec4 *vertices = new vec4[a.verts.size()];
	for (int i = 0; i < a.verts.size(); i++)
	{
		vertices[i] = a.verts[i];
		//std::cout << vertices[i] << std::endl;
	}
	vec4 *norms = new vec4[a.norms.size()];
	for (int i = 0; i < a.norms.size(); i++)
	{
		norms[i] = a.norms[i];
		//std::cout << norms[i] << std::endl;
	}

	int* indices = new int[a.indices.size()];
	int* nindices = new int[a.nindices.size()];
	for (int i = 0; i < a.indices.size(); i += 3)
	{
		indices[i] = a.indices[i];
		indices[i+1] = a.indices[i+1];
		indices[i+2] = a.indices[i+2];

		nindices[i] = a.nindices[i];
		nindices[i + 1] = a.nindices[i + 1];
		nindices[i + 2] = a.nindices[i + 2];

		//std::cout << nindices[i] << nindices[i + 1] << nindices[i + 2] << std::endl;
	}
	physics::A_solid mushroom = physics::A_solid(vertices, a.verts.size(), indices, a.indices.size(),
		norms, a.norms.size(), nindices, a.nindices.size());
	
	for (int i = 0; i < mushroom.intsize / 3; i++)
	{
		//std::cout << mushroom.jigsaw[i].t1 << mushroom.jigsaw[i].t2 << mushroom.jigsaw[i].t3 << mushroom.jigsaw[i].t4 << std::endl;
		//std::cout << mushroom.jigsaw[i].volume() << std::endl;
	}
	std::cout << "centre of Mass: " << mushroom.com << "\n volume: " << mushroom.Volume << "\n centroid: " << mushroom.centroid << std::endl;
	system("PAUSE");
}