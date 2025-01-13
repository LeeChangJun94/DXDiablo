#include "PreCompile.h"
#include "Skeleton_Axe.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/EngineCore.h>
#include <EngineCore/CameraActor.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineDebug.h>
#include <EngineCore/Collision.h>

ASkeleton_Axe::ASkeleton_Axe()
{
	MonsterTypeValue = EMonsterType::Skeleton_Axe;

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<USpriteRenderer>();

	//ZombieRenderer->SetAutoScale(true);
	//ZombieRenderer->SetAutoScaleRatio(1.0f);

	Renderer->CreateAnimation("Attack_2", "Skeleton with Two Axes_Attack.png", 0, 12, 0.05f, false);
	Renderer->CreateAnimation("Attack_1", "Skeleton with Two Axes_Attack.png", 13, 25, 0.05f, false);
	Renderer->CreateAnimation("Attack_4", "Skeleton with Two Axes_Attack.png", 26, 38, 0.05f, false);
	Renderer->CreateAnimation("Attack_7", "Skeleton with Two Axes_Attack.png", 39, 51, 0.05f, false);
	Renderer->CreateAnimation("Attack_8", "Skeleton with Two Axes_Attack.png", 52, 64, 0.05f, false);
	Renderer->CreateAnimation("Attack_9", "Skeleton with Two Axes_Attack.png", 65, 77, 0.05f, false);
	Renderer->CreateAnimation("Attack_6", "Skeleton with Two Axes_Attack.png", 78, 90, 0.05f, false);
	Renderer->CreateAnimation("Attack_3", "Skeleton with Two Axes_Attack.png", 91, 103, 0.05f, false);

	Renderer->SetAnimationEvent("Attack_2", 12, [this]()
		{
			Renderer->ChangeAnimation("Idle_2");
		});
	Renderer->SetAnimationEvent("Attack_1", 25, [this]()
		{
			Renderer->ChangeAnimation("Idle_1");
		});
	Renderer->SetAnimationEvent("Attack_4", 38, [this]()
		{
			Renderer->ChangeAnimation("Idle_4");
		});
	Renderer->SetAnimationEvent("Attack_7", 51, [this]()
		{
			Renderer->ChangeAnimation("Idle_7");
		});
	Renderer->SetAnimationEvent("Attack_8", 64, [this]()
		{
			Renderer->ChangeAnimation("Idle_8");
		});
	Renderer->SetAnimationEvent("Attack_9", 77, [this]()
		{
			Renderer->ChangeAnimation("Idle_9");
		});
	Renderer->SetAnimationEvent("Attack_6", 90, [this]()
		{
			Renderer->ChangeAnimation("Idle_6");
		});
	Renderer->SetAnimationEvent("Attack_3", 103, [this]()
		{
			Renderer->ChangeAnimation("Idle_3");
		});

	Renderer->CreateAnimation("Die_2", "Skeleton with Two Axes_Die.png", 0, 16, 0.1f, false);
	Renderer->CreateAnimation("Die_1", "Skeleton with Two Axes_Die.png", 17, 33, 0.1f, false);
	Renderer->CreateAnimation("Die_4", "Skeleton with Two Axes_Die.png", 34, 50, 0.1f, false);
	Renderer->CreateAnimation("Die_7", "Skeleton with Two Axes_Die.png", 51, 67, 0.1f, false);
	Renderer->CreateAnimation("Die_8", "Skeleton with Two Axes_Die.png", 68, 84, 0.1f, false);
	Renderer->CreateAnimation("Die_9", "Skeleton with Two Axes_Die.png", 85, 101, 0.1f, false);
	Renderer->CreateAnimation("Die_6", "Skeleton with Two Axes_Die.png", 102, 118, 0.1f, false);
	Renderer->CreateAnimation("Die_3", "Skeleton with Two Axes_Die.png", 119, 135, 0.1f, false);

	Renderer->CreateAnimation("Hit_2", "Skeleton with Two Axes_Hit.png", 0, 5, 0.1f, false);
	Renderer->CreateAnimation("Hit_1", "Skeleton with Two Axes_Hit.png", 6, 11, 0.1f, false);
	Renderer->CreateAnimation("Hit_4", "Skeleton with Two Axes_Hit.png", 12, 17, 0.1f, false);
	Renderer->CreateAnimation("Hit_7", "Skeleton with Two Axes_Hit.png", 18, 23, 0.1f, false);
	Renderer->CreateAnimation("Hit_8", "Skeleton with Two Axes_Hit.png", 24, 29, 0.1f, false);
	Renderer->CreateAnimation("Hit_9", "Skeleton with Two Axes_Hit.png", 30, 35, 0.1f, false);
	Renderer->CreateAnimation("Hit_6", "Skeleton with Two Axes_Hit.png", 36, 41, 0.1f, false);
	Renderer->CreateAnimation("Hit_3", "Skeleton with Two Axes_Hit.png", 42, 47, 0.1f, false);

	Renderer->SetAnimationEvent("Hit_2", 5, [this]()
		{
			Renderer->ChangeAnimation("Idle_2");
		});
	Renderer->SetAnimationEvent("Hit_1", 11, [this]()
		{
			Renderer->ChangeAnimation("Idle_1");
		});
	Renderer->SetAnimationEvent("Hit_4", 17, [this]()
		{
			Renderer->ChangeAnimation("Idle_4");
		});
	Renderer->SetAnimationEvent("Hit_7", 23, [this]()
		{
			Renderer->ChangeAnimation("Idle_7");
		});
	Renderer->SetAnimationEvent("Hit_8", 29, [this]()
		{
			Renderer->ChangeAnimation("Idle_8");
		});
	Renderer->SetAnimationEvent("Hit_9", 35, [this]()
		{
			Renderer->ChangeAnimation("Idle_9");
		});
	Renderer->SetAnimationEvent("Hit_6", 41, [this]()
		{
			Renderer->ChangeAnimation("Idle_6");
		});
	Renderer->SetAnimationEvent("Hit_3", 47, [this]()
		{
			Renderer->ChangeAnimation("Idle_3");
		});

	Renderer->CreateAnimation("Idle_2", "Skeleton with Two Axes_Idle.png", 0, 11, 0.1f);
	Renderer->CreateAnimation("Idle_1", "Skeleton with Two Axes_Idle.png", 12, 23, 0.1f);
	Renderer->CreateAnimation("Idle_4", "Skeleton with Two Axes_Idle.png", 24, 35, 0.1f);
	Renderer->CreateAnimation("Idle_7", "Skeleton with Two Axes_Idle.png", 36, 47, 0.1f);
	Renderer->CreateAnimation("Idle_8", "Skeleton with Two Axes_Idle.png", 48, 59, 0.1f);
	Renderer->CreateAnimation("Idle_9", "Skeleton with Two Axes_Idle.png", 60, 71, 0.1f);
	Renderer->CreateAnimation("Idle_6", "Skeleton with Two Axes_Idle.png", 72, 83, 0.1f);
	Renderer->CreateAnimation("Idle_3", "Skeleton with Two Axes_Idle.png", 84, 95, 0.1f);

	Renderer->CreateAnimation("Special_2", "Skeleton with Two Axes_Special.png", 0, 15, 0.1f, false);
	Renderer->CreateAnimation("Special_1", "Skeleton with Two Axes_Special.png", 16, 31, 0.1f, false);
	Renderer->CreateAnimation("Special_4", "Skeleton with Two Axes_Special.png", 32, 47, 0.1f, false);
	Renderer->CreateAnimation("Special_7", "Skeleton with Two Axes_Special.png", 48, 63, 0.1f, false);
	Renderer->CreateAnimation("Special_8", "Skeleton with Two Axes_Special.png", 64, 79, 0.1f, false);
	Renderer->CreateAnimation("Special_9", "Skeleton with Two Axes_Special.png", 80, 95, 0.1f, false);
	Renderer->CreateAnimation("Special_6", "Skeleton with Two Axes_Special.png", 96, 111, 0.1f, false);
	Renderer->CreateAnimation("Special_3", "Skeleton with Two Axes_Special.png", 112, 127, 0.1f, false);

	Renderer->SetAnimationEvent("Special_2", 15, [this]()
		{
			Renderer->ChangeAnimation("Idle_2");
		});
	Renderer->SetAnimationEvent("Special_1", 31, [this]()
		{
			Renderer->ChangeAnimation("Idle_1");
		});
	Renderer->SetAnimationEvent("Special_4", 47, [this]()
		{
			Renderer->ChangeAnimation("Idle_4");
		});
	Renderer->SetAnimationEvent("Special_7", 63, [this]()
		{
			Renderer->ChangeAnimation("Idle_7");
		});
	Renderer->SetAnimationEvent("Special_8", 79, [this]()
		{
			Renderer->ChangeAnimation("Idle_8");
		});
	Renderer->SetAnimationEvent("Special_9", 95, [this]()
		{
			Renderer->ChangeAnimation("Idle_9");
		});
	Renderer->SetAnimationEvent("Special_6", 111, [this]()
		{
			Renderer->ChangeAnimation("Idle_6");
		});
	Renderer->SetAnimationEvent("Special_3", 127, [this]()
		{
			Renderer->ChangeAnimation("Idle_3");
		});

	Renderer->CreateAnimation("Walk_2", "Skeleton with Two Axes_Walk.png", 0, 7, 0.1f);
	Renderer->CreateAnimation("Walk_1", "Skeleton with Two Axes_Walk.png", 8, 15, 0.1f);
	Renderer->CreateAnimation("Walk_4", "Skeleton with Two Axes_Walk.png", 16, 23, 0.1f);
	Renderer->CreateAnimation("Walk_7", "Skeleton with Two Axes_Walk.png", 24, 31, 0.1f);
	Renderer->CreateAnimation("Walk_8", "Skeleton with Two Axes_Walk.png", 32, 39, 0.1f);
	Renderer->CreateAnimation("Walk_9", "Skeleton with Two Axes_Walk.png", 40, 47, 0.1f);
	Renderer->CreateAnimation("Walk_6", "Skeleton with Two Axes_Walk.png", 48, 55, 0.1f);
	Renderer->CreateAnimation("Walk_3", "Skeleton with Two Axes_Walk.png", 56, 63, 0.1f);


	Renderer->SetRelativeScale3D({ 50, 50, 1.0f });
	Renderer->SetupAttachment(RootComponent);

	Renderer->ChangeAnimation("Special_2");

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Monster");
	Collision->SetScale3D({ 50.0f, 50.0f });
}

ASkeleton_Axe::~ASkeleton_Axe()
{
}

void ASkeleton_Axe::BeginPlay()
{
	AActor::BeginPlay();
}

void ASkeleton_Axe::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

