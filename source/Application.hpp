#ifndef APPLICATION_HPP
#define APPLICATION_HPP
namespasce Sincronia{
	class World;
	class Application {
	public:
		virtual void UserStartUp(World& world);

		virtual void UserShutDown(World& world);

		virtual void UserUpdate(World& world, float dt);

	private:
		void StartUp(World& world);
	};
}
#endif