#ifndef SPAWNER2D_HPP
#define SPAWNER2D_HPP

///class pembantu khusus game

#include "Object2D.hpp"
#define TYPE_SQUARE 1
#define TYPE_QUAD 2
#define TYPE_TRIANGLE 3

class Spawner2D {
	private:
		Time spawntimer;
		float spawntime;
		float spawnhealth;
		float maxhealth;
		Object2D* spawner;
		int objtype;
		int spawntype;
		Time damagetime;
	public:
		Spawner2D(Object2D* sp, int otype, float sptime, float health, int type);
		virtual ~Spawner2D();
		float getSpawnTime() const;
		Object2D* getObject();
		float getHealth() const;
		float getMaxHealth() const;
		int getObjType() const;
		void setSpawnTime(float t);
		Time& getSpawnTimer();
		void damage(float d);
		bool isDamaged();
		void spawnObject();
		void setSpawnType(int type);
		int getSpawnType() const;
};

#endif
