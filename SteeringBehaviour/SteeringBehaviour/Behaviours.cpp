#include "Behaviours.h"
#include "SceneHandler.h"
#include "Unit.h"
#include <random>
#include <memory>

Behaviours::Behaviours(SceneHandler* scene)
	: m_scene(scene)
{
	srand(time(NULL));
}

Transform Behaviours::calculateTransform(GameState::Enum state, Target target, Unit& unit)
{
	if (state == GameState::SEEK)
		return seek(target, unit);
	if (state == GameState::FLEE)
		return flee(target, unit);
	if (state == GameState::ARRIVE)
		return arrive(target, unit);
	if (state == GameState::WANDER)
		return wander(unit);
	if (state == GameState::PURSUIT)
		return pursuit(target, unit);
	if (state == GameState::EVADE)
		return evade(target, unit);
	if (state == GameState::PATHFOLLOW)
		return pathFollow(unit, m_scene->getPathFollow());
	if (state == GameState::COLLISIONFOV)
		return collisionFov(target, unit);
	if (state == GameState::COLLISIONPREDICTION)
		return collisionPrediction(target, unit);
	if (state == GameState::OBSTACLEAVOIDANCE)
		return obstacleAvoidance(target, unit);
	if (state == GameState::SCENARIO)
		return scenario(target, unit);
	if (state == GameState::TEAM)
		return team(target, unit);
	if (state == GameState::ENEMIE1)
		return pathFollow(unit, m_scene->getEnemiePath(1));
	if (state == GameState::ENEMIE2)
		return pathFollow(unit, m_scene->getEnemiePath(2));
	if (state == GameState::ENEMIE3)
		return pathFollow(unit, m_scene->getEnemiePath(3));
	if (state == GameState::ENEMIE4)
		return pathFollow(unit, m_scene->getEnemiePath(4));
	if (state == GameState::ENEMIE5)
		return pathFollow(unit, m_scene->getEnemiePath(5));
	if (state == GameState::ENEMIE6)
		return pathFollow(unit, m_scene->getEnemiePath(6));
	if (state == GameState::ENEMIE7)
		return pathFollow(unit, m_scene->getEnemiePath(7));
	if (state == GameState::ENEMIE8)
		return pathFollow(unit, m_scene->getEnemiePath(8));

}

Transform Behaviours::align(Vec2 target, Unit& unit) const
{
	Transform transform;
	transform.angAcceleration = 0;
	transform.acceleration = Vec2();

	auto rotation = target.getAngle() - unit.getOrientation().asFloat();
	rotation = mapToRange(rotation);

	auto rotationSize = fabsf(rotation);
	if (rotationSize < m_AlignSatisfactionAngel)
	{		
		unit.setRotationVelocity(0.0f);
		return transform;
	}

	auto targetRotation = 0.0f;
	if (rotationSize > m_AlignProximityAngel)
	{
		targetRotation = unit.getMaxRotationVelocity();
	}
	else
	{
		targetRotation = unit.getMaxRotationVelocity() * rotationSize / m_AlignProximityAngel;
	}

	targetRotation *= rotation / rotationSize;
	
	
	auto angAcceleration = targetRotation - unit.getRotationVelocity();
	angAcceleration /= m_TimeToTarget;

	auto acceleration = fabsf(angAcceleration);
	if (acceleration > unit.getMaxRotationAcceleration())
	{
		angAcceleration /= acceleration;
		angAcceleration *= unit.getMaxRotationAcceleration();
	}

	transform.angAcceleration = angAcceleration;
	return transform;
}

Transform Behaviours::seek(Target target, Unit& unit) const
{
	unit.setTarget(target);
	auto transform = align(unit.getVelocity(), unit);

	auto velocity = target.position - unit.getPosition();
	auto acceleration = velocity.normalize() * unit.getMaxAcceleration();
		
	transform.acceleration = acceleration;
	return transform;
}

Transform Behaviours::flee(Target target, Unit& unit) const
{
	unit.setTarget(target);
	auto transform = seek(target, unit);
	transform.acceleration = transform.acceleration * -1;
	return transform;
}

