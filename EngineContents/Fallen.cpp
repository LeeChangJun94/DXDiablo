#include "PreCompile.h"
#include "Fallen.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/EngineCore.h>
#include <EngineCore/CameraActor.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineDebug.h>
#include <EngineCore/Collision.h>

AFallen::AFallen()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	FallenRenderer = CreateDefaultSubObject<USpriteRenderer>();

	//ZombieRenderer->SetAutoScale(true);
	//ZombieRenderer->SetAutoScaleRatio(1.0f);

	FallenRenderer->CreateAnimation("Attack_2", "Zombie_Attack.png", 0, 11, 0.1f, false);



	FallenRenderer->SetRelativeScale3D({ 50, 50, 1.0f });
	FallenRenderer->SetupAttachment(RootComponent);

	FallenRenderer->ChangeAnimation("Idle_2");

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Monster");
	Collision->SetScale3D({ 50.0f, 50.0f });
}

AFallen::~AFallen()
{
}

void AFallen::BeginPlay()
{
	AActor::BeginPlay();
}

void AFallen::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}