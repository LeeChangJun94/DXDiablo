#include "PreCompile.h"
#include "Player.h"
#include <EngineCore/SpriteRenderer.h>
#include <EnginePlatform/EngineInput.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/EngineCore.h>
#include <EngineCore/CameraActor.h>
#include <EngineBase/EngineMath.h>
#include <EngineBase/EngineDebug.h>
#include <EngineCore/TimeEventComponent.h>
#include <EngineCore/Collision.h>
#include "MyCustomRenderer.h"


APlayer::APlayer()
{
	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	// 랜더러를 만든다.
	PlayerRenderer = CreateDefaultSubObject<USpriteRenderer>();
	PlayerRenderer->SetupAttachment(RootComponent);

	//PlayerRenderer->SetAutoScale(true);
	PlayerRenderer->SetAutoScaleRatio(1.0f);
	//PlayerRenderer->BillboardOn();

	//GetWorld()->GetMainCamera()->AttachToActor(this);

	// Sword & Shield
	{
		PlayerRenderer->CreateAnimation("Walk_Sword & Shield_Town_2", "Warrior in Light Armor with Sword & Shield_Walk_Town.png", 0, 7, 0.1f);
		PlayerRenderer->CreateAnimation("Walk_Sword & Shield_Town_1", "Warrior in Light Armor with Sword & Shield_Walk_Town.png", 8, 15, 0.1f);
		PlayerRenderer->CreateAnimation("Walk_Sword & Shield_Town_4", "Warrior in Light Armor with Sword & Shield_Walk_Town.png", 16, 23, 0.1f);
		PlayerRenderer->CreateAnimation("Walk_Sword & Shield_Town_7", "Warrior in Light Armor with Sword & Shield_Walk_Town.png", 24, 31, 0.1f);
		PlayerRenderer->CreateAnimation("Walk_Sword & Shield_Town_8", "Warrior in Light Armor with Sword & Shield_Walk_Town.png", 32, 39, 0.1f);
		PlayerRenderer->CreateAnimation("Walk_Sword & Shield_Town_9", "Warrior in Light Armor with Sword & Shield_Walk_Town.png", 40, 47, 0.1f);
		PlayerRenderer->CreateAnimation("Walk_Sword & Shield_Town_6", "Warrior in Light Armor with Sword & Shield_Walk_Town.png", 48, 55, 0.1f);
		PlayerRenderer->CreateAnimation("Walk_Sword & Shield_Town_3", "Warrior in Light Armor with Sword & Shield_Walk_Town.png", 56, 63, 0.1f);
		
		PlayerRenderer->CreateAnimation("Attack_Sword & Shield_Dungeon_2", "Warrior in Light Armor with Sword & Shield_Attack.png", 0, 15, 0.05f, false);
		PlayerRenderer->CreateAnimation("Attack_Sword & Shield_Dungeon_1", "Warrior in Light Armor with Sword & Shield_Attack.png", 16, 31, 0.05f, false);
		PlayerRenderer->CreateAnimation("Attack_Sword & Shield_Dungeon_4", "Warrior in Light Armor with Sword & Shield_Attack.png", 32, 47, 0.05f, false);
		PlayerRenderer->CreateAnimation("Attack_Sword & Shield_Dungeon_7", "Warrior in Light Armor with Sword & Shield_Attack.png", 48, 63, 0.05f, false);
		PlayerRenderer->CreateAnimation("Attack_Sword & Shield_Dungeon_8", "Warrior in Light Armor with Sword & Shield_Attack.png", 64, 79, 0.05f, false);
		PlayerRenderer->CreateAnimation("Attack_Sword & Shield_Dungeon_9", "Warrior in Light Armor with Sword & Shield_Attack.png", 80, 95, 0.05f, false);
		PlayerRenderer->CreateAnimation("Attack_Sword & Shield_Dungeon_6", "Warrior in Light Armor with Sword & Shield_Attack.png", 96, 111, 0.05f, false);
		PlayerRenderer->CreateAnimation("Attack_Sword & Shield_Dungeon_3", "Warrior in Light Armor with Sword & Shield_Attack.png", 112, 127, 0.05f, false);

		PlayerRenderer->SetAnimationEvent("Attack_Sword & Shield_Dungeon_2", 15, [this]()
			{
				PlayerRenderer->ChangeAnimation("Idle_Sword & Shield_Dungeon_2");
			});
		PlayerRenderer->SetAnimationEvent("Attack_Sword & Shield_Dungeon_1", 31, [this]()
			{
				PlayerRenderer->ChangeAnimation("Idle_Sword & Shield_Dungeon_1");
			});
		PlayerRenderer->SetAnimationEvent("Attack_Sword & Shield_Dungeon_4", 47, [this]()
			{
				PlayerRenderer->ChangeAnimation("Idle_Sword & Shield_Dungeon_4");
			});
		PlayerRenderer->SetAnimationEvent("Attack_Sword & Shield_Dungeon_7", 63, [this]()
			{
				PlayerRenderer->ChangeAnimation("Idle_Sword & Shield_Dungeon_7");
			});
		PlayerRenderer->SetAnimationEvent("Attack_Sword & Shield_Dungeon_8", 79, [this]()
			{
				PlayerRenderer->ChangeAnimation("Idle_Sword & Shield_Dungeon_8");
			});
		PlayerRenderer->SetAnimationEvent("Attack_Sword & Shield_Dungeon_9", 95, [this]()
			{
				PlayerRenderer->ChangeAnimation("Idle_Sword & Shield_Dungeon_9");
			});
		PlayerRenderer->SetAnimationEvent("Attack_Sword & Shield_Dungeon_6", 111, [this]()
			{
				PlayerRenderer->ChangeAnimation("Idle_Sword & Shield_Dungeon_6");
			});
		PlayerRenderer->SetAnimationEvent("Attack_Sword & Shield_Dungeon_3", 127, [this]()
			{
				PlayerRenderer->ChangeAnimation("Idle_Sword & Shield_Dungeon_3");
			});

		PlayerRenderer->CreateAnimation("Die_Sword & Shield_Dungeon_2", "Warrior in Light Armor with Sword & Shield_Die.png", 0, 20, 0.1f, false);
		PlayerRenderer->CreateAnimation("Die_Sword & Shield_Dungeon_1", "Warrior in Light Armor with Sword & Shield_Die.png", 21, 41, 0.1f, false);
		PlayerRenderer->CreateAnimation("Die_Sword & Shield_Dungeon_4", "Warrior in Light Armor with Sword & Shield_Die.png", 42, 62, 0.1f, false);
		PlayerRenderer->CreateAnimation("Die_Sword & Shield_Dungeon_7", "Warrior in Light Armor with Sword & Shield_Die.png", 63, 83, 0.1f, false);
		PlayerRenderer->CreateAnimation("Die_Sword & Shield_Dungeon_8", "Warrior in Light Armor with Sword & Shield_Die.png", 84, 104, 0.1f, false);
		PlayerRenderer->CreateAnimation("Die_Sword & Shield_Dungeon_9", "Warrior in Light Armor with Sword & Shield_Die.png", 105, 125, 0.1f, false);
		PlayerRenderer->CreateAnimation("Die_Sword & Shield_Dungeon_6", "Warrior in Light Armor with Sword & Shield_Die.png", 126, 146, 0.1f, false);
		PlayerRenderer->CreateAnimation("Die_Sword & Shield_Dungeon_3", "Warrior in Light Armor with Sword & Shield_Die.png", 147, 167, 0.1f, false);

		PlayerRenderer->CreateAnimation("Hit_Sword & Shield_Dungeon_2", "Warrior in Light Armor with Sword & Shield_Hit.png", 0, 5, 0.1f, false);
		PlayerRenderer->CreateAnimation("Hit_Sword & Shield_Dungeon_1", "Warrior in Light Armor with Sword & Shield_Hit.png", 6, 11, 0.1f, false);
		PlayerRenderer->CreateAnimation("Hit_Sword & Shield_Dungeon_4", "Warrior in Light Armor with Sword & Shield_Hit.png", 12, 17, 0.1f, false);
		PlayerRenderer->CreateAnimation("Hit_Sword & Shield_Dungeon_7", "Warrior in Light Armor with Sword & Shield_Hit.png", 18, 23, 0.1f, false);
		PlayerRenderer->CreateAnimation("Hit_Sword & Shield_Dungeon_8", "Warrior in Light Armor with Sword & Shield_Hit.png", 24, 29, 0.1f, false);
		PlayerRenderer->CreateAnimation("Hit_Sword & Shield_Dungeon_9", "Warrior in Light Armor with Sword & Shield_Hit.png", 30, 35, 0.1f, false);
		PlayerRenderer->CreateAnimation("Hit_Sword & Shield_Dungeon_6", "Warrior in Light Armor with Sword & Shield_Hit.png", 36, 41, 0.1f, false);
		PlayerRenderer->CreateAnimation("Hit_Sword & Shield_Dungeon_3", "Warrior in Light Armor with Sword & Shield_Hit.png", 42, 47, 0.1f, false);

		PlayerRenderer->SetAnimationEvent("Hit_Sword & Shield_Dungeon_2", 5, [this]()
			{
				PlayerRenderer->ChangeAnimation("Idle_Sword & Shield_Dungeon_2");
			});
		PlayerRenderer->SetAnimationEvent("Hit_Sword & Shield_Dungeon_1", 11, [this]()
			{
				PlayerRenderer->ChangeAnimation("Idle_Sword & Shield_Dungeon_1");
			});
		PlayerRenderer->SetAnimationEvent("Hit_Sword & Shield_Dungeon_4", 17, [this]()
			{
				PlayerRenderer->ChangeAnimation("Idle_Sword & Shield_Dungeon_4");
			});
		PlayerRenderer->SetAnimationEvent("Hit_Sword & Shield_Dungeon_7", 23, [this]()
			{
				PlayerRenderer->ChangeAnimation("Idle_Sword & Shield_Dungeon_7");
			});
		PlayerRenderer->SetAnimationEvent("Hit_Sword & Shield_Dungeon_8", 29, [this]()
			{
				PlayerRenderer->ChangeAnimation("Idle_Sword & Shield_Dungeon_8");
			});
		PlayerRenderer->SetAnimationEvent("Hit_Sword & Shield_Dungeon_9", 35, [this]()
			{
				PlayerRenderer->ChangeAnimation("Idle_Sword & Shield_Dungeon_9");
			});
		PlayerRenderer->SetAnimationEvent("Hit_Sword & Shield_Dungeon_6", 41, [this]()
			{
				PlayerRenderer->ChangeAnimation("Idle_Sword & Shield_Dungeon_6");
			});
		PlayerRenderer->SetAnimationEvent("Hit_Sword & Shield_Dungeon_3", 47, [this]()
			{
				PlayerRenderer->ChangeAnimation("Idle_Sword & Shield_Dungeon_3");
			});

		PlayerRenderer->CreateAnimation("Idle_Sword & Shield_Dungeon_2", "Warrior in Light Armor with Sword & Shield_Idle_Dungeon.png", 0, 9, 0.1f);
		PlayerRenderer->CreateAnimation("Idle_Sword & Shield_Dungeon_1", "Warrior in Light Armor with Sword & Shield_Idle_Dungeon.png", 10, 19, 0.1f);
		PlayerRenderer->CreateAnimation("Idle_Sword & Shield_Dungeon_4", "Warrior in Light Armor with Sword & Shield_Idle_Dungeon.png", 20, 29, 0.1f);
		PlayerRenderer->CreateAnimation("Idle_Sword & Shield_Dungeon_7", "Warrior in Light Armor with Sword & Shield_Idle_Dungeon.png", 30, 39, 0.1f);
		PlayerRenderer->CreateAnimation("Idle_Sword & Shield_Dungeon_8", "Warrior in Light Armor with Sword & Shield_Idle_Dungeon.png", 40, 49, 0.1f);
		PlayerRenderer->CreateAnimation("Idle_Sword & Shield_Dungeon_9", "Warrior in Light Armor with Sword & Shield_Idle_Dungeon.png", 50, 59, 0.1f);
		PlayerRenderer->CreateAnimation("Idle_Sword & Shield_Dungeon_6", "Warrior in Light Armor with Sword & Shield_Idle_Dungeon.png", 60, 69, 0.1f);
		PlayerRenderer->CreateAnimation("Idle_Sword & Shield_Dungeon_3", "Warrior in Light Armor with Sword & Shield_Idle_Dungeon.png", 70, 79, 0.1f);

		PlayerRenderer->CreateAnimation("Idle_Sword & Shield_Town_2", "Warrior in Light Armor with Sword & Shield_Idle_Town.png", 0, 19, 0.1f);
		PlayerRenderer->CreateAnimation("Idle_Sword & Shield_Town_1", "Warrior in Light Armor with Sword & Shield_Idle_Town.png", 20, 39, 0.1f);
		PlayerRenderer->CreateAnimation("Idle_Sword & Shield_Town_4", "Warrior in Light Armor with Sword & Shield_Idle_Town.png", 40, 59, 0.1f);
		PlayerRenderer->CreateAnimation("Idle_Sword & Shield_Town_7", "Warrior in Light Armor with Sword & Shield_Idle_Town.png", 60, 79, 0.1f);
		PlayerRenderer->CreateAnimation("Idle_Sword & Shield_Town_8", "Warrior in Light Armor with Sword & Shield_Idle_Town.png", 80, 99, 0.1f);
		PlayerRenderer->CreateAnimation("Idle_Sword & Shield_Town_9", "Warrior in Light Armor with Sword & Shield_Idle_Town.png", 100, 119, 0.1f);
		PlayerRenderer->CreateAnimation("Idle_Sword & Shield_Town_6", "Warrior in Light Armor with Sword & Shield_Idle_Town.png", 120, 139, 0.1f);
		PlayerRenderer->CreateAnimation("Idle_Sword & Shield_Town_3", "Warrior in Light Armor with Sword & Shield_Idle_Town.png", 140, 159, 0.1f);

		PlayerRenderer->CreateAnimation("Walk_Sword & Shield_Dungeon_2", "Warrior in Light Armor with Sword & Shield_Walk_Dungeon.png", 0, 7, 0.1f);
		PlayerRenderer->CreateAnimation("Walk_Sword & Shield_Dungeon_1", "Warrior in Light Armor with Sword & Shield_Walk_Dungeon.png", 8, 15, 0.1f);
		PlayerRenderer->CreateAnimation("Walk_Sword & Shield_Dungeon_4", "Warrior in Light Armor with Sword & Shield_Walk_Dungeon.png", 16, 23, 0.1f);
		PlayerRenderer->CreateAnimation("Walk_Sword & Shield_Dungeon_7", "Warrior in Light Armor with Sword & Shield_Walk_Dungeon.png", 24, 31, 0.1f);
		PlayerRenderer->CreateAnimation("Walk_Sword & Shield_Dungeon_8", "Warrior in Light Armor with Sword & Shield_Walk_Dungeon.png", 32, 39, 0.1f);
		PlayerRenderer->CreateAnimation("Walk_Sword & Shield_Dungeon_9", "Warrior in Light Armor with Sword & Shield_Walk_Dungeon.png", 40, 47, 0.1f);
		PlayerRenderer->CreateAnimation("Walk_Sword & Shield_Dungeon_6", "Warrior in Light Armor with Sword & Shield_Walk_Dungeon.png", 48, 55, 0.1f);
		PlayerRenderer->CreateAnimation("Walk_Sword & Shield_Dungeon_3", "Warrior in Light Armor with Sword & Shield_Walk_Dungeon.png", 56, 63, 0.1f);
	}
	
	// Weaponless
	{
		PlayerRenderer->CreateAnimation("Idle_Weaponless_Town_2", "Warrior in Heavy Armor (Weaponless)_Idle_Town.png", 0, 19, 0.1f);
		PlayerRenderer->CreateAnimation("Idle_Weaponless_Town_1", "Warrior in Heavy Armor (Weaponless)_Idle_Town.png", 20, 39, 0.1f);
		PlayerRenderer->CreateAnimation("Idle_Weaponless_Town_4", "Warrior in Heavy Armor (Weaponless)_Idle_Town.png", 40, 59, 0.1f);
		PlayerRenderer->CreateAnimation("Idle_Weaponless_Town_7", "Warrior in Heavy Armor (Weaponless)_Idle_Town.png", 60, 79, 0.1f);
		PlayerRenderer->CreateAnimation("Idle_Weaponless_Town_8", "Warrior in Heavy Armor (Weaponless)_Idle_Town.png", 80, 99, 0.1f);
		PlayerRenderer->CreateAnimation("Idle_Weaponless_Town_9", "Warrior in Heavy Armor (Weaponless)_Idle_Town.png", 100, 119, 0.1f);
		PlayerRenderer->CreateAnimation("Idle_Weaponless_Town_6", "Warrior in Heavy Armor (Weaponless)_Idle_Town.png", 120, 139, 0.1f);
		PlayerRenderer->CreateAnimation("Idle_Weaponless_Town_3", "Warrior in Heavy Armor (Weaponless)_Idle_Town.png", 140, 159, 0.1f);

		PlayerRenderer->CreateAnimation("Walk_Weaponless_Town_2", "Warrior in Heavy Armor (Weaponless)_Walk_Town.png", 0, 7, 0.1f);
		PlayerRenderer->CreateAnimation("Walk_Weaponless_Town_1", "Warrior in Heavy Armor (Weaponless)_Walk_Town.png", 8, 15, 0.1f);
		PlayerRenderer->CreateAnimation("Walk_Weaponless_Town_4", "Warrior in Heavy Armor (Weaponless)_Walk_Town.png", 16, 23, 0.1f);
		PlayerRenderer->CreateAnimation("Walk_Weaponless_Town_7", "Warrior in Heavy Armor (Weaponless)_Walk_Town.png", 24, 31, 0.1f);
		PlayerRenderer->CreateAnimation("Walk_Weaponless_Town_8", "Warrior in Heavy Armor (Weaponless)_Walk_Town.png", 32, 39, 0.1f);
		PlayerRenderer->CreateAnimation("Walk_Weaponless_Town_9", "Warrior in Heavy Armor (Weaponless)_Walk_Town.png", 40, 47, 0.1f);
		PlayerRenderer->CreateAnimation("Walk_Weaponless_Town_6", "Warrior in Heavy Armor (Weaponless)_Walk_Town.png", 48, 55, 0.1f);
		PlayerRenderer->CreateAnimation("Walk_Weaponless_Town_3", "Warrior in Heavy Armor (Weaponless)_Walk_Town.png", 56, 63, 0.1f);
	}

	PlayerRenderer->ChangeAnimation("Idle_Sword & Shield_Dungeon_2");
	SetActorLocation({ 300.0f, 0.0f, 0.0f });
	//PlayerRenderer->AddRelativeLocation({ 0.0f,0.0f, 100.f });
	Collision = CreateDefaultSubObject<UCollision>();
	Collision->SetupAttachment(RootComponent);
	Collision->SetCollisionProfileName("Player");
	Collision->SetScale3D({ 50.0f, 50.0f, 50.0f});


	//GetWorld()->GetMainCamera()->AttachToActor(this);


	//Collision->SetCollisionEnter([](UCollision* _This, UCollision* _Other)
	//	{
	//		_Other->GetActor()->Destroy();
	//		// _Other->Destroy();
	//		UEngineDebug::OutPutString("Enter");
	//	});

	//Collision->SetCollisionStay([](UCollision* _This, UCollision* _Other)
	//	{
	//		UEngineDebug::OutPutString("Stay");
	//	});

	//Collision->SetCollisionEnd([](UCollision* _This, UCollision* _Other)
	//	{
	//		UEngineDebug::OutPutString("End");
	//	});

	// 부모가 존재하지 않는 root는 Relative든 Local이던 
	// 결과는 같다. 
	// 부모의 크기에 내가 영향을 받을수 있기 대문에 함수가 나뉜것이다.
	// 부모가 없으면

	//Renderer = CreateDefaultSubObject<MyCustomRenderer>();
	//Renderer->SetupAttachment(RootComponent);
	//Renderer->SetRelativeScale3D({ 100.0f, 100.0f, 1.0f });

	//PlayerRenderer->SetRelativeScale3D({ 50, 50, 1.0f });
	


	//Child = CreateDefaultSubObject<USpriteRenderer>();
	//Child->SetSprite("Player.png", 2);
	//// 부모의 스케일이 나에게 영향을 주면서 나는 100이 아닐수가 있다
	//Child->SetRelativeLocation({100.0f, 0.0f, 0.0f});
	//Child->SetScale3D({ 50.0f, 50.0f, 1.0f });
	//// Child->SetScale3D({ 50.0f, 50.0f, 1.0f });
	//Child->SetupAttachment(RootComponent);

		// 인벤토리
	//TimeEventComponent = CreateDefaultSubObject<UTimeEventComponent>();

	//TimeEventComponent->AddEvent(2.0f,
	//	[](float _Delta, float _Acc)
	//	{
	//		UEngineDebug::OutPutString("Update" + std::to_string(_Acc));
	//	},
	//	[]()
	//	{
	//		UEngineDebug::OutPutString("Test");
	//	}, true
	//);

	///*TimeEventComponent->AddEndEvent(2.0f, []()
	//	{
	//		UEngineDebug::OutPutString("Test");
	//	}, true
	//);*/

	//LogoRenderer = CreateDefaultSubObject<USpriteRenderer>();

	//{
	//	UEngineDirectory Dir;
	//	if (false == Dir.MoveParentToDirectory("ContentsResources"))
	//	{
	//		MSGASSERT("리소스 폴더를 찾지 못했습니다.");
	//		return;
	//	}
	//	Dir.Append("Image");
	//	UEngineFile ImageFiles = Dir.GetFile("BackGround.png");

	//	// 편한 인터페이스로 안됩니다.
	//	ColImage.Load(nullptr, ImageFiles.GetPathToString());
	//}

	//UColor Color = ColImage.GetColor(FIntPoint{ 3, 3 }, UColor(255, 255, 255, 255));

	//int a = 0;

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
	
	//std::vector<UCollision*> Result;
	//
	//Collision->CollisionCheck("Monster", Result);

	//if (공격 상태일때만)
//{
//	std::vector<UCollision*> Result;
//	if (true == Collision->CollisionCheck("Monster", Result))
//	{
//		Result[0]->GetActor()->Destroy();
//	}
//}
	
	if (UEngineInput::IsDown(VK_LBUTTON) && !UEngineInput::IsPress(VK_LSHIFT))
	{
		Direction();
		
		float WindowSizehX = UEngineCore::GetScreenScale().hX();
		float WindowSizehY = UEngineCore::GetScreenScale().hY();

		if (-WindowSizehX > MousePos.X)
		{
			return;
		}
		if (WindowSizehX < MousePos.X)
		{
			return;
		}
		if (-WindowSizehY > MousePos.Y)
		{
			return;
		}
		if (WindowSizehY < MousePos.Y)
		{
			return;
		}
		
		
		Distance = (MousePos - PlayerRenderer->GetTransformRef().WorldLocation).Length();

		Move = true;
	}

	if (UEngineInput::IsDown(VK_LBUTTON) && UEngineInput::IsPress(VK_LSHIFT))
	{
		Direction();
		Distance = 0.0f;
		Move = false;
		State = "Attack_";
		Pos = "Dungeon_";
		PlayerRenderer->ChangeAnimation(State + Equipment + Pos + Dir);
	}

	PlayerMove(_DeltaTime);
	

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

	if (UEngineInput::IsDown('F'))
	{
		GetWorld()->GetCamera(EEngineCameraType::UICamera)->SetActiveSwitch();
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
	std::shared_ptr<class ACameraActor> Camera = GetWorld()->GetCamera(0);
	MousePos = Camera->ScreenMousePosToWorldPos();
	MouseDir = MousePos - PlayerRenderer->GetTransformRef().WorldLocation;


	UEngineDebug::OutPutString(MousePos.ToString());
	//UEngineDebug::OutPutString(std::to_string(MousePos.X));
	//UEngineDebug::OutPutString(std::to_string(MousePos.Y));
	UEngineDebug::OutPutString(std::to_string(AngleDeg));

	//Distance = MouseDir.Length();
	MouseDir.Normalize();

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

	//PlayerRenderer->ChangeAnimation(Idle + Dir);
}

void APlayer::PlayerMove(float _DeltaTime)
{
	if (true == Move)
	{
		State = "Walk_";
		PlayerRenderer->ChangeAnimation(State + Equipment + Pos + Dir);

		if (0.0f >= Distance)
		{
			Move = false;
			State = "Idle_";
			PlayerRenderer->ChangeAnimation(State + Equipment + Pos + Dir);
		}

		Distance -= (MouseDir * Speed * _DeltaTime).Length();
		AddRelativeLocation(MouseDir * Speed * _DeltaTime);
		//UEngineDebug::OutPutString(std::to_string(Distance));
	}
}
