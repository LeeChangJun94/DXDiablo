#pragma once
#include "Monster.h"

// Ό³Έν :
class ASkeleton_Axe : public AMonster
{
public:
	// constrcuter destructer
	ASkeleton_Axe();
	~ASkeleton_Axe();

	// delete Function
	ASkeleton_Axe(const ASkeleton_Axe& _Other) = delete;
	ASkeleton_Axe(ASkeleton_Axe&& _Other) noexcept = delete;
	ASkeleton_Axe& operator=(const ASkeleton_Axe& _Other) = delete;
	ASkeleton_Axe& operator=(ASkeleton_Axe&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

private:
	std::shared_ptr<class USpriteRenderer> Skeleton_AxeRenderer;
	std::shared_ptr<class USpriteRenderer> Child;

	std::shared_ptr<class UCollision> Collision;
};

