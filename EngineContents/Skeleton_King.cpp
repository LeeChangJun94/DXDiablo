#include "PreCompile.h"
#include "Skeleton_King.h"
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/EngineCore.h>
#include <EngineCore/CameraActor.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/FSMStateManager.h>
#include <EngineBase/EngineDebug.h>
#include <EngineCore/Collision.h>
#include "Player.h"

ASkeleton_King::ASkeleton_King()
{
	MonsterTypeValue = EMonsterType::SKELETON_KING;

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	Renderer = CreateDefaultSubObject<USpriteRenderer>();

	Renderer->CreateAnimation("Attack_2", "Skeleton King_Attack.png", 0, 15, 1.0f / 16, false);
	Renderer->CreateAnimation("Attack_1", "Skeleton King_Attack.png", 16, 31, 1.0f / 16, false);
	Renderer->CreateAnimation("Attack_4", "Skeleton King_Attack.png", 32, 47, 1.0f / 16, false);
	Renderer->CreateAnimation("Attack_7", "Skeleton King_Attack.png", 48, 63, 1.0f / 16, false);
	Renderer->CreateAnimation("Attack_8", "Skeleton King_Attack.png", 64, 79, 1.0f / 16, false);
	Renderer->CreateAnimation("Attack_9", "Skeleton King_Attack.png", 80, 95, 1.0f / 16, false);
	Renderer->CreateAnimation("Attack_6", "Skeleton King_Attack.png", 96, 111, 1.0f / 16, false);
	Renderer->CreateAnimation("Attack_3", "Skeleton King_Attack.png", 112, 127, 1.0f / 16, false);

	Renderer->SetAnimationEvent("Attack_2", 15, [this]()
		{
			Renderer->ChangeAnimation("Idle_2");
		});
	Renderer->SetAnimationEvent("Attack_1", 31, [this]()
		{
			Renderer->ChangeAnimation("Idle_1");
		});
	Renderer->SetAnimationEvent("Attack_4", 47, [this]()
		{
			Renderer->ChangeAnimation("Idle_4");
		});
	Renderer->SetAnimationEvent("Attack_7", 63, [this]()
		{
			Renderer->ChangeAnimation("Idle_7");
		});
	Renderer->SetAnimationEvent("Attack_8", 79, [this]()
		{
			Renderer->ChangeAnimation("Idle_8");
		});
	Renderer->SetAnimationEvent("Attack_9", 95, [this]()
		{
			Renderer->ChangeAnimation("Idle_9");
		});
	Renderer->SetAnimationEvent("Attack_6", 111, [this]()
		{
			Renderer->ChangeAnimation("Idle_6");
		});
	Renderer->SetAnimationEvent("Attack_3", 127, [this]()
		{
			Renderer->ChangeAnimation("Idle_3");
		});

	Renderer->CreateAnimation("Die_2", "Skeleton King_Die.png", 0, 15, 1.0f / 16, false);
	Renderer->CreateAnimation("Die_1", "Skeleton King_Die.png", 16, 31, 1.0f / 16, false);
	Renderer->CreateAnimation("Die_4", "Skeleton King_Die.png", 32, 47, 1.0f / 16, false);
	Renderer->CreateAnimation("Die_7", "Skeleton King_Die.png", 48, 63, 1.0f / 16, false);
	Renderer->CreateAnimation("Die_8", "Skeleton King_Die.png", 64, 79, 1.0f / 16, false);
	Renderer->CreateAnimation("Die_9", "Skeleton King_Die.png", 80, 95, 1.0f / 16, false);
	Renderer->CreateAnimation("Die_6", "Skeleton King_Die.png", 96, 111, 1.0f / 16, false);
	Renderer->CreateAnimation("Die_3", "Skeleton King_Die.png", 112, 127, 1.0f / 16, false);

	Renderer->CreateAnimation("Hit_2", "Skeleton King_Hit.png", 0, 5, 1.0f / 6, false);
	Renderer->CreateAnimation("Hit_1", "Skeleton King_Hit.png", 6, 11, 1.0f / 6, false);
	Renderer->CreateAnimation("Hit_4", "Skeleton King_Hit.png", 12, 17, 1.0f / 6, false);
	Renderer->CreateAnimation("Hit_7", "Skeleton King_Hit.png", 18, 23, 1.0f / 6, false);
	Renderer->CreateAnimation("Hit_8", "Skeleton King_Hit.png", 24, 29, 1.0f / 6, false);
	Renderer->CreateAnimation("Hit_9", "Skeleton King_Hit.png", 30, 35, 1.0f / 6, false);
	Renderer->CreateAnimation("Hit_6", "Skeleton King_Hit.png", 36, 41, 1.0f / 6, false);
	Renderer->CreateAnimation("Hit_3", "Skeleton King_Hit.png", 42, 47, 1.0f / 6, false);

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

	Renderer->CreateAnimation("Idle_2", "Skeleton King_Idle.png", 0, 7, 1.0f / 8);
	Renderer->CreateAnimation("Idle_1", "Skeleton King_Idle.png", 8, 15, 1.0f / 8);
	Renderer->CreateAnimation("Idle_4", "Skeleton King_Idle.png", 16, 23, 1.0f / 8);
	Renderer->CreateAnimation("Idle_7", "Skeleton King_Idle.png", 24, 31, 1.0f / 8);
	Renderer->CreateAnimation("Idle_8", "Skeleton King_Idle.png", 32, 39, 1.0f / 8);
	Renderer->CreateAnimation("Idle_9", "Skeleton King_Idle.png", 40, 47, 1.0f / 8);
	Renderer->CreateAnimation("Idle_6", "Skeleton King_Idle.png", 48, 55, 1.0f / 8);
	Renderer->CreateAnimation("Idle_3", "Skeleton King_Idle.png", 56, 63, 1.0f / 8);

	Renderer->CreateAnimation("Special_2", "Skeleton King_Special.png", 0, 11, 1.0f / 12, false);
	Renderer->CreateAnimation("Special_1", "Skeleton King_Special.png", 12, 23, 1.0f / 12, false);
	Renderer->CreateAnimation("Special_4", "Skeleton King_Special.png", 24, 35, 1.0f / 12, false);
	Renderer->CreateAnimation("Special_7", "Skeleton King_Special.png", 36, 47, 1.0f / 12, false);
	Renderer->CreateAnimation("Special_8", "Skeleton King_Special.png", 48, 59, 1.0f / 12, false);
	Renderer->CreateAnimation("Special_9", "Skeleton King_Special.png", 60, 71, 1.0f / 12, false);
	Renderer->CreateAnimation("Special_6", "Skeleton King_Special.png", 72, 83, 1.0f / 12, false);
	Renderer->CreateAnimation("Special_3", "Skeleton King_Special.png", 84, 95, 1.0f / 12, false);

	Renderer->SetAnimationEvent("Special_2", 11, [this]()
		{
			Renderer->ChangeAnimation("Idle_2");
		});
	Renderer->SetAnimationEvent("Special_1", 23, [this]()
		{
			Renderer->ChangeAnimation("Idle_1");
		});
	Renderer->SetAnimationEvent("Special_4", 35, [this]()
		{
			Renderer->ChangeAnimation("Idle_4");
		});
	Renderer->SetAnimationEvent("Special_7", 47, [this]()
		{
			Renderer->ChangeAnimation("Idle_7");
		});
	Renderer->SetAnimationEvent("Special_8", 59, [this]()
		{
			Renderer->ChangeAnimation("Idle_8");
		});
	Renderer->SetAnimationEvent("Special_9", 71, [this]()
		{
			Renderer->ChangeAnimation("Idle_9");
		});
	Renderer->SetAnimationEvent("Special_6", 83, [this]()
		{
			Renderer->ChangeAnimation("Idle_6");
		});
	Renderer->SetAnimationEvent("Special_3", 95, [this]()
		{
			Renderer->ChangeAnimation("Idle_3");
		});

	Renderer->CreateAnimation("Walk_2", "Skeleton King_Walk.png", 0, 7, 1.0f / 8);
	Renderer->CreateAnimation("Walk_1", "Skeleton King_Walk.png", 8, 15, 1.0f / 8);
	Renderer->CreateAnimation("Walk_4", "Skeleton King_Walk.png", 16, 23, 1.0f / 8);
	Renderer->CreateAnimation("Walk_7", "Skeleton King_Walk.png", 24, 31, 1.0f / 8);
	Renderer->CreateAnimation("Walk_8", "Skeleton King_Walk.png", 32, 39, 1.0f / 8);
	Renderer->CreateAnimation("Walk_9", "Skeleton King_Walk.png", 40, 47, 1.0f / 8);
	Renderer->CreateAnimation("Walk_6", "Skeleton King_Walk.png", 48, 55, 1.0f / 8);
	Renderer->CreateAnimation("Walk_3", "Skeleton King_Walk.png", 56, 63, 1.0f / 8);


	Renderer->SetRelativeScale3D({ 50, 50, 1.0f });
	Renderer->SetupAttachment(RootComponent);

	Renderer->ChangeAnimation("Attack_2");

	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Monster");
	Collision->SetScale3D({ 50.0f, 50.0f });

	FSM.CreateState(EStateType::IDLE, [](float _DeltaTime)
		{

		},
		[this]()
		{
			Renderer->ChangeAnimation("Idle_" + Dir);
		});

	FSM.CreateState(EStateType::ATTACK, [](float _DeltaTime)
		{

		},
		[this]()
		{
			Renderer->ChangeAnimation("Attack_" + Dir);
		});

	FSM.CreateState(EStateType::DIE, [](float _DeltaTime)
		{

		},
		[this]()
		{
			Renderer->ChangeAnimation("Die_" + Dir);
		});

	FSM.CreateState(EStateType::WALK, [this](float _DeltaTime)
		{
			MonsterMove(_DeltaTime);
		},
		[this]()
		{
			Renderer->ChangeAnimation("Walk_" + Dir);
		});

	FSM.CreateState(EStateType::SPECIAL, [](float _DeltaTime)
		{

		},
		[this]()
		{
			Renderer->ChangeAnimation("Special_" + Dir);
		});

	FSM.CreateState(EStateType::HIT, [](float _DeltaTime)
		{

		},
		[this]()
		{
			Renderer->ChangeAnimation("Hit_" + Dir);
		});
	FSM.ChangeState(EStateType::IDLE);
}

ASkeleton_King::~ASkeleton_King()
{
}

void ASkeleton_King::BeginPlay()
{
	AMonster::BeginPlay();
}

void ASkeleton_King::Tick(float _DeltaTime)
{
	AMonster::Tick(_DeltaTime);
	FSM.Update(_DeltaTime);
	//MonsterDirection();
}

