#pragma once
#include "Monster.h"

// ���� :
class AZombie : public AMonster
{
public:
	// constrcuter destructer
	AZombie();
	~AZombie();

	// delete Function
	AZombie(const AZombie& _Other) = delete;
	AZombie(AZombie&& _Other) noexcept = delete;
	AZombie& operator=(const AZombie& _Other) = delete;
	AZombie& operator=(AZombie&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void Serialize(UEngineSerializer& _Ser) override;
	void DeSerialize(UEngineSerializer& _Ser) override;
private:
	std::shared_ptr<class USpriteRenderer> ZombieRenderer;
	std::shared_ptr<class USpriteRenderer> Child;

	std::shared_ptr<class UCollision> Collision;

};

