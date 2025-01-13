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
	MonsterTypeValue = EMonsterType::HIDDEN;

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<USpriteRenderer>();

	Renderer->CreateAnimation("Attack_2", "Hidden_Attack.png", 0, 11, 1.0f / 12, false);
	Renderer->CreateAnimation("Attack_1", "Hidden_Attack.png", 12, 23, 1.0f / 12, false);
	Renderer->CreateAnimation("Attack_4", "Hidden_Attack.png", 24, 35, 1.0f / 12, false);
	Renderer->CreateAnimation("Attack_7", "Hidden_Attack.png", 36, 47, 1.0f / 12, false);
	Renderer->CreateAnimation("Attack_8", "Hidden_Attack.png", 48, 59, 1.0f / 12, false);
	Renderer->CreateAnimation("Attack_9", "Hidden_Attack.png", 60, 71, 1.0f / 12, false);
	Renderer->CreateAnimation("Attack_6", "Hidden_Attack.png", 72, 83, 1.0f / 12, false);
	Renderer->CreateAnimation("Attack_3", "Hidden_Attack.png", 84, 95, 1.0f / 12, false);

	Renderer->SetAnimationEvent("Attack_2", 11, [this]()
		{
			Renderer->ChangeAnimation("Idle_2");
		});
	Renderer->SetAnimationEvent("Attack_1", 23, [this]()
		{
			Renderer->ChangeAnimation("Idle_1");
		});
	Renderer->SetAnimationEvent("Attack_4", 35, [this]()
		{
			Renderer->ChangeAnimation("Idle_4");
		});
	Renderer->SetAnimationEvent("Attack_7", 47, [this]()
		{
			Renderer->ChangeAnimation("Idle_7");
		});
	Renderer->SetAnimationEvent("Attack_8", 59, [this]()
		{
			Renderer->ChangeAnimation("Idle_8");
		});
	Renderer->SetAnimationEvent("Attack_9", 71, [this]()
		{
			Renderer->ChangeAnimation("Idle_9");
		});
	Renderer->SetAnimationEvent("Attack_6", 83, [this]()
		{
			Renderer->ChangeAnimation("Idle_6");
		});
	Renderer->SetAnimationEvent("Attack_3", 95, [this]()
		{
			Renderer->ChangeAnimation("Idle_3");
		});

	Renderer->CreateAnimation("Die_2", "Hidden_Die.png", 0, 23, 1.0f / 24, false);
	Renderer->CreateAnimation("Die_1", "Hidden_Die.png", 24, 47, 1.0f / 24, false);
	Renderer->CreateAnimation("Die_4", "Hidden_Die.png", 48, 71, 1.0f / 24, false);
	Renderer->CreateAnimation("Die_7", "Hidden_Die.png", 72, 95, 1.0f / 24, false);
	Renderer->CreateAnimation("Die_8", "Hidden_Die.png", 96, 119, 1.0f / 24, false);
	Renderer->CreateAnimation("Die_9", "Hidden_Die.png", 120, 143, 1.0f / 24, false);
	Renderer->CreateAnimation("Die_6", "Hidden_Die.png", 144, 167, 1.0f / 24, false);
	Renderer->CreateAnimation("Die_3", "Hidden_Die.png", 168, 191, 1.0f / 24, false);

	Renderer->CreateAnimation("Hit_2", "Hidden_Hit.png", 0, 7, 1.0f / 8, false);
	Renderer->CreateAnimation("Hit_1", "Hidden_Hit.png", 8, 15, 1.0f / 8, false);
	Renderer->CreateAnimation("Hit_4", "Hidden_Hit.png", 16, 23, 1.0f / 8, false);
	Renderer->CreateAnimation("Hit_7", "Hidden_Hit.png", 24, 31, 1.0f / 8, false);
	Renderer->CreateAnimation("Hit_8", "Hidden_Hit.png", 32, 39, 1.0f / 8, false);
	Renderer->CreateAnimation("Hit_9", "Hidden_Hit.png", 40, 47, 1.0f / 8, false);
	Renderer->CreateAnimation("Hit_6", "Hidden_Hit.png", 48, 55, 1.0f / 8, false);
	Renderer->CreateAnimation("Hit_3", "Hidden_Hit.png", 56, 63, 1.0f / 8, false);

	Renderer->SetAnimationEvent("Hit_2", 7, [this]()
		{
			Renderer->ChangeAnimation("Idle_2");
		});
	Renderer->SetAnimationEvent("Hit_1", 15, [this]()
		{
			Renderer->ChangeAnimation("Idle_1");
		});
	Renderer->SetAnimationEvent("Hit_4", 23, [this]()
		{
			Renderer->ChangeAnimation("Idle_4");
		});
	Renderer->SetAnimationEvent("Hit_7", 31, [this]()
		{
			Renderer->ChangeAnimation("Idle_7");
		});
	Renderer->SetAnimationEvent("Hit_8", 39, [this]()
		{
			Renderer->ChangeAnimation("Idle_8");
		});
	Renderer->SetAnimationEvent("Hit_9", 47, [this]()
		{
			Renderer->ChangeAnimation("Idle_9");
		});
	Renderer->SetAnimationEvent("Hit_6", 55, [this]()
		{
			Renderer->ChangeAnimation("Idle_6");
		});
	Renderer->SetAnimationEvent("Hit_3", 63, [this]()
		{
			Renderer->ChangeAnimation("Idle_3");
		});

	Renderer->CreateAnimation("Idle_2", "Hidden_Idle.png", 0, 15, 1.0f / 16);
	Renderer->CreateAnimation("Idle_1", "Hidden_Idle.png", 16, 31, 1.0f / 16);
	Renderer->CreateAnimation("Idle_4", "Hidden_Idle.png", 32, 47, 1.0f / 16);
	Renderer->CreateAnimation("Idle_7", "Hidden_Idle.png", 48, 63, 1.0f / 16);
	Renderer->CreateAnimation("Idle_8", "Hidden_Idle.png", 64, 79, 1.0f / 16);
	Renderer->CreateAnimation("Idle_9", "Hidden_Idle.png", 80, 95, 1.0f / 16);
	Renderer->CreateAnimation("Idle_6", "Hidden_Idle.png", 96, 111, 1.0f / 16);
	Renderer->CreateAnimation("Idle_3", "Hidden_Idle.png", 112, 127, 1.0f / 16);

	Renderer->CreateAnimation("Special_2", "Hidden_Special.png", 0, 14, 1.0f / 15, false);
	Renderer->CreateAnimation("Special_1", "Hidden_Special.png", 15, 29, 1.0f / 15, false);
	Renderer->CreateAnimation("Special_4", "Hidden_Special.png", 30, 44, 1.0f / 15, false);
	Renderer->CreateAnimation("Special_7", "Hidden_Special.png", 45, 59, 1.0f / 15, false);
	Renderer->CreateAnimation("Special_8", "Hidden_Special.png", 60, 74, 1.0f / 15, false);
	Renderer->CreateAnimation("Special_9", "Hidden_Special.png", 75, 89, 1.0f / 15, false);
	Renderer->CreateAnimation("Special_6", "Hidden_Special.png", 90, 104, 1.0f / 15, false);
	Renderer->CreateAnimation("Special_3", "Hidden_Special.png", 105, 119, 1.0f / 15, false);

	Renderer->SetAnimationEvent("Special_2", 14, [this]()
		{
			Renderer->ChangeAnimation("Idle_2");
		});
	Renderer->SetAnimationEvent("Special_1", 29, [this]()
		{
			Renderer->ChangeAnimation("Idle_1");
		});
	Renderer->SetAnimationEvent("Special_4", 44, [this]()
		{
			Renderer->ChangeAnimation("Idle_4");
		});
	Renderer->SetAnimationEvent("Special_7", 59, [this]()
		{
			Renderer->ChangeAnimation("Idle_7");
		});
	Renderer->SetAnimationEvent("Special_8", 74, [this]()
		{
			Renderer->ChangeAnimation("Idle_8");
		});
	Renderer->SetAnimationEvent("Special_9", 89, [this]()
		{
			Renderer->ChangeAnimation("Idle_9");
		});
	Renderer->SetAnimationEvent("Special_6", 104, [this]()
		{
			Renderer->ChangeAnimation("Idle_6");
		});
	Renderer->SetAnimationEvent("Special_3", 119, [this]()
		{
			Renderer->ChangeAnimation("Idle_3");
		});

	Renderer->CreateAnimation("Walk_2", "Hidden_Walk.png", 0, 7, 1.0f / 8);
	Renderer->CreateAnimation("Walk_1", "Hidden_Walk.png", 8, 15, 1.0f / 8);
	Renderer->CreateAnimation("Walk_4", "Hidden_Walk.png", 16, 23, 1.0f / 8);
	Renderer->CreateAnimation("Walk_7", "Hidden_Walk.png", 24, 31, 1.0f / 8);
	Renderer->CreateAnimation("Walk_8", "Hidden_Walk.png", 32, 39, 1.0f / 8);
	Renderer->CreateAnimation("Walk_9", "Hidden_Walk.png", 40, 47, 1.0f / 8);
	Renderer->CreateAnimation("Walk_6", "Hidden_Walk.png", 48, 55, 1.0f / 8);
	Renderer->CreateAnimation("Walk_3", "Hidden_Walk.png", 56, 63, 1.0f / 8);


	Renderer->SetRelativeScale3D({ 50, 50, 1.0f });
	Renderer->SetupAttachment(RootComponent);

	Renderer->ChangeAnimation("Special_2");

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Monster");
	Collision->SetScale3D({ 50.0f, 50.0f });

	FSM.CreateState(EStateType::IDLE, [](float _DeltaTime)
		{

		},
		[this]()
		{
			Renderer->ChangeAnimation("Idle_2");
		});

	FSM.CreateState(EStateType::ATTACK, [](float _DeltaTime)
		{

		},
		[this]()
		{
			Renderer->ChangeAnimation("Attack_2");
		});

	FSM.CreateState(EStateType::DIE, [](float _DeltaTime)
		{

		},
		[this]()
		{
			Renderer->ChangeAnimation("Die_2");
		});

	FSM.CreateState(EStateType::WALK, [](float _DeltaTime)
		{

		},
		[this]()
		{
			Renderer->ChangeAnimation("Walk_2");
		});

	FSM.CreateState(EStateType::SPECIAL, [](float _DeltaTime)
		{

		},
		[this]()
		{
			Renderer->ChangeAnimation("Special_2");
		});

	FSM.CreateState(EStateType::HIT, [](float _DeltaTime)
		{

		},
		[this]()
		{
			Renderer->ChangeAnimation("Hit_2");
		});
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