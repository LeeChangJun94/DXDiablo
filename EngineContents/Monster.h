#pragma once
#include <EngineCore/Actor.h>
#include <EngineBase/FSMStateManager.h>

enum EMonsterType
{
	FALLEN_SWORD,
	FALLEN_SPEAR,
	HIDDEN,
	SCAVENGER,
	SKELETON_AXE,
	SKELETON_BOW,
	SKELETON_SWORD,
	ZOMBIE,
	BUTCHER,
	SKELETON_KING,
};

enum class EStateType
{
	NONE,
	IDLE,
	ATTACK,
	HIT,
	WALK,
	SPECIAL,
	DIE,
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

	virtual std::shared_ptr<class USpriteRenderer> GetRenderer();
	virtual void ChangeState(EStateType _MonsterState);

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	std::shared_ptr<class USpriteRenderer> Renderer;
	EStateType MonsterState;

	UFSMStateManager FSM;

private:
	std::shared_ptr<class USpriteRenderer> Child;
};

