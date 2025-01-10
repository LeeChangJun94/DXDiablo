#pragma once
#include <EngineCore/Actor.h>

enum EMonsterType
{
	Fallen_Sword,
	Fallen_Spear,
	Hidden,
	Scavenger,
	Skeleton_Axe,
	Skeleton_Bow,
	Skeleton_Sword,
	Zombie,
	Butcher,
	Skeleton_King,
};


// Ό³Έν :
class AMonster : public AActor
{
public:
	// constrcuter destructer
	AMonster();
	~AMonster();

	// delete Function
	AMonster(const AMonster& _Other) = delete;
	AMonster(AMonster&& _Other) noexcept = delete;
	AMonster& operator=(const AMonster& _Other) = delete;
	AMonster& operator=(AMonster&& _Other) noexcept = delete;

	EMonsterType MonsterTypeValue;

	std::shared_ptr<class USpriteRenderer> GetRenderer()
	{
		return Renderer;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	std::shared_ptr<class USpriteRenderer> Renderer;
	std::shared_ptr<class USpriteRenderer> Child;


};

