#include "PreCompile.h"
#include "ContentsCore.h"
#include "Player.h"
#include <EngineCore/Level.h>
#include <EngineCore/EngineTexture.h>
#include <EngineCore/EngineSprite.h>
#include <EngineCore/EngineShader.h>
#include <EngineCore/EngineMaterial.h>
#include "TitleGameMode.h"
#include "TileMapEditor.h"
#include <EngineCore/HUD.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/EngineGUIWindow.h>
#include "ContentsEditorGUI.h"


// #define�� �׳� ������ ����
CreateContentsCoreDefine(UContentsCore);

UContentsCore::UContentsCore()
{
}

UContentsCore::~UContentsCore()
{
}


void UContentsCore::EngineStart(UEngineInitData& _Data)
{
	// mainwindow�� �ƹ��� �ǵ�� �ȵȴ�.
	// �� �������ݾ� ������ �����ϴ� �������°� �����ϴ����� ������Ѵ�.

	_Data.WindowPos = { 100, 100 };
	_Data.WindowSize = { 1280, 720 };

	MyGSetting();

	{
		UEngineDirectory Dir;
		if (false == Dir.MoveParentToDirectory("ContentsResources"))
		{
			MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
			return;
		}
		Dir.Append("Image");
		std::vector<UEngineFile> ImageFiles = Dir.GetAllFile(true, { ".PNG", ".BMP", ".JPG" });
		for (size_t i = 0; i < ImageFiles.size(); i++)
		{
			std::string FilePath = ImageFiles[i].GetPathToString();
			UEngineTexture::Load(FilePath);
		}
	}

	//{
	//	UEngineDirectory Dir;
	//	if (false == Dir.MoveParentToDirectory("ContentsResources"))
	//	{
	//		MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
	//		return;
	//	}
	//	Dir.Append("Image/Tevi");
	//
	//	UEngineSprite::CreateSpriteToFolder(Dir.GetPathToString());
	//}


	UEngineSprite::CreateSpriteToMeta("Warrior in Heavy Armor (Weaponless)_Idle_Town.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Warrior in Heavy Armor (Weaponless)_Walk_Town.png", ".sdata");

	UEngineSprite::CreateSpriteToMeta("Warrior in Light Armor with Sword & Shield_Walk_Town.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Warrior in Light Armor with Sword & Shield_Attack.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Warrior in Light Armor with Sword & Shield_Die.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Warrior in Light Armor with Sword & Shield_Hit.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Warrior in Light Armor with Sword & Shield_Idle_Dungeon.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Warrior in Light Armor with Sword & Shield_Idle_Town.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Warrior in Light Armor with Sword & Shield_Walk_Dungeon.png", ".sdata");
	
	UEngineSprite::CreateSpriteToMeta("Butcher_Attack.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Butcher_Die.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Butcher_Hit.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Butcher_Idle.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Butcher_Walk.png", ".sdata");

	UEngineSprite::CreateSpriteToMeta("Scavenger_Attack.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Scavenger_Die.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Scavenger_Hit.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Scavenger_Idle.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Scavenger_Special.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Scavenger_Walk.png", ".sdata");

	UEngineSprite::CreateSpriteToMeta("Skeleton King_Attack.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Skeleton King_Die.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Skeleton King_Hit.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Skeleton King_Idle.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Skeleton King_Special.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Skeleton King_Walk.png", ".sdata");

	UEngineSprite::CreateSpriteToMeta("Skeleton with Bow_Attack.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Skeleton with Bow_Die.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Skeleton with Bow_Hit.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Skeleton with Bow_Idle.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Skeleton with Bow_Special.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Skeleton with Bow_Walk.png", ".sdata");

	UEngineSprite::CreateSpriteToMeta("Skeleton with Sword & Shield_Attack.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Skeleton with Sword & Shield_Die.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Skeleton with Sword & Shield_Hit.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Skeleton with Sword & Shield_Idle.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Skeleton with Sword & Shield_Walk.png", ".sdata");

	UEngineSprite::CreateSpriteToMeta("Skeleton with Two Axes_Attack.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Skeleton with Two Axes_Die.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Skeleton with Two Axes_Hit.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Skeleton with Two Axes_Idle.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Skeleton with Two Axes_Special.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Skeleton with Two Axes_Walk.png", ".sdata");

	UEngineSprite::CreateSpriteToMeta("Zombie_Attack.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Zombie_Die.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Zombie_Hit.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Zombie_Idle.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Zombie_Walk.png", ".sdata");

	UEngineSprite::CreateSpriteToMeta("Fallen One with Sword_Attack.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Fallen One with Sword_Die.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Fallen One with Sword_Hit.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Fallen One with Sword_Idle.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Fallen One with Sword_Special.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Fallen One with Sword_Walk.png", ".sdata");

	UEngineSprite::CreateSpriteToMeta("Fallen Ones with Spear_Attack.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Fallen Ones with Spear_Die.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Fallen Ones with Spear_Hit.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Fallen Ones with Spear_Idle.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Fallen Ones with Spear_Special.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Fallen Ones with Spear_Walk.png", ".sdata");

	UEngineSprite::CreateSpriteToMeta("Hidden_Attack.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Hidden_Die.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Hidden_Hit.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Hidden_Idle.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Hidden_Special.png", ".sdata");
	UEngineSprite::CreateSpriteToMeta("Hidden_Walk.png", ".sdata");

	UEngineSprite::CreateSpriteToMeta("Church Dungeon.png", ".sdata");
	
	// ���ΰ� APawn ��� ��������.
	UEngineCore::CreateLevel<ATitleGameMode, APlayer, AHUD>("Titlelevel");
	UEngineCore::CreateLevel<ATileMapEditor, APawn, AHUD>("TileMapEditor");
	UEngineCore::OpenLevel("Titlelevel");

	UEngineGUI::AllWindowOff();

	UEngineGUI::CreateGUIWindow<UContentsEditorGUI>("ContentsEditorGUI");
	std::shared_ptr<UContentsEditorGUI> Window = UEngineGUI::FindGUIWindow<UContentsEditorGUI>("ContentsEditorGUI");
	Window->SetActive(true);
}

void UContentsCore::EngineTick(float _DeltaTime)
{

}

void UContentsCore::EngineEnd()
{

}