#pragma once
#include "Monster.h"

// Ό³Έν :
class AFallen_Spear : public AMonster
{
public:
	// constrcuter destructer
	AFallen_Spear();
	~AFallen_Spear();

	// delete Function
	AFallen_Spear(const AFallen_Spear& _Other) = delete;
	AFallen_Spear(AFallen_Spear&& _Other) noexcept = delete;
	AFallen_Spear& operator=(const AFallen_Spear& _Other) = delete;
	AFallen_Spear& operator=(AFallen_Spear&& _Other) noexcept = delete;


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	std::shared_ptr<class USpriteRenderer> Fallen_SpearRenderer;
	std::shared_ptr<class USpriteRenderer> Child;

	std::shared_ptr<class UCollision> Collision;
};

