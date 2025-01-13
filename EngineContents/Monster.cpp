#include "PreCompile.h"
#include "Monster.h"

AMonster::AMonster()
{
}

AMonster::~AMonster()
{
}

std::shared_ptr<class USpriteRenderer> AMonster::GetRenderer()
{
	return Renderer;
}

void AMonster::ChangeState(EStateType _MonsterState)
{
	MonsterState = _MonsterState;
}

void AMonster::BeginPlay()
{
	AActor::BeginPlay();
}

void AMonster::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}