Transform Behaviours::arrive(Target target, Unit& unit) const
{
	auto transform = align(unit.getVelocity(), unit);
	
	auto distance = target.position - unit.getPosition();
	if (distance.lengthSqrt() < m_ArriveRadius * m_ArriveRadius)
	{
		transform.acceleration = Vec2();
		unit.setVelocity(Vec2());
		return transform;
	}
	
	auto unitSpeed = 0.f;
	if (distance.lengthSqrt() > m_ArriveFullSpeedRadius * m_ArriveFullSpeedRadius)
	{
		unitSpeed = unit.getMaxVelocity();
	}
	else
	{
		unitSpeed = (distance.length() / m_ArriveFullSpeedRadius) * unit.getMaxVelocity();
	}

	auto velocity = distance.normalize() * unitSpeed;
	auto acceleration = (velocity - unit.getVelocity()) / m_TimeToTarget;

	if (acceleration.lengthSqrt() > unit.getMaxAcceleration() * unit.getMaxAcceleration())
	{
		acceleration = acceleration.normalize() * unit.getMaxAcceleration();
	}

	transform.acceleration = acceleration;
	return transform;
}

Transform Behaviours::wander(Unit& unit)
{	
	Target target;
	m_wander.orientation += randomBinomial() * m_wander.rate;
	target.orientation = m_wander.orientation + unit.getOrientation().asFloat();
	target.position = unit.getPosition() + unit.getOrientation().asVec2() * m_wander.offset;
	target.position += target.orientation.asVec2() * m_wander.radius;

	auto direction = target.position - unit.getPosition();
	unit.setWander(m_wander);

	Transform transform;
	auto foo = look(direction, unit);
	transform.angAcceleration = foo;
	transform.acceleration = unit.getOrientation().asVec2() * unit.getMaxAcceleration();
	
	return transform;
}

Transform Behaviours::pursuit(Target target, Unit& unit) const
{
	auto distance = (target.position - unit.getPosition()).length();
	auto speed = unit.getVelocity().length();
	
	auto prediction = 0.0f;

	if (speed <= (distance / m_PersuitPredictionTime))
	{
		prediction = m_PersuitPredictionTime;
	}
	else
	{
		prediction = distance / speed;
	}

	target.position += target.velocity * prediction;
	return seek(target, unit);
}

Transform Behaviours::evade(Target target, Unit& unit) const
{
	auto transform = pursuit(target, unit);
	transform.acceleration = transform.acceleration * -1;
	return transform;
}

Transform Behaviours::pathFollow(Unit& unit, std::vector<Vec2> path) const
{	
	auto distance = std::numeric_limits<float>::max();
	auto index = 0, i = 0;	
	
	for (auto vec : path)
	{
		auto temp = vec - unit.getPosition();
		if (fabs(temp.length()) < distance)
		{
			index = i;
			distance = fabs(temp.length());
		}
		i++;
	}
	index += unit.getPathOffset();
	index = index % path.size();
	unit.setLastPathIndex(index);

	Transform transform;
	Target target;
	if (unit.getLastPathIndex() == path.size() - 1)
	{
		target.position = path.at(index);
		target.orientation = 0;
		transform = arrive(target, unit);
	}
	else
	{
		target.position = path.at(index);
		target.orientation = 0;
		transform = seek(target, unit);
	}
	return transform;
}

Transform Behaviours::collisionFov(Target target, Unit& unit)
{
	Transform transform;
	transform.acceleration = Vec2();
	transform.angAcceleration = 0;

	auto units = m_scene->getUnits();

	for (auto& tempUnit : units)
	{
		auto deltaPosition = tempUnit->getPosition() - unit.getPosition();
		auto dot = deltaPosition.dot(unit.getOrientation().asVec2());
		if (fabsf(dot) > unit.getFov() && deltaPosition.lengthSqrt() < m_viewDistance * m_viewDistance)
		{
			transform = evade(tempUnit->createTarget(), unit);
			return transform;
		}
	}
	return seek(target, unit);
}

