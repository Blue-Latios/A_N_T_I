#include "Spawner2D.hpp"
#include "SquareObj.hpp"

Spawner2D::Spawner2D(Object2D* sp, float sptime, float health, int type) {
	spawner = sp;
	spawntime = sptime;
	spawnhealth = health;
	spawntype = type;
}
Spawner2D::~Spawner2D() {
}
float Spawner2D::getSpawnTime() const {
	return spawntime;
}
Object2D* Spawner2D::getObject() {
	return spawner;
}
float Spawner2D::getHealth() const {
	return spawnhealth;
}
void Spawner2D::setSpawnTime(float t) {
	spawntime = t;
}
Time& Spawner2D::getSpawnTimer() {
	return spawntimer;
}
void Spawner2D::damage(float d) {
	spawnhealth -= d;
	damagetime.resetTime();
}
bool Spawner2D::isDamaged() {
	return (damagetime.getElapsed() <= 0.1);
}
void Spawner2D::setSpawnType(int type) {
	spawntype = type;
}

