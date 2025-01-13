#include "PreCompile.h"
#include "TitleGameMode.h"
#include "TitleLogo.h"
#include "Player.h"
#include "Zombie.h"
#include "Skeleton_Sword.h"
#include "Skeleton_Axe.h"
#include "Skeleton_Bow.h"
#include "Skeleton_King.h"
#include "Scavenger.h"
#include "Hidden.h"
#include "Fallen_Spear.h"
#include "Fallen_Sword.h"
#include "Butcher.h"
#include <EngineCore/CameraActor.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>
#include <EngineCore/EngineCamera.h>
#include "ContentsEditorGUI.h"

class TestWindow : public UEngineGUIWindow
{
public:
	void OnGUI() override
	{
		if (true == ImGui::Button("WindowButton"))
		{
			std::shared_ptr<AZombie> NewZombie = GetWorld()->SpawnActor<AZombie>();
			NewZombie->SetActorLocation({ 300.0f, 200.0f, 0.0f });
		}

		if (true == ImGui::Button("Idle"))
		{
				TitleGameMode->Zombie->GetRenderer()->ChangeAnimation("Idle_2");
				TitleGameMode->Skeleton_Sword->GetRenderer()->ChangeAnimation("Idle_2");
				TitleGameMode->Skeleton_Bow->GetRenderer()->ChangeAnimation("Idle_2");
				TitleGameMode->Skeleton_Axe->GetRenderer()->ChangeAnimation("Idle_2");
				TitleGameMode->Skeleton_King->GetRenderer()->ChangeAnimation("Idle_2");
				TitleGameMode->Scavenger->GetRenderer()->ChangeAnimation("Idle_2");
				TitleGameMode->Hidden->GetRenderer()->ChangeAnimation("Idle_2");
				TitleGameMode->Fallen_Sword->GetRenderer()->ChangeAnimation("Idle_2");
				TitleGameMode->Fallen_Spear->GetRenderer()->ChangeAnimation("Idle_2");
				TitleGameMode->Butcher->GetRenderer()->ChangeAnimation("Idle_2");
		}

		if (true == ImGui::Button("Attack"))
		{
			TitleGameMode->Zombie->GetRenderer()->ChangeAnimation("Attack_2");
			TitleGameMode->Skeleton_Sword->GetRenderer()->ChangeAnimation("Attack_2");
			TitleGameMode->Skeleton_Bow->GetRenderer()->ChangeAnimation("Attack_2");
			TitleGameMode->Skeleton_Axe->GetRenderer()->ChangeAnimation("Attack_2");
			TitleGameMode->Skeleton_King->GetRenderer()->ChangeAnimation("Attack_2");
			TitleGameMode->Scavenger->GetRenderer()->ChangeAnimation("Attack_2");
			TitleGameMode->Hidden->GetRenderer()->ChangeAnimation("Attack_2");
			TitleGameMode->Fallen_Sword->GetRenderer()->ChangeAnimation("Attack_2");
			TitleGameMode->Fallen_Spear->GetRenderer()->ChangeAnimation("Attack_2");
			TitleGameMode->Butcher->GetRenderer()->ChangeAnimation("Attack_2");
		}

		if (true == ImGui::Button("Die"))
		{
			TitleGameMode->Zombie->GetRenderer()->ChangeAnimation("Die_2");
			TitleGameMode->Skeleton_Sword->GetRenderer()->ChangeAnimation("Die_2");
			TitleGameMode->Skeleton_Bow->GetRenderer()->ChangeAnimation("Die_2");
			TitleGameMode->Skeleton_Axe->GetRenderer()->ChangeAnimation("Die_2");
			TitleGameMode->Skeleton_King->GetRenderer()->ChangeAnimation("Die_2");
			TitleGameMode->Scavenger->GetRenderer()->ChangeAnimation("Die_2");
			TitleGameMode->Hidden->GetRenderer()->ChangeAnimation("Die_2");
			TitleGameMode->Fallen_Sword->GetRenderer()->ChangeAnimation("Die_2");
			TitleGameMode->Fallen_Spear->GetRenderer()->ChangeAnimation("Die_2");
			TitleGameMode->Butcher->GetRenderer()->ChangeAnimation("Die_2");
		}

		if (true == ImGui::Button("Special"))
		{
			TitleGameMode->Skeleton_Bow->GetRenderer()->ChangeAnimation("Special_2");
			TitleGameMode->Skeleton_Axe->GetRenderer()->ChangeAnimation("Special_2");
			TitleGameMode->Skeleton_King->GetRenderer()->ChangeAnimation("Special_2");
			TitleGameMode->Scavenger->GetRenderer()->ChangeAnimation("Special_2");
			TitleGameMode->Hidden->GetRenderer()->ChangeAnimation("Special_2");
			TitleGameMode->Fallen_Sword->GetRenderer()->ChangeAnimation("Special_2");
			TitleGameMode->Fallen_Spear->GetRenderer()->ChangeAnimation("Special_2");
		}

		if (true == ImGui::Button("Walk"))
		{
			TitleGameMode->Zombie->GetRenderer()->ChangeAnimation("Walk_2");;
			TitleGameMode->Skeleton_Sword->GetRenderer()->ChangeAnimation("Walk_2");;
			TitleGameMode->Skeleton_Bow->GetRenderer()->ChangeAnimation("Walk_2");;
			TitleGameMode->Skeleton_Axe->GetRenderer()->ChangeAnimation("Walk_2");;
			TitleGameMode->Skeleton_King->GetRenderer()->ChangeAnimation("Walk_2");;
			TitleGameMode->Scavenger->GetRenderer()->ChangeAnimation("Walk_2");;
			TitleGameMode->Hidden->GetRenderer()->ChangeAnimation("Walk_2");;
			TitleGameMode->Fallen_Sword->GetRenderer()->ChangeAnimation("Walk_2");;
			TitleGameMode->Fallen_Spear->GetRenderer()->ChangeAnimation("Walk_2");;
			TitleGameMode->Butcher->GetRenderer()->ChangeAnimation("Walk_2");
		}

		if (true == ImGui::Button("Hit"))
		{
			TitleGameMode->Zombie->GetRenderer()->ChangeAnimation("Hit_2");;
			TitleGameMode->Skeleton_Sword->GetRenderer()->ChangeAnimation("Hit_2");;
			TitleGameMode->Skeleton_Bow->GetRenderer()->ChangeAnimation("Hit_2");;
			TitleGameMode->Skeleton_Axe->GetRenderer()->ChangeAnimation("Hit_2");;
			TitleGameMode->Skeleton_King->GetRenderer()->ChangeAnimation("Hit_2");;
			TitleGameMode->Scavenger->GetRenderer()->ChangeAnimation("Hit_2");;
			TitleGameMode->Hidden->GetRenderer()->ChangeAnimation("Hit_2");;
			TitleGameMode->Fallen_Sword->GetRenderer()->ChangeAnimation("Hit_2");;
			TitleGameMode->Fallen_Spear->GetRenderer()->ChangeAnimation("Hit_2");;
			TitleGameMode->Butcher->GetRenderer()->ChangeAnimation("Hit_2");
		}

		if (true == ImGui::Button("FreeCameraOn"))
		{
			GetWorld()->GetMainCamera()->FreeCameraSwitch();
		}

		ImGui::SameLine(); // 한간 띄기
		ImGui::Text("test");
	}

