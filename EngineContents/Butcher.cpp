#include "PreCompile.h"
#include "Butcher.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/EngineCore.h>
#include <EngineCore/CameraActor.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineDebug.h>
#include <EngineCore/Collision.h>

AButcher::AButcher()
{
	MonsterTypeValue = EMonsterType::Butcher;

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	ButcherRenderer = CreateDefaultSubObject<USpriteRenderer>();

	//ZombieRenderer->SetAutoScale(true);
	//ZombieRenderer->SetAutoScaleRatio(1.0f);

	/*Butcher_Attack.png"
		Butcher_Die.png", "
		Butcher_Hit.png", "
		Butcher_Idle.png", 
		Butcher_Walk.png", */

	ButcherRenderer->CreateAnimation("Attack_2", "Butcher_Attack.png", 0, 11, 0.1f, false);
	ButcherRenderer->CreateAnimation("Attack_1", "Butcher_Attack.png", 12, 23, 0.1f, false);
	ButcherRenderer->CreateAnimation("Attack_4", "Butcher_Attack.png", 24, 35, 0.1f, false);
	ButcherRenderer->CreateAnimation("Attack_7", "Butcher_Attack.png", 36, 47, 0.1f, false);
	ButcherRenderer->CreateAnimation("Attack_8", "Butcher_Attack.png", 48, 59, 0.1f, false);
	ButcherRenderer->CreateAnimation("Attack_9", "Butcher_Attack.png", 60, 71, 0.1f, false);
	ButcherRenderer->CreateAnimation("Attack_6", "Butcher_Attack.png", 72, 83, 0.1f, false);
	ButcherRenderer->CreateAnimation("Attack_3", "Butcher_Attack.png", 84, 95, 0.1f, false);

	ButcherRenderer->SetAnimationEvent("Attack_2", 11, [this]()
		{
			ButcherRenderer->ChangeAnimation("Idle_2");
		});
	ButcherRenderer->SetAnimationEvent("Attack_1", 23, [this]()
		{
			ButcherRenderer->ChangeAnimation("Idle_1");
		});
	ButcherRenderer->SetAnimationEvent("Attack_4", 35, [this]()
		{
			ButcherRenderer->ChangeAnimation("Idle_4");
		});
	ButcherRenderer->SetAnimationEvent("Attack_7", 47, [this]()
		{
			ButcherRenderer->ChangeAnimation("Idle_7");
		});
	ButcherRenderer->SetAnimationEvent("Attack_8", 59, [this]()
		{
			ButcherRenderer->ChangeAnimation("Idle_8");
		});
	ButcherRenderer->SetAnimationEvent("Attack_9", 71, [this]()
		{
			ButcherRenderer->ChangeAnimation("Idle_9");
		});
	ButcherRenderer->SetAnimationEvent("Attack_6", 83, [this]()
		{
			ButcherRenderer->ChangeAnimation("Idle_6");
		});
	ButcherRenderer->SetAnimationEvent("Attack_3", 95, [this]()
		{
			ButcherRenderer->ChangeAnimation("Idle_3");
		});

	ButcherRenderer->CreateAnimation("Die_2", "Butcher_Die.png", 0, 15, 0.1f, false);
	ButcherRenderer->CreateAnimation("Die_1", "Butcher_Die.png", 16, 31, 0.1f, false);
	ButcherRenderer->CreateAnimation("Die_4", "Butcher_Die.png", 32, 47, 0.1f, false);
	ButcherRenderer->CreateAnimation("Die_7", "Butcher_Die.png", 48, 63, 0.1f, false);
	ButcherRenderer->CreateAnimation("Die_8", "Butcher_Die.png", 64, 79, 0.1f, false);
	ButcherRenderer->CreateAnimation("Die_9", "Butcher_Die.png", 80, 95, 0.1f, false);
	ButcherRenderer->CreateAnimation("Die_6", "Butcher_Die.png", 96, 111, 0.1f, false);
	ButcherRenderer->CreateAnimation("Die_3", "Butcher_Die.png", 112, 127, 0.1f, false);

	ButcherRenderer->CreateAnimation("Hit_2", "Butcher_Hit.png", 0, 5, 0.1f, false);
	ButcherRenderer->CreateAnimation("Hit_1", "Butcher_Hit.png", 6, 11, 0.1f, false);
	ButcherRenderer->CreateAnimation("Hit_4", "Butcher_Hit.png", 12, 17, 0.1f, false);
	ButcherRenderer->CreateAnimation("Hit_7", "Butcher_Hit.png", 18, 23, 0.1f, false);
	ButcherRenderer->CreateAnimation("Hit_8", "Butcher_Hit.png", 24, 29, 0.1f, false);
	ButcherRenderer->CreateAnimation("Hit_9", "Butcher_Hit.png", 30, 35, 0.1f, false);
	ButcherRenderer->CreateAnimation("Hit_6", "Butcher_Hit.png", 36, 41, 0.1f, false);
	ButcherRenderer->CreateAnimation("Hit_3", "Butcher_Hit.png", 42, 47, 0.1f, false);

	ButcherRenderer->SetAnimationEvent("Hit_2", 5, [this]()
		{
			ButcherRenderer->ChangeAnimation("Idle_2");
		});
	ButcherRenderer->SetAnimationEvent("Hit_1", 11, [this]()
		{
			ButcherRenderer->ChangeAnimation("Idle_1");
		});
	ButcherRenderer->SetAnimationEvent("Hit_4", 17, [this]()
		{
			ButcherRenderer->ChangeAnimation("Idle_4");
		});
	ButcherRenderer->SetAnimationEvent("Hit_7", 23, [this]()
		{
			ButcherRenderer->ChangeAnimation("Idle_7");
		});
	ButcherRenderer->SetAnimationEvent("Hit_8", 29, [this]()
		{
			ButcherRenderer->ChangeAnimation("Idle_8");
		});
	ButcherRenderer->SetAnimationEvent("Hit_9", 35, [this]()
		{
			ButcherRenderer->ChangeAnimation("Idle_9");
		});
	ButcherRenderer->SetAnimationEvent("Hit_6", 41, [this]()
		{
			ButcherRenderer->ChangeAnimation("Idle_6");
		});
	ButcherRenderer->SetAnimationEvent("Hit_3", 47, [this]()
		{
			ButcherRenderer->ChangeAnimation("Idle_3");
		});

	ButcherRenderer->CreateAnimation("Idle_2", "Butcher_Idle.png", 0, 10, 0.1f);
	ButcherRenderer->CreateAnimation("Idle_1", "Butcher_Idle.png", 11, 21, 0.1f);
	ButcherRenderer->CreateAnimation("Idle_4", "Butcher_Idle.png", 22, 32, 0.1f);
	ButcherRenderer->CreateAnimation("Idle_7", "Butcher_Idle.png", 33, 43, 0.1f);
	ButcherRenderer->CreateAnimation("Idle_8", "Butcher_Idle.png", 44, 54, 0.1f);
	ButcherRenderer->CreateAnimation("Idle_9", "Butcher_Idle.png", 55, 65, 0.1f);
	ButcherRenderer->CreateAnimation("Idle_6", "Butcher_Idle.png", 66, 76, 0.1f);
	ButcherRenderer->CreateAnimation("Idle_3", "Butcher_Idle.png", 77, 87, 0.1f);

	ButcherRenderer->CreateAnimation("Walk_2", "Butcher_Walk.png", 0, 7, 0.1f);
	ButcherRenderer->CreateAnimation("Walk_1", "Butcher_Walk.png", 8, 15, 0.1f);
	ButcherRenderer->CreateAnimation("Walk_4", "Butcher_Walk.png", 16, 23, 0.1f);
	ButcherRenderer->CreateAnimation("Walk_7", "Butcher_Walk.png", 24, 31, 0.1f);
	ButcherRenderer->CreateAnimation("Walk_8", "Butcher_Walk.png", 32, 39, 0.1f);
	ButcherRenderer->CreateAnimation("Walk_9", "Butcher_Walk.png", 40, 47, 0.1f);
	ButcherRenderer->CreateAnimation("Walk_6", "Butcher_Walk.png", 48, 55, 0.1f);
	ButcherRenderer->CreateAnimation("Walk_3", "Butcher_Walk.png", 56, 63, 0.1f);


	ButcherRenderer->SetRelativeScale3D({ 50, 50, 1.0f });
	ButcherRenderer->SetupAttachment(RootComponent);

	ButcherRenderer->ChangeAnimation("Idle_2");

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Monster");
	Collision->SetScale3D({ 50.0f, 50.0f });
}

AButcher::~AButcher()
{
}

void AButcher::BeginPlay()
{
	AActor::BeginPlay();
}

void AButcher::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
}

