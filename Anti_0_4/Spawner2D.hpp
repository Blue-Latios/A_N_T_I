#ifndef SPAWNER2D_HPP
#define SPAWNER2D_HPP

///class pembantu khusus game

#include "Object2D.hpp"

class Spawner2D {
	private:
		Time spawntimer;
		float spawntime;
		float spawnhealth;
		Object2D* spawner;
		int spawntype;
		Time damagetime;
	public:
		Spawner2D(Object2D* sp, float sptime, float health, int type);
		virtual ~Spawner2D();
		float getSpawnTime() const;
		Object2D* getObject();
		float getHealth() const;
		void setSpawnTime(float t);
		Time& getSpawnTimer();
		void damage(float d);
		bool isDamaged();
		void spawnObject();
		void setSpawnType(int type);
};

#endif
