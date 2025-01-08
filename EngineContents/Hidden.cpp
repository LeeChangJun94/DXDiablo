#include "PreCompile.h"
#include "Hidden.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/EngineCore.h>
#include <EngineCore/CameraActor.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineDebug.h>
#include <EngineCore/Collision.h>

AHidden::AHidden()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	HiddenRenderer = CreateDefaultSubObject<USpriteRenderer>();

	//ZombieRenderer->SetAutoScale(true);
	//ZombieRenderer->SetAutoScaleRatio(1.0f);

	HiddenRenderer->CreateAnimation("Attack_2", "Zombie_Attack.png", 0, 11, 0.1f, false);



	HiddenRenderer->SetRelativeScale3D({ 50, 50, 1.0f });
	HiddenRenderer->SetupAttachment(RootComponent);

	HiddenRenderer->ChangeAnimation("Idle_2");

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Monster");
	Collision->SetScale3D({ 50.0f, 50.0f });
}

AHidden::~AHidden()
{
}

void AHidden::BeginPlay()
{
	AActor::BeginPlay();
}

void AHidden::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}