Transform Behaviours::collisionPrediction(Target target, Unit& unit)
{
	Transform transform;
	transform.acceleration = Vec2();
	transform.angAcceleration = 0;
	
	Vec2 deltaPosition;
	Vec2 deltaVelocity;
	std::shared_ptr<Unit> colUnit;
	auto closestTime = std::numeric_limits<float>::max();
	auto minDistance = 0.0f;
	auto units = m_scene->getUnits();

	for (auto& tempUnit : units)
	{
		auto deltaP = tempUnit->getPosition() - unit.getPosition();
		auto deltaV = tempUnit->getVelocity() - unit.getVelocity();

		if (deltaV.lengthSqrt() <= m_Epsilon)
		{
			continue;
		}

		auto t = deltaP.dot(deltaV) / deltaV.length();
		auto distance = deltaP.length() - deltaV.length() * t;

		if (distance < 2 * m_SeperationRadius && t < closestTime)
		{
			closestTime = t;
			colUnit = tempUnit;
			deltaPosition = deltaP;
			deltaVelocity = deltaV;
			minDistance = distance;
		}
	}

	
	if (closestTime == std::numeric_limits<float>::max())
		return seek(target, unit);

	if (minDistance >= 0 || deltaPosition.length() < 2 * m_SeperationRadius)
	{
		transform = evade(colUnit->createTarget(), unit);
	}
	else
	{
		return seek(target, unit);
	}
	return transform;
}

Transform Behaviours::velocityMatching(Target target, Unit& unit)
{
	Transform transform;
	
	transform = align(unit.getVelocity(), unit);

	if (target.velocity == unit.getVelocity())
		return transform;
		
	transform.acceleration = target.velocity;
	if (transform.acceleration.lengthSqrt() > unit.getMaxAcceleration() * unit.getMaxAcceleration())
	{
		transform.acceleration = transform.acceleration.normalize() * unit.getMaxAcceleration();
	}
	return transform;
}


Transform Behaviours::obstacleAvoidance(Target target, Unit& unit)
{
	Transform transform;
	transform.acceleration = Vec2();
	transform.angAcceleration = 0;

	auto obstacles = m_scene->getObstacle();

	auto centralRay = unit.getVelocity();
	if (centralRay.length() < m_Epsilon && centralRay.length() > -m_Epsilon)
	{
		return wander(unit);
	}

	centralRay = centralRay.normalize();

	auto whiskeyLeft = unit.getVelocity();
	whiskeyLeft = whiskeyLeft.normalize();
	whiskeyLeft = whiskeyLeft.rotate(25.0f);

	auto whiskeyRight = unit.getVelocity();
	whiskeyRight = whiskeyRight.normalize();
	whiskeyRight = whiskeyRight.rotate(-25.0f);
	auto i = 0;

	for (auto& obstacle : obstacles)
	{
		auto pos = obstacle.getPosition();
		auto sice = obstacle.getSize();
		auto point1 = Vec2(pos.x, pos.y);
		auto point2 = Vec2(pos.x + sice.x, pos.y + sice.y);
		Vec2 normal;

		auto collision = rayBoxIntersection(point1, point2, unit.getPosition(), centralRay);
		if (collision.x < std::numeric_limits<float>::max() && collision.y < std::numeric_limits<float>::max() && (collision - unit.getPosition()).length() < 100.0f)
		{
			unit.m_collided = i;
			normal = getCollisionNormals(collision, point1, point2);
			auto targetVec = collision + normal * 100.0f;
			Target newtarget;
			newtarget.position = targetVec;
			newtarget.orientation = 0;
			return seek(newtarget, unit);
		}

		collision = rayBoxIntersection(point1, point2, unit.getPosition(), whiskeyLeft);
		if (collision.x < std::numeric_limits<float>::max() && collision.y < std::numeric_limits<float>::max() && (collision - unit.getPosition()).length() < 40.0f)
		{
			auto targetVec = unit.getPosition() + whiskeyRight * 30.0f;
			Target newtarget;
			newtarget.position = targetVec;
			newtarget.orientation = 0;
			return seek(newtarget, unit);
		}

		collision = rayBoxIntersection(point1, point2, unit.getPosition(), whiskeyRight);
		if (collision.x < std::numeric_limits<float>::max() && collision.y < std::numeric_limits<float>::max() && (collision - unit.getPosition()).length() < 40.0f)
		{
			auto targetVec = unit.getPosition() + whiskeyLeft * 30.0f;
			Target newtarget;
			newtarget.position = targetVec;
			newtarget.orientation = 0;
			return seek(target, unit);
		}

		i++;
	}

	return seek(target, unit);
}

