#include "PreCompile.h"
#include "Zombie.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/EngineCore.h>
#include <EngineCore/CameraActor.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineDebug.h>
#include <EngineCore/Collision.h>

AZombie::AZombie()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	ZombieRenderer = CreateDefaultSubObject<USpriteRenderer>();

	//ZombieRenderer->SetAutoScale(true);
	//ZombieRenderer->SetAutoScaleRatio(1.0f);

	ZombieRenderer->CreateAnimation("Attack_2", "Zombie_Attack.png", 0, 11, 0.1f);

	ZombieRenderer->SetRelativeScale3D({ 50, 50, 1.0f });
	ZombieRenderer->SetupAttachment(RootComponent);

	ZombieRenderer->ChangeAnimation("Attack_2");

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Monster");
	Collision->SetScale3D({ 50.0f, 50.0f });
}

AZombie::~AZombie()
{
}

void AZombie::BeginPlay()
{
	AActor::BeginPlay();
}

void AZombie::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

