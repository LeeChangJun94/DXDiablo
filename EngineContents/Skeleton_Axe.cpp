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

	Skeleton_AxeRenderer = CreateDefaultSubObject<USpriteRenderer>();

	//ZombieRenderer->SetAutoScale(true);
	//ZombieRenderer->SetAutoScaleRatio(1.0f);

	Skeleton_AxeRenderer->CreateAnimation("Attack_2", "Skeleton with Two Axes_Attack.png", 0, 12, 0.1f, false);
	Skeleton_AxeRenderer->CreateAnimation("Attack_1", "Skeleton with Two Axes_Attack.png", 13, 25, 0.1f, false);
	Skeleton_AxeRenderer->CreateAnimation("Attack_4", "Skeleton with Two Axes_Attack.png", 26, 38, 0.1f, false);
	Skeleton_AxeRenderer->CreateAnimation("Attack_7", "Skeleton with Two Axes_Attack.png", 39, 51, 0.1f, false);
	Skeleton_AxeRenderer->CreateAnimation("Attack_8", "Skeleton with Two Axes_Attack.png", 52, 64, 0.1f, false);
	Skeleton_AxeRenderer->CreateAnimation("Attack_9", "Skeleton with Two Axes_Attack.png", 65, 77, 0.1f, false);
	Skeleton_AxeRenderer->CreateAnimation("Attack_6", "Skeleton with Two Axes_Attack.png", 78, 90, 0.1f, false);
	Skeleton_AxeRenderer->CreateAnimation("Attack_3", "Skeleton with Two Axes_Attack.png", 91, 103, 0.1f, false);

	Skeleton_AxeRenderer->SetAnimationEvent("Attack_2", 12, [this]()
		{
			Skeleton_AxeRenderer->ChangeAnimation("Idle_2");
		});
	Skeleton_AxeRenderer->SetAnimationEvent("Attack_1", 25, [this]()
		{
			Skeleton_AxeRenderer->ChangeAnimation("Idle_1");
		});
	Skeleton_AxeRenderer->SetAnimationEvent("Attack_4", 38, [this]()
		{
			Skeleton_AxeRenderer->ChangeAnimation("Idle_4");
		});
	Skeleton_AxeRenderer->SetAnimationEvent("Attack_7", 51, [this]()
		{
			Skeleton_AxeRenderer->ChangeAnimation("Idle_7");
		});
	Skeleton_AxeRenderer->SetAnimationEvent("Attack_8", 64, [this]()
		{
			Skeleton_AxeRenderer->ChangeAnimation("Idle_8");
		});
	Skeleton_AxeRenderer->SetAnimationEvent("Attack_9", 77, [this]()
		{
			Skeleton_AxeRenderer->ChangeAnimation("Idle_9");
		});
	Skeleton_AxeRenderer->SetAnimationEvent("Attack_6", 90, [this]()
		{
			Skeleton_AxeRenderer->ChangeAnimation("Idle_6");
		});
	Skeleton_AxeRenderer->SetAnimationEvent("Attack_3", 103, [this]()
		{
			Skeleton_AxeRenderer->ChangeAnimation("Idle_3");
		});

	Skeleton_AxeRenderer->CreateAnimation("Die_2", "Skeleton with Two Axes_Die.png", 0, 16, 0.1f, false);
	Skeleton_AxeRenderer->CreateAnimation("Die_1", "Skeleton with Two Axes_Die.png", 17, 33, 0.1f, false);
	Skeleton_AxeRenderer->CreateAnimation("Die_4", "Skeleton with Two Axes_Die.png", 34, 50, 0.1f, false);
	Skeleton_AxeRenderer->CreateAnimation("Die_7", "Skeleton with Two Axes_Die.png", 51, 67, 0.1f, false);
	Skeleton_AxeRenderer->CreateAnimation("Die_8", "Skeleton with Two Axes_Die.png", 68, 84, 0.1f, false);
	Skeleton_AxeRenderer->CreateAnimation("Die_9", "Skeleton with Two Axes_Die.png", 85, 101, 0.1f, false);
	Skeleton_AxeRenderer->CreateAnimation("Die_6", "Skeleton with Two Axes_Die.png", 102, 118, 0.1f, false);
	Skeleton_AxeRenderer->CreateAnimation("Die_3", "Skeleton with Two Axes_Die.png", 119, 135, 0.1f, false);

	Skeleton_AxeRenderer->CreateAnimation("Hit_2", "Skeleton with Two Axes_Hit.png", 0, 5, 0.1f, false);
	Skeleton_AxeRenderer->CreateAnimation("Hit_1", "Skeleton with Two Axes_Hit.png", 6, 11, 0.1f, false);
	Skeleton_AxeRenderer->CreateAnimation("Hit_4", "Skeleton with Two Axes_Hit.png", 12, 17, 0.1f, false);
	Skeleton_AxeRenderer->CreateAnimation("Hit_7", "Skeleton with Two Axes_Hit.png", 18, 23, 0.1f, false);
	Skeleton_AxeRenderer->CreateAnimation("Hit_8", "Skeleton with Two Axes_Hit.png", 24, 29, 0.1f, false);
	Skeleton_AxeRenderer->CreateAnimation("Hit_9", "Skeleton with Two Axes_Hit.png", 30, 35, 0.1f, false);
	Skeleton_AxeRenderer->CreateAnimation("Hit_6", "Skeleton with Two Axes_Hit.png", 36, 41, 0.1f, false);
	Skeleton_AxeRenderer->CreateAnimation("Hit_3", "Skeleton with Two Axes_Hit.png", 42, 47, 0.1f, false);

	Skeleton_AxeRenderer->SetAnimationEvent("Hit_2", 5, [this]()
		{
			Skeleton_AxeRenderer->ChangeAnimation("Idle_2");
		});
	Skeleton_AxeRenderer->SetAnimationEvent("Hit_1", 11, [this]()
		{
			Skeleton_AxeRenderer->ChangeAnimation("Idle_1");
		});
	Skeleton_AxeRenderer->SetAnimationEvent("Hit_4", 17, [this]()
		{
			Skeleton_AxeRenderer->ChangeAnimation("Idle_4");
		});
	Skeleton_AxeRenderer->SetAnimationEvent("Hit_7", 23, [this]()
		{
			Skeleton_AxeRenderer->ChangeAnimation("Idle_7");
		});
	Skeleton_AxeRenderer->SetAnimationEvent("Hit_8", 29, [this]()
		{
			Skeleton_AxeRenderer->ChangeAnimation("Idle_8");
		});
	Skeleton_AxeRenderer->SetAnimationEvent("Hit_9", 35, [this]()
		{
			Skeleton_AxeRenderer->ChangeAnimation("Idle_9");
		});
	Skeleton_AxeRenderer->SetAnimationEvent("Hit_6", 41, [this]()
		{
			Skeleton_AxeRenderer->ChangeAnimation("Idle_6");
		});
	Skeleton_AxeRenderer->SetAnimationEvent("Hit_3", 47, [this]()
		{
			Skeleton_AxeRenderer->ChangeAnimation("Idle_3");
		});

	Skeleton_AxeRenderer->CreateAnimation("Idle_2", "Skeleton with Two Axes_Idle.png", 0, 11, 0.1f);
	Skeleton_AxeRenderer->CreateAnimation("Idle_1", "Skeleton with Two Axes_Idle.png", 12, 23, 0.1f);
	Skeleton_AxeRenderer->CreateAnimation("Idle_4", "Skeleton with Two Axes_Idle.png", 24, 35, 0.1f);
	Skeleton_AxeRenderer->CreateAnimation("Idle_7", "Skeleton with Two Axes_Idle.png", 36, 47, 0.1f);
	Skeleton_AxeRenderer->CreateAnimation("Idle_8", "Skeleton with Two Axes_Idle.png", 48, 59, 0.1f);
	Skeleton_AxeRenderer->CreateAnimation("Idle_9", "Skeleton with Two Axes_Idle.png", 60, 71, 0.1f);
	Skeleton_AxeRenderer->CreateAnimation("Idle_6", "Skeleton with Two Axes_Idle.png", 72, 83, 0.1f);
	Skeleton_AxeRenderer->CreateAnimation("Idle_3", "Skeleton with Two Axes_Idle.png", 84, 95, 0.1f);

	Skeleton_AxeRenderer->CreateAnimation("Special_2", "Skeleton with Two Axes_Special.png", 0, 15, 0.1f, false);
	Skeleton_AxeRenderer->CreateAnimation("Special_1", "Skeleton with Two Axes_Special.png", 16, 31, 0.1f, false);
	Skeleton_AxeRenderer->CreateAnimation("Special_4", "Skeleton with Two Axes_Special.png", 32, 47, 0.1f, false);
	Skeleton_AxeRenderer->CreateAnimation("Special_7", "Skeleton with Two Axes_Special.png", 48, 63, 0.1f, false);
	Skeleton_AxeRenderer->CreateAnimation("Special_8", "Skeleton with Two Axes_Special.png", 64, 79, 0.1f, false);
	Skeleton_AxeRenderer->CreateAnimation("Special_9", "Skeleton with Two Axes_Special.png", 80, 95, 0.1f, false);
	Skeleton_AxeRenderer->CreateAnimation("Special_6", "Skeleton with Two Axes_Special.png", 96, 111, 0.1f, false);
	Skeleton_AxeRenderer->CreateAnimation("Special_3", "Skeleton with Two Axes_Special.png", 112, 127, 0.1f, false);

	Skeleton_AxeRenderer->SetAnimationEvent("Special_2", 15, [this]()
		{
			Skeleton_AxeRenderer->ChangeAnimation("Idle_2");
		});
	Skeleton_AxeRenderer->SetAnimationEvent("Special_1", 31, [this]()
		{
			Skeleton_AxeRenderer->ChangeAnimation("Idle_1");
		});
	Skeleton_AxeRenderer->SetAnimationEvent("Special_4", 47, [this]()
		{
			Skeleton_AxeRenderer->ChangeAnimation("Idle_4");
		});
	Skeleton_AxeRenderer->SetAnimationEvent("Special_7", 63, [this]()
		{
			Skeleton_AxeRenderer->ChangeAnimation("Idle_7");
		});
	Skeleton_AxeRenderer->SetAnimationEvent("Special_8", 79, [this]()
		{
			Skeleton_AxeRenderer->ChangeAnimation("Idle_8");
		});
	Skeleton_AxeRenderer->SetAnimationEvent("Special_9", 95, [this]()
		{
			Skeleton_AxeRenderer->ChangeAnimation("Idle_9");
		});
	Skeleton_AxeRenderer->SetAnimationEvent("Special_6", 111, [this]()
		{
			Skeleton_AxeRenderer->ChangeAnimation("Idle_6");
		});
	Skeleton_AxeRenderer->SetAnimationEvent("Special_3", 127, [this]()
		{
			Skeleton_AxeRenderer->ChangeAnimation("Idle_3");
		});

	Skeleton_AxeRenderer->CreateAnimation("Walk_2", "Skeleton with Two Axes_Walk.png", 0, 7, 0.1f);
	Skeleton_AxeRenderer->CreateAnimation("Walk_1", "Skeleton with Two Axes_Walk.png", 8, 15, 0.1f);
	Skeleton_AxeRenderer->CreateAnimation("Walk_4", "Skeleton with Two Axes_Walk.png", 16, 23, 0.1f);
	Skeleton_AxeRenderer->CreateAnimation("Walk_7", "Skeleton with Two Axes_Walk.png", 24, 31, 0.1f);
	Skeleton_AxeRenderer->CreateAnimation("Walk_8", "Skeleton with Two Axes_Walk.png", 32, 39, 0.1f);
	Skeleton_AxeRenderer->CreateAnimation("Walk_9", "Skeleton with Two Axes_Walk.png", 40, 47, 0.1f);
	Skeleton_AxeRenderer->CreateAnimation("Walk_6", "Skeleton with Two Axes_Walk.png", 48, 55, 0.1f);
	Skeleton_AxeRenderer->CreateAnimation("Walk_3", "Skeleton with Two Axes_Walk.png", 56, 63, 0.1f);


	Skeleton_AxeRenderer->SetRelativeScale3D({ 50, 50, 1.0f });
	Skeleton_AxeRenderer->SetupAttachment(RootComponent);

	Skeleton_AxeRenderer->ChangeAnimation("Special_2");

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

