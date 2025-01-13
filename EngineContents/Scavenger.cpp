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
	MonsterTypeValue = EMonsterType::SCAVENGER;

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<USpriteRenderer>();

	Renderer->CreateAnimation("Attack_2", "Scavenger_Attack.png", 0, 11, 1.0f / 12, false);
	Renderer->CreateAnimation("Attack_1", "Scavenger_Attack.png", 12, 23, 1.0f / 12, false);
	Renderer->CreateAnimation("Attack_4", "Scavenger_Attack.png", 24, 35, 1.0f / 12, false);
	Renderer->CreateAnimation("Attack_7", "Scavenger_Attack.png", 36, 47, 1.0f / 12, false);
	Renderer->CreateAnimation("Attack_8", "Scavenger_Attack.png", 48, 59, 1.0f / 12, false);
	Renderer->CreateAnimation("Attack_9", "Scavenger_Attack.png", 60, 71, 1.0f / 12, false);
	Renderer->CreateAnimation("Attack_6", "Scavenger_Attack.png", 72, 83, 1.0f / 12, false);
	Renderer->CreateAnimation("Attack_3", "Scavenger_Attack.png", 84, 95, 1.0f / 12, false);

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
	Renderer->SetAnimationEvent("Attack_7",47 , [this]()
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

	Renderer->CreateAnimation("Die_2", "Scavenger_Die.png", 0, 19, 1.0f / 20, false);
	Renderer->CreateAnimation("Die_1", "Scavenger_Die.png", 20, 39, 1.0f / 20, false);
	Renderer->CreateAnimation("Die_4", "Scavenger_Die.png", 40, 59, 1.0f / 20, false);
	Renderer->CreateAnimation("Die_7", "Scavenger_Die.png", 60, 79, 1.0f / 20, false);
	Renderer->CreateAnimation("Die_8", "Scavenger_Die.png", 80, 99, 1.0f / 20, false);
	Renderer->CreateAnimation("Die_9", "Scavenger_Die.png", 100, 119, 1.0f / 20, false);
	Renderer->CreateAnimation("Die_6", "Scavenger_Die.png", 120, 139, 1.0f / 20, false);
	Renderer->CreateAnimation("Die_3", "Scavenger_Die.png", 140, 159, 1.0f / 20, false);

	Renderer->CreateAnimation("Hit_2", "Scavenger_Hit.png", 0, 7, 1.0f / 8, false);
	Renderer->CreateAnimation("Hit_1", "Scavenger_Hit.png", 8, 15, 1.0f / 8, false);
	Renderer->CreateAnimation("Hit_4", "Scavenger_Hit.png", 16, 23, 1.0f / 8, false);
	Renderer->CreateAnimation("Hit_7", "Scavenger_Hit.png", 24, 31, 1.0f / 8, false);
	Renderer->CreateAnimation("Hit_8", "Scavenger_Hit.png", 32, 39, 1.0f / 8, false);
	Renderer->CreateAnimation("Hit_9", "Scavenger_Hit.png", 40, 47, 1.0f / 8, false);
	Renderer->CreateAnimation("Hit_6", "Scavenger_Hit.png", 48, 55, 1.0f / 8, false);
	Renderer->CreateAnimation("Hit_3", "Scavenger_Hit.png", 56, 63, 1.0f / 8, false);

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

	Renderer->CreateAnimation("Idle_2", "Scavenger_Idle.png", 0, 11, 1.0f / 12);
	Renderer->CreateAnimation("Idle_1", "Scavenger_Idle.png", 12, 23, 1.0f / 12);
	Renderer->CreateAnimation("Idle_4", "Scavenger_Idle.png", 24, 35, 1.0f / 12);
	Renderer->CreateAnimation("Idle_7", "Scavenger_Idle.png", 36, 47, 1.0f / 12);
	Renderer->CreateAnimation("Idle_8", "Scavenger_Idle.png", 48, 59, 1.0f / 12);
	Renderer->CreateAnimation("Idle_9", "Scavenger_Idle.png", 60, 71, 1.0f / 12);
	Renderer->CreateAnimation("Idle_6", "Scavenger_Idle.png", 72, 83, 1.0f / 12);
	Renderer->CreateAnimation("Idle_3", "Scavenger_Idle.png", 84, 95, 1.0f / 12);

	Renderer->CreateAnimation("Special_2", "Scavenger_Special.png", 0, 10, 1.0f / 11, false);
	Renderer->CreateAnimation("Special_1", "Scavenger_Special.png", 11, 21, 1.0f / 11, false);
	Renderer->CreateAnimation("Special_4", "Scavenger_Special.png", 22, 32, 1.0f / 11, false);
	Renderer->CreateAnimation("Special_7", "Scavenger_Special.png", 33, 43, 1.0f / 11, false);
	Renderer->CreateAnimation("Special_8", "Scavenger_Special.png", 44, 54, 1.0f / 11, false);
	Renderer->CreateAnimation("Special_9", "Scavenger_Special.png", 55, 65, 1.0f / 11, false);
	Renderer->CreateAnimation("Special_6", "Scavenger_Special.png", 66, 76, 1.0f / 11, false);
	Renderer->CreateAnimation("Special_3", "Scavenger_Special.png", 77, 87, 1.0f / 11, false);

	Renderer->SetAnimationEvent("Special_2", 10, [this]()
		{
			Renderer->ChangeAnimation("Idle_2");
		});
	Renderer->SetAnimationEvent("Special_1", 21, [this]()
		{
			Renderer->ChangeAnimation("Idle_1");
		});
	Renderer->SetAnimationEvent("Special_4", 32, [this]()
		{
			Renderer->ChangeAnimation("Idle_4");
		});
	Renderer->SetAnimationEvent("Special_7", 43, [this]()
		{
			Renderer->ChangeAnimation("Idle_7");
		});
	Renderer->SetAnimationEvent("Special_8", 54, [this]()
		{
			Renderer->ChangeAnimation("Idle_8");
		});
	Renderer->SetAnimationEvent("Special_9", 65, [this]()
		{
			Renderer->ChangeAnimation("Idle_9");
		});
	Renderer->SetAnimationEvent("Special_6", 76, [this]()
		{
			Renderer->ChangeAnimation("Idle_6");
		});
	Renderer->SetAnimationEvent("Special_3", 87, [this]()
		{
			Renderer->ChangeAnimation("Idle_3");
		});

	Renderer->CreateAnimation("Walk_2", "Scavenger_Walk.png", 0, 7, 1.0f / 8);
	Renderer->CreateAnimation("Walk_1", "Scavenger_Walk.png", 8, 15, 1.0f / 8);
	Renderer->CreateAnimation("Walk_4", "Scavenger_Walk.png", 16, 23, 1.0f / 8);
	Renderer->CreateAnimation("Walk_7", "Scavenger_Walk.png", 24, 31, 1.0f / 8);
	Renderer->CreateAnimation("Walk_8", "Scavenger_Walk.png", 32, 39, 1.0f / 8);
	Renderer->CreateAnimation("Walk_9", "Scavenger_Walk.png", 40, 47, 1.0f / 8);
	Renderer->CreateAnimation("Walk_6", "Scavenger_Walk.png", 48, 55, 1.0f / 8);
	Renderer->CreateAnimation("Walk_3", "Scavenger_Walk.png", 56, 63, 1.0f / 8);


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

