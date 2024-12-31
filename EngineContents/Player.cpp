#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/EngineCore.h>
#include <EngineCore/CameraActor.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineDebug.h>


APlayer::APlayer()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	// 랜더러를 만든다.
	PlayerRenderer = CreateDefaultSubObject<USpriteRenderer>();

	PlayerRenderer->CreateAnimation("Idle_2", "Warrior in Heavy Armor (Weaponless)_Idle_Town.png", 0, 19, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Idle_2");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->CreateAnimation("Idle_1", "Warrior in Heavy Armor (Weaponless)_Idle_Town.png", 20, 39, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Idle_1");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->CreateAnimation("Idle_4", "Warrior in Heavy Armor (Weaponless)_Idle_Town.png", 40, 59, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Idle_4");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->CreateAnimation("Idle_7", "Warrior in Heavy Armor (Weaponless)_Idle_Town.png", 60, 79, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Idle_7");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->CreateAnimation("Idle_8", "Warrior in Heavy Armor (Weaponless)_Idle_Town.png", 80, 99, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Idle_8");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->CreateAnimation("Idle_9", "Warrior in Heavy Armor (Weaponless)_Idle_Town.png", 100, 119, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Idle_9");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->CreateAnimation("Idle_6", "Warrior in Heavy Armor (Weaponless)_Idle_Town.png", 120, 139, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Idle_6");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->CreateAnimation("Idle_3", "Warrior in Heavy Armor (Weaponless)_Idle_Town.png", 140, 159, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Idle_3");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->CreateAnimation("Move_2", "Warrior in Heavy Armor (Weaponless)_Walk_Town.png", 0, 7, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Move_2");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->CreateAnimation("Move_1", "Warrior in Heavy Armor (Weaponless)_Walk_Town.png", 8, 15, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Move_1");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->CreateAnimation("Move_4", "Warrior in Heavy Armor (Weaponless)_Walk_Town.png", 16, 23, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Move_4");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->CreateAnimation("Move_7", "Warrior in Heavy Armor (Weaponless)_Walk_Town.png", 24, 31, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Move_7");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->CreateAnimation("Move_8", "Warrior in Heavy Armor (Weaponless)_Walk_Town.png", 32, 39, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Move_8");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->CreateAnimation("Move_9", "Warrior in Heavy Armor (Weaponless)_Walk_Town.png", 40, 47, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Move_9");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->CreateAnimation("Move_6", "Warrior in Heavy Armor (Weaponless)_Walk_Town.png", 48, 55, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Move_6");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->CreateAnimation("Move_3", "Warrior in Heavy Armor (Weaponless)_Walk_Town.png", 56, 63, 0.1f);
	{
		USpriteRenderer::FrameAnimation* Animation = PlayerRenderer->FindAnimation("Move_3");
		Animation->IsAutoScale = true;
		Animation->AutoScaleRatio = 1.0f;
	}

	PlayerRenderer->ChangeAnimation("Idle_2");

	// 부모가 존재하지 않는 root는 Relative든 Local이던 
	// 결과는 같다. 
	// 부모의 크기에 내가 영향을 받을수 있기 대문에 함수가 나뉜것이다.
	// 부모가 없으면
	PlayerRenderer->SetRelativeScale3D({ 50, 50, 1.0f });
	PlayerRenderer->SetupAttachment(RootComponent);


	//Child = CreateDefaultSubObject<USpriteRenderer>();
	//Child->SetSprite("Player.png", 2);
	//// 부모의 스케일이 나에게 영향을 주면서 나는 100이 아닐수가 있다
	//Child->SetRelativeLocation({100.0f, 0.0f, 0.0f});
	//Child->SetScale3D({ 50.0f, 50.0f, 1.0f });
	//// Child->SetScale3D({ 50.0f, 50.0f, 1.0f });
	//Child->SetupAttachment(RootComponent);
}

APlayer::~APlayer()
{
}

void APlayer::BeginPlay()
{
	AActor::BeginPlay();
}

void APlayer::Tick(float _DeltaTime)
{
	AActor::Tick(_DeltaTime);
	
	Direction();
	
	if (UEngineInput::IsPress('A'))
	{
		AddRelativeLocation(FVector{ -100.0f * _DeltaTime, 0.0f, 0.0f });
	}
	if (UEngineInput::IsPress('D'))
	{
		AddRelativeLocation(FVector{ 100.0f * _DeltaTime, 0.0f, 0.0f });
	}

	if (UEngineInput::IsPress('W'))
	{
		AddRelativeLocation(FVector{ 0.0f, 100.0f * _DeltaTime, 0.0f });
	}

	if (UEngineInput::IsPress('S'))
	{
		AddRelativeLocation(FVector{ 0.0f, -100.0f * _DeltaTime, 0.0f });
	}

	//if (UEngineInput::IsPress('Q'))
	//{
	//	AddActorRotation(FVector{ 0.0f, 0.0f , 360.0f * _DeltaTime });
	//}

	//if (UEngineInput::IsPress('E'))
	//{
	//	PlayerRenderer->ChangeAnimation("Move");
	//	// 단 1순간만 처리되는 걸로 
	//	// Child->AddRelativeLocation(FVector{ 100.0f * _DeltaTime, 0.0f , 0.0f });
	//}

	//if (UEngineInput::IsPress('R'))
	//{
	//	// Child->SetWorldLocation(FVector{ 100.0f, 0.0f , 0.0f });
	//}

	// AddActorLocation(FVector{ 100.0f * _DeltaTime, 0.0f, 0.0f});
}

void APlayer::Direction()
{
	UEngineDebug::OutPutString(std::to_string(MousePos.X));
	UEngineDebug::OutPutString(std::to_string(MousePos.Y));
	UEngineDebug::OutPutString(std::to_string(AngleDeg));

	std::shared_ptr<class ACameraActor> Camera = GetWorld()->GetCamera(0);
	MousePos = Camera->ScreenMousePosToWorldPos();
	//FVector PlayerWLocation = PlayerRenderer->GetTransformRef().WorldLocation;

	FVector MouseDir = MousePos - PlayerRenderer->GetTransformRef().WorldLocation;
	//MouseDir.Normalize();

	AngleDeg = FVector::GetVectorAngleDeg({ 1, 0 }, MouseDir);

	FVector MouseCross = FVector::Cross({ 1, 0 }, MouseDir);

	if (0.0f > MouseCross.Z)
	{
		AngleDeg = 360.0f - AngleDeg;
	}

	if (22.5f > AngleDeg)
	{
		Dir = '6';
	}
	else if (67.5f > AngleDeg)
	{
		Dir = '9';
	}
	else if (112.5f > AngleDeg)
	{
		Dir = '8';
	}
	else if (157.5f > AngleDeg)
	{
		Dir = '7';
	}
	else if (202.5f > AngleDeg)
	{
		Dir = '4';
	}
	else if (247.5f > AngleDeg)
	{
		Dir = '1';
	}
	else if (292.5f > AngleDeg)
	{
		Dir = '2';
	}
	else if (337.5f > AngleDeg)
	{
		Dir = '3';
	}
	else
	{
		Dir = '6';
	}

	PlayerRenderer->ChangeAnimation(Idle + Dir);
}
