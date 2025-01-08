#include "PreCompile.h"
#include "Scavenger.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/EngineCore.h>
#include <EngineCore/CameraActor.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineDebug.h>
#include <EngineCore/Collision.h>

AScavenger::AScavenger()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	ScavengerRenderer = CreateDefaultSubObject<USpriteRenderer>();

	//ZombieRenderer->SetAutoScale(true);
	//ZombieRenderer->SetAutoScaleRatio(1.0f);

	ScavengerRenderer->CreateAnimation("Attack_2", "Zombie_Attack.png", 0, 11, 0.1f, false);



	ScavengerRenderer->SetRelativeScale3D({ 50, 50, 1.0f });
	ScavengerRenderer->SetupAttachment(RootComponent);

	ScavengerRenderer->ChangeAnimation("Idle_2");

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Monster");
	Collision->SetScale3D({ 50.0f, 50.0f });
}

AScavenger::~AScavenger()
{
}

void AScavenger::BeginPlay()
{
	AActor::BeginPlay();
}

void AScavenger::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