	void SetGameMode(ATitleGameMode* _GameMode)
	{
		TitleGameMode = _GameMode;
	}

private :
	ATitleGameMode* TitleGameMode = nullptr;
};

ATitleGameMode::ATitleGameMode()
{

	GetWorld()->CreateCollisionProfile("Monster");
	GetWorld()->CreateCollisionProfile("Player");

	GetWorld()->LinkCollisionProfile("Player", "Monster");
	
	// 카메라를 일정거리 뒤로 가서 
	// 카메라 위치조정을 무조건 해줘야 할것이다.
	std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -1000.0f, 1.0f });
	//Camera->GetCameraComponent()->SetZSort(0, true);
	
	{
		Player = GetWorld()->SpawnActor<APlayer>();
		Player->SetActorLocation({ 300.0f, 0.0f, 0.0f });
		//Player->GetRenderer()->SetSpriteData(4);
	}

	{
		Zombie = GetWorld()->SpawnActor<AZombie>();
		Zombie->SetActorLocation({ 250.0f, 0.0f, 0.0f });
	}
	
	{
		Skeleton_Sword = GetWorld()->SpawnActor<ASkeleton_Sword>();
		Skeleton_Sword->SetActorLocation({ 350.0f, 0.0f, 0.0f });
	}
	
	{
		Skeleton_Bow = GetWorld()->SpawnActor<ASkeleton_Bow>();
		Skeleton_Bow->SetActorLocation({ 150.0f, 0.0f, 0.0f });
	}
	
	{
		Skeleton_Axe = GetWorld()->SpawnActor<ASkeleton_Axe>();
		Skeleton_Axe->SetActorLocation({ 100.0f, 0.0f, 0.0f });
	}
	
	{
		Skeleton_King = GetWorld()->SpawnActor<ASkeleton_King>();
		Skeleton_King->SetActorLocation({ 50.0f, 0.0f, 0.0f });
	}
	
	{
		Scavenger = GetWorld()->SpawnActor<AScavenger>();
		Scavenger->SetActorLocation({ 0.0f, 0.0f, 0.0f });
	}
	
	{
		Hidden = GetWorld()->SpawnActor<AHidden>();
		Hidden->SetActorLocation({ 400.0f, 0.0f, 0.0f });
	}
	
	{
		Fallen_Sword = GetWorld()->SpawnActor<AFallen_Sword>();
		Fallen_Sword->SetActorLocation({ 450.0f, 0.0f, 0.0f });
	}
	
	{
		Fallen_Spear = GetWorld()->SpawnActor<AFallen_Spear>();
		Fallen_Spear->SetActorLocation({ -50.0f, 0.0f, 0.0f });
	}
	
	{
		Butcher = GetWorld()->SpawnActor<AButcher>();
		Butcher->SetActorLocation({ -100.0f, 0.0f, 0.0f });
	}


	//UEngineGUI::CreateGUIWindow<TestWindow>("TestWindow");
}

ATitleGameMode::~ATitleGameMode()
{

}

void ATitleGameMode::Tick(float _DeltaTime)
{
	// 부모 호출
	AActor::Tick(_DeltaTime);

	//if (nullptr == Logo && true == Logo->IsDestroy())
	//{
	//	Logo = nullptr;
	//}
}

void ATitleGameMode::LevelChangeStart()
{
	UEngineGUI::AllWindowOff();

	{
		std::shared_ptr<UContentsEditorGUI> Window = UEngineGUI::FindGUIWindow<UContentsEditorGUI>("ContentsEditorGUI");

		if (nullptr == Window)
		{
			Window = UEngineGUI::CreateGUIWindow<UContentsEditorGUI>("ContentsEditorGUI");
		}

		Window->SetActive(true);
	}

	{
		std::shared_ptr<TestWindow> Window = UEngineGUI::FindGUIWindow<TestWindow>("TestWindow");

		if (nullptr == Window)
		{
			Window = UEngineGUI::CreateGUIWindow<TestWindow>("TestWindow");
		}

		Window->SetGameMode(this);
		Window->SetActive(true);
	}
}