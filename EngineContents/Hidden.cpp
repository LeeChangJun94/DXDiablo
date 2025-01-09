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
	MonsterTypeValue = EMonsterType::Hidden;

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	HiddenRenderer = CreateDefaultSubObject<USpriteRenderer>();

	//ZombieRenderer->SetAutoScale(true);
	//ZombieRenderer->SetAutoScaleRatio(1.0f);

	HiddenRenderer->CreateAnimation("Attack_2", "Zombie_Attack.png", 0, 11, 0.1f, false);

	HiddenRenderer->CreateAnimation("Attack_2", "Scavenger_Attack.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Attack_1", "Scavenger_Attack.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Attack_4", "Scavenger_Attack.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Attack_7", "Scavenger_Attack.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Attack_8", "Scavenger_Attack.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Attack_9", "Scavenger_Attack.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Attack_6", "Scavenger_Attack.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Attack_3", "Scavenger_Attack.png", 0, 11, 0.1f, false);

	HiddenRenderer->SetAnimationEvent("Attack_2", , [this]()
		{
			HiddenRenderer->ChangeAnimation("Idle_2");
		});
	HiddenRenderer->SetAnimationEvent("Attack_1", , [this]()
		{
			HiddenRenderer->ChangeAnimation("Idle_1");
		});
	HiddenRenderer->SetAnimationEvent("Attack_4", , [this]()
		{
			HiddenRenderer->ChangeAnimation("Idle_4");
		});
	HiddenRenderer->SetAnimationEvent("Attack_7", , [this]()
		{
			HiddenRenderer->ChangeAnimation("Idle_7");
		});
	HiddenRenderer->SetAnimationEvent("Attack_8", , [this]()
		{
			HiddenRenderer->ChangeAnimation("Idle_8");
		});
	HiddenRenderer->SetAnimationEvent("Attack_9", , [this]()
		{
			HiddenRenderer->ChangeAnimation("Idle_9");
		});
	HiddenRenderer->SetAnimationEvent("Attack_6", , [this]()
		{
			HiddenRenderer->ChangeAnimation("Idle_6");
		});
	HiddenRenderer->SetAnimationEvent("Attack_3", , [this]()
		{
			HiddenRenderer->ChangeAnimation("Idle_3");
		});

	HiddenRenderer->CreateAnimation("Die_2", "Scavenger_Die.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Die_1", "Scavenger_Die.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Die_4", "Scavenger_Die.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Die_7", "Scavenger_Die.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Die_8", "Scavenger_Die.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Die_9", "Scavenger_Die.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Die_6", "Scavenger_Die.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Die_3", "Scavenger_Die.png", 0, 11, 0.1f, false);

	HiddenRenderer->CreateAnimation("Hit_2", "Scavenger_Hit.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Hit_1", "Scavenger_Hit.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Hit_4", "Scavenger_Hit.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Hit_7", "Scavenger_Hit.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Hit_8", "Scavenger_Hit.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Hit_9", "Scavenger_Hit.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Hit_6", "Scavenger_Hit.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Hit_3", "Scavenger_Hit.png", 0, 11, 0.1f, false);

	HiddenRenderer->SetAnimationEvent("Attack_2", , [this]()
		{
			HiddenRenderer->ChangeAnimation("Idle_2");
		});
	HiddenRenderer->SetAnimationEvent("Attack_1", , [this]()
		{
			HiddenRenderer->ChangeAnimation("Idle_1");
		});
	HiddenRenderer->SetAnimationEvent("Attack_4", , [this]()
		{
			HiddenRenderer->ChangeAnimation("Idle_4");
		});
	HiddenRenderer->SetAnimationEvent("Attack_7", , [this]()
		{
			HiddenRenderer->ChangeAnimation("Idle_7");
		});
	HiddenRenderer->SetAnimationEvent("Attack_8", , [this]()
		{
			HiddenRenderer->ChangeAnimation("Idle_8");
		});
	HiddenRenderer->SetAnimationEvent("Attack_9", , [this]()
		{
			HiddenRenderer->ChangeAnimation("Idle_9");
		});
	HiddenRenderer->SetAnimationEvent("Attack_6", , [this]()
		{
			HiddenRenderer->ChangeAnimation("Idle_6");
		});
	HiddenRenderer->SetAnimationEvent("Attack_3", , [this]()
		{
			HiddenRenderer->ChangeAnimation("Idle_3");
		});

	HiddenRenderer->CreateAnimation("Idle_2", "Scavenger_Idle.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Idle_1", "Scavenger_Idle.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Idle_4", "Scavenger_Idle.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Idle_7", "Scavenger_Idle.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Idle_8", "Scavenger_Idle.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Idle_9", "Scavenger_Idle.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Idle_6", "Scavenger_Idle.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Idle_3", "Scavenger_Idle.png", 0, 11, 0.1f, false);

	HiddenRenderer->CreateAnimation("Special_2", "Scavenger_Special.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Special_1", "Scavenger_Special.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Special_4", "Scavenger_Special.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Special_7", "Scavenger_Special.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Special_8", "Scavenger_Special.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Special_9", "Scavenger_Special.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Special_6", "Scavenger_Special.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Special_3", "Scavenger_Special.png", 0, 11, 0.1f, false);

	HiddenRenderer->SetAnimationEvent("Attack_2", , [this]()
		{
			HiddenRenderer->ChangeAnimation("Idle_2");
		});
	HiddenRenderer->SetAnimationEvent("Attack_1", , [this]()
		{
			HiddenRenderer->ChangeAnimation("Idle_1");
		});
	HiddenRenderer->SetAnimationEvent("Attack_4", , [this]()
		{
			HiddenRenderer->ChangeAnimation("Idle_4");
		});
	HiddenRenderer->SetAnimationEvent("Attack_7", , [this]()
		{
			HiddenRenderer->ChangeAnimation("Idle_7");
		});
	HiddenRenderer->SetAnimationEvent("Attack_8", , [this]()
		{
			HiddenRenderer->ChangeAnimation("Idle_8");
		});
	HiddenRenderer->SetAnimationEvent("Attack_9", , [this]()
		{
			HiddenRenderer->ChangeAnimation("Idle_9");
		});
	HiddenRenderer->SetAnimationEvent("Attack_6", , [this]()
		{
			HiddenRenderer->ChangeAnimation("Idle_6");
		});
	HiddenRenderer->SetAnimationEvent("Attack_3", , [this]()
		{
			HiddenRenderer->ChangeAnimation("Idle_3");
		});

	HiddenRenderer->CreateAnimation("Walk_2", "Scavenger_Walk.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Walk_1", "Scavenger_Walk.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Walk_4", "Scavenger_Walk.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Walk_7", "Scavenger_Walk.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Walk_8", "Scavenger_Walk.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Walk_9", "Scavenger_Walk.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Walk_6", "Scavenger_Walk.png", 0, 11, 0.1f, false);
	HiddenRenderer->CreateAnimation("Walk_3", "Scavenger_Walk.png", 0, 11, 0.1f, false);


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