#include "PreCompile.h"
#include "Skeleton.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/EngineCore.h>
#include <EngineCore/CameraActor.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineDebug.h>
#include <EngineCore/Collision.h>

ASkeleton::ASkeleton()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	SkeletonRenderer = CreateDefaultSubObject<USpriteRenderer>();

	//ZombieRenderer->SetAutoScale(true);
	//ZombieRenderer->SetAutoScaleRatio(1.0f);

	SkeletonRenderer->CreateAnimation("Attack_2", "Zombie_Attack.png", 0, 11, 0.1f, false);



	SkeletonRenderer->SetRelativeScale3D({ 50, 50, 1.0f });
	SkeletonRenderer->SetupAttachment(RootComponent);

	SkeletonRenderer->ChangeAnimation("Idle_2");

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Monster");
	Collision->SetScale3D({ 50.0f, 50.0f });
}

ASkeleton::~ASkeleton()
{
}

void ASkeleton::BeginPlay()
{
	AActor::BeginPlay();
}

void ASkeleton::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

