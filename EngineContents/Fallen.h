#pragma once
#include "Monster.h"

// Ό³Έν :
class AFallen : public AMonster
{
public:
	// constrcuter destructer
	AFallen();
	~AFallen();

	// delete Function
	AFallen(const AFallen& _Other) = delete;
	AFallen(AFallen&& _Other) noexcept = delete;
	AFallen& operator=(const AFallen& _Other) = delete;
	AFallen& operator=(AFallen&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
private:
	std::shared_ptr<class USpriteRenderer> FallenRenderer;
	std::shared_ptr<class USpriteRenderer> Child;

	std::shared_ptr<class UCollision> Collision;
};

