#ifndef WORLD_HPP
#define WORLD_HPP
namespace Sincronia {
	class World {
	private:
		World(Application& app);
		void StartMainLoop();
		void Update(float dt);

};
}

#endif