Transform Behaviours::seperation(Unit& unit)
{
	Transform transform;
	auto units = m_scene->getTeam();
	for (auto& tempUnit : units)
	{
		auto deltaPos = tempUnit->getPosition() - unit.getPosition();
		if (deltaPos.length() > m_Epsilon && deltaPos.length() < m_SeperationRadius)
		{
			auto strength = fminf(3 * (1 / deltaPos.length()), unit.getMaxAcceleration());
			transform.acceleration = deltaPos.normalize() * strength;
		}
	}
	return transform;
}


Transform Behaviours::scenario(Target target, Unit& unit)
{
	Transform transform;

	return pathFollow(unit, m_scene->getPathFollow());
}

Transform Behaviours::team(Target target, Unit& unit)
{
	auto transSep = seperation(unit);
	auto transVel = velocityMatching(target, unit);
	auto transObs = obstacleAvoidance(target, unit);
	auto transCol = collisionFov(target, unit);

	Transform transform;
	transform.acceleration += transSep.acceleration * 0.5;
	transform.angAcceleration += transSep.angAcceleration * 0.5;

	transform.acceleration += transVel.acceleration * 0.6;
	transform.angAcceleration += transVel.angAcceleration * 0.6;

	transform.acceleration += transObs.acceleration * 0.8;
	transform.angAcceleration += transObs.angAcceleration * 0.8;

	transform.acceleration += transCol.acceleration * 0.4;
	transform.angAcceleration += transCol.angAcceleration * 0.4;

	if (transform.acceleration.length() > unit.getMaxAcceleration())
		transform.acceleration = transform.acceleration.normalize() * unit.getMaxAcceleration();

	if (transform.angAcceleration > unit.getMaxRotationAcceleration())
		transform.angAcceleration = unit.getMaxRotationAcceleration();

	return transform;
}

float Behaviours::look(Vec2 target, Unit& unit) const
{
	if (unit.getVelocity().length() == 0)
		return 0.f;

	return target.getAngle() + m_Pi / 2;
}

float Behaviours::randomBinomial() const
{
	//return rand() - rand();
	return static_cast <float> (rand()) / static_cast <float> (RAND_MAX) * static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
}

float Behaviours::mapToRange(float rotation) const
{
	return rotation - 2 * m_Pi * floorf((rotation + m_Pi) / (2 * m_Pi));
}

Vec2 Behaviours::rayBoxIntersection(Vec2 point1, Vec2 point2, Vec2 start, Vec2 ray)
{
	Vec2 intersetion(std::numeric_limits<float>::max(), std::numeric_limits<float>::max());
	auto tmin = std::numeric_limits<float>::min();
	auto tmax = std::numeric_limits<float>::max();

	if (ray.x != 0.0f)
	{
		auto tx1 = (point1.x - start.x) / ray.x;
		auto tx2 = (point2.x - start.x) / ray.x;

		tmin = fmaxf(tmin, fminf(tx1, tx2));
		tmax = fminf(tmax, fmaxf(tx1, tx2));
	}

	if (ray.y != 0.0f)
	{
		auto ty1 = (point1.y - start.y) / ray.y;
		auto ty2 = (point2.y - start.y) / ray.y;

		tmin = fmaxf(tmin, fminf(ty1, ty2));
		tmax = fminf(tmax, fmaxf(ty1, ty2));
	}

	if (tmax >= tmin)
		intersetion = start + ray * tmin;

	return intersetion;
}

Vec2 Behaviours::getCollisionNormals(Vec2 collision, Vec2 point1, Vec2 point2)
{
	Vec2 normal;
	if (point1.y <= collision.y)
	{
		normal = Vec2(0, -1);
	}
	else if (point2.y <= collision.y)
	{
		normal = Vec2(0, 1);
	}
	else if (point1.x <= collision.x)
	{
		normal = Vec2(-1, 0);
	}
	else if (point2.x <= collision.x)
	{
		normal = Vec2(1, 0);
	}
	return normal;
}
