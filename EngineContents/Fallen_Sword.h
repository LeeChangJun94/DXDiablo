#pragma once
#include "Monster.h"

// Ό³Έν :
class AFallen_Sword : public AMonster
{
public:
	// constrcuter destructer
	AFallen_Sword();
	~AFallen_Sword();

	// delete Function
	AFallen_Sword(const AFallen_Sword& _Other) = delete;
	AFallen_Sword(AFallen_Sword&& _Other) noexcept = delete;
	AFallen_Sword& operator=(const AFallen_Sword& _Other) = delete;
	AFallen_Sword& operator=(AFallen_Sword&& _Other) noexcept = delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	std::shared_ptr<class USpriteRenderer> Child;

	std::shared_ptr<class UCollision> Collision;
};

