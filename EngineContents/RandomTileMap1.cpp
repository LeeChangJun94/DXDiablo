#include "PreCompile.h"
#include "RandomTileMap1.h"
#include "Zombie.h"
#include "Hidden.h"
#include <EngineBase/EngineRandom.h>
#include <EngineCore/CameraActor.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/TileMapRenderer.h>
#include <EngineCore/EngineGUIWindow.h>
#include <EngineCore/EngineGUI.h>
#include <EngineCore/imgui.h>
#include <EngineCore/EngineCamera.h>
#include "ContentsEditorGUI.h"
#include <EnginePlatform/EngineInput.h>
#include "queue"


enum class EEditMode
{
	TileMap,
	Object,
};

enum class ESpawnList
{
	Zombie,
	Hidden,
};

class UTileMapWindow : public UEngineGUIWindow
{
public:
	int SelectItem = 0;
	int ObjectItem = -1;
	UTileMapRenderer* TileMapRenderer = nullptr;
	UEngineRandom Random;
	EEditMode Mode = EEditMode::TileMap;

	//std::list<std::shared_ptr<AMonster>> AllMonsterList;

	int TileCountX = 40;
	int TileCountY = 40;
	int SelectTileIndex = 0;
	int MinRoomSize = 4;
	int MaxSplits = 8;
	int maxDungeonGenerations = 50;

	void TileMapMode()
	{
		{
			UEngineSprite* Sprite = TileMapRenderer->GetSprite();

			for (size_t i = 0; i < Sprite->GetSpriteCount(); i++)
			{
				UEngineTexture* Texture = Sprite->GetTexture(i);
				FSpriteData Data = Sprite->GetSpriteData(i);

				//SRV�Դϴ�
				ImTextureID SRV = reinterpret_cast<ImTextureID>(Texture->GetSRV());

				std::string Text = std::to_string(i);

				if (i != 0)
				{
					if (0 != (i % 10))
					{
						ImGui::SameLine();
					}
				}


				ImVec2 Pos = { Data.CuttingPos.X, Data.CuttingPos.Y };
				ImVec2 Size = { Data.CuttingPos.X + Data.CuttingSize.X, Data.CuttingPos.Y + Data.CuttingSize.Y };

				if (ImGui::ImageButton(Text.c_str(), SRV, { 60, 60 }, Pos, Size))
				{
					SelectTileIndex = static_cast<int>(i);
				}
				// ���͸� ġ�� �ʴ°���.
			}

			ImGui::InputInt("TileMapX", &TileCountX);
			ImGui::InputInt("TileMapY", &TileCountY);

			if (ImGui::Button("TileMap Create"))
			{
				for (int y = 0; y < TileCountY; y++)
				{
					for (int x = 0; x < TileCountX; x++)
					{
						TileMapRenderer->SetTile(x, y, SelectTileIndex);
					}
				}
			}

			if (ImGui::Button("RandomMap Create"))
			{
				for (int i = 0; i < maxDungeonGenerations; ++i) {
					if (RandomTileGameMode->GenerateDungeon()) {
						//std::cout << "Dungeon generation succeeded on attempt: " << i + 1 << "\n";
						break;
					}
					//else {
					//	std::cout << "Dungeon generation failed on attempt: " << i + 1 << ", retrying...\n";
					//}
				}

				for (int y = 0; y < DUNGEON_HEIGHT; ++y)
				{
					for (int x = 0; x < DUNGEON_WIDTH; ++x)
					{
						if ('#' == static_cast<int>(RandomTileGameMode->DungeonMap[y][x]))
						{
							TileMapRenderer->SetTile(x, y, 0);
						}

						if ('.' == static_cast<int>(RandomTileGameMode->DungeonMap[y][x]))
						{
							TileMapRenderer->SetTile(x, y, 1);
						}

						if ('1' == static_cast<int>(RandomTileGameMode->DungeonMap[y][x]))
						{
							TileMapRenderer->SetTile(x, y, 2);
						}

						if ('2' == static_cast<int>(RandomTileGameMode->DungeonMap[y][x]))
						{
							TileMapRenderer->SetTile(x, y, 3);
						}
						//std::cout << RandomTileGameMode->dungeonMap[y][x];
					}
					//std::cout << "\n";
				}

				/*std::vector<std::vector<ETileType>> Map(HEIGHT, std::vector<ETileType>(WIDTH));
				GenerateDungeon(Map);

				for (int y = 0; y < HEIGHT; ++y)
				{
					for (int x = 0; x < WIDTH; ++x)
					{
						if (0 == static_cast<int>(Map[y][x]))
						{
							continue;
						}
					
						TileMapRenderer->SetTile(x, y, 1);
					}
				}*/
			}

			if (ImGui::Button("DrawHallways"))
			{
				RandomTileGameMode->DrawHallways();
			}

			if (ImGui::Button("TileRemove"))
			{
				for (int y = 0; y < DUNGEON_HEIGHT; ++y) {
					for (int x = 0; x < DUNGEON_WIDTH; ++x) {
						TileMapRenderer->RemoveTile(x, y);
					}
				}
			}

			if (true == UEngineInput::IsPress(VK_LBUTTON))
			{
				FVector ScreenPos = GetWorld()->GetMainCamera()->ScreenMousePosToWorldPos();

				TileMapRenderer->SetTile(ScreenPos, SelectTileIndex);
			}

			if (true == UEngineInput::IsPress(VK_RBUTTON))
			{
				FVector ScreenPos = GetWorld()->GetMainCamera()->ScreenMousePosToWorldPos();

				TileMapRenderer->RemoveTile(ScreenPos);
			}
		}
	}

	void ObjectMode()
	{
		{
			std::vector<const char*> Arr;
			Arr.push_back("Monster");
			Arr.push_back("Monster2");


			ImGui::ListBox("SpawnList", &SelectItem, &Arr[0], 2);

			// GetMainWindow()->IsScreenOut();


			if (true == UEngineInput::IsDown(VK_LBUTTON))
			{
				ESpawnList SelectMonster = static_cast<ESpawnList>(SelectItem);
				std::shared_ptr<class ACameraActor> Camera = GetWorld()->GetMainCamera();
				FVector Pos = Camera->ScreenMousePosToWorldPos();
				Pos.Z = 0.0f;

				std::shared_ptr<AMonster> NewMonster;

				switch (SelectMonster)
				{
				case ESpawnList::Zombie:
					NewMonster = GetWorld()->SpawnActor<AZombie>("Zombie");
					break;
				case ESpawnList::Hidden:
					NewMonster = GetWorld()->SpawnActor<AHidden>("Hidden");
					break;
				default:
					break;
				}

				NewMonster->SetActorLocation(Pos);
				//AllMonsterList.push_back(NewMonster);

			}
		}

		{
			if (ImGui::Button("EditObjectDelete"))
			{
				std::list<std::shared_ptr<AMonster>> AllMonsterList = GetWorld()->GetAllActorListByClass<AMonster>();
				for (std::shared_ptr<AMonster> Monster : AllMonsterList)
				{
					Monster->Destroy();
				}

			}
		}

		{
			std::vector<std::shared_ptr<AMonster>> AllMonsterList = GetWorld()->GetAllActorArrayByClass<AMonster>();
			std::vector<std::string> ArrString;
			for (std::shared_ptr<class AActor> Actor : AllMonsterList)
			{
				ArrString.push_back(Actor->GetName());
			}

			std::vector<const char*> Arr;
			for (size_t i = 0; i < ArrString.size(); i++)
			{
				Arr.push_back(ArrString[i].c_str());
			}


			if (0 < Arr.size())
			{
				ImGui::ListBox("AllActorList", &ObjectItem, &Arr[0], static_cast<int>(Arr.size()));

				// AllMonsterList[SelectItem]->Destroy();

				if (ObjectItem != -1)
				{
					// AllMonsterList[ObjectItem]->
				}

				if (true == ImGui::Button("Delete"))
				{
					AllMonsterList[ObjectItem]->Destroy();
					ObjectItem = -1;
				}

			}
		}

	}

	void SaveAndLoad()
	{
		if (true == ImGui::Button("Save"))
		{
			UEngineDirectory Dir;
			if (false == Dir.MoveParentToDirectory("ContentsResources"))
			{
				MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
				return;
			}
			Dir.Append("Data");
			std::string InitPath = Dir.GetPathToString();

			OPENFILENAME ofn;       // common dialog box structure
			char szFile[260] = { 0 };       // if using TCHAR macros
			// Initialize OPENFILENAME
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = nullptr;
			ofn.lpstrFile = szFile;
			ofn.nMaxFile = sizeof(szFile);
			ofn.lpstrFilter = ("All\0*.*\0");
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrDefExt = "MapData";
			ofn.lpstrInitialDir = InitPath.c_str();
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			if (GetSaveFileNameA(&ofn) == TRUE)
			{
				std::list<std::shared_ptr<AMonster>> AllMonsterList = GetWorld()->GetAllActorListByClass<AMonster>();

				UEngineSerializer Ser;

				Ser << static_cast<int>(AllMonsterList.size());

				for (std::shared_ptr<AMonster> Actor : AllMonsterList)
				{

					Ser << static_cast<int>(Actor->MonsterTypeValue);
					// ���� ����ȴٴ� �̾߱�
					Actor->Serialize(Ser);
				}

				TileMapRenderer->Serialize(Ser);

				UEngineFile NewFile = Dir.GetFile(ofn.lpstrFile);

				NewFile.FileOpen("wb");
				NewFile.Write(Ser);
			}
		}

		if (true == ImGui::Button("Load"))
		{
			UEngineDirectory Dir;
			if (false == Dir.MoveParentToDirectory("ContentsResources"))
			{
				MSGASSERT("���ҽ� ������ ã�� ���߽��ϴ�.");
				return;
			}
			Dir.Append("Data");
			std::string InitPath = Dir.GetPathToString();

			OPENFILENAME ofn;       // common dialog box structure
			char szFile[260] = { 0 };       // if using TCHAR macros
			// Initialize OPENFILENAME
			ZeroMemory(&ofn, sizeof(ofn));
			ofn.lStructSize = sizeof(ofn);
			ofn.hwndOwner = nullptr;
			ofn.lpstrFile = szFile;
			ofn.nMaxFile = sizeof(szFile);
			ofn.lpstrFilter = ("All\0*.*\0Text\0*.MapData\0");
			ofn.nFilterIndex = 1;
			ofn.lpstrFileTitle = NULL;
			ofn.nMaxFileTitle = 0;
			ofn.lpstrInitialDir = InitPath.c_str();
			ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

			if (GetOpenFileNameA(&ofn) == TRUE)
			{
				UEngineFile NewFile = Dir.GetFile(ofn.lpstrFile);
				UEngineSerializer Ser;

				NewFile.FileOpen("rb");
				NewFile.Read(Ser);


				int MonsterCount = 0;

				Ser >> MonsterCount;

				for (size_t i = 0; i < MonsterCount; i++)
				{
					int MonsterTypeValue = 0;
					Ser >> MonsterTypeValue;

					EMonsterType MonsterType = static_cast<EMonsterType>(MonsterTypeValue);

					std::shared_ptr<AMonster> NewMon = nullptr;

					switch (MonsterType)
					{
					case ZOMBIE:
						NewMon = GetWorld()->SpawnActor<AZombie>();
						break;
					case HIDDEN:
						NewMon = GetWorld()->SpawnActor<AHidden>();
						break;
					default:
						break;
					}

					NewMon->DeSerialize(Ser);
				}

				TileMapRenderer->DeSerialize(Ser);
			}
		}
	}

	void OnGUI() override
	{

		if (Mode == EEditMode::Object)
		{
			if (ImGui::Button("ObjectMode"))
			{
				Mode = EEditMode::TileMap;
			}
		}
		else
		{
			if (ImGui::Button("TileMapMode"))
			{
				Mode = EEditMode::Object;
			}
		}

		if (true == ImGui::Button("FreeCameraOn"))
		{
			GetWorld()->GetMainCamera()->FreeCameraSwitch();
		}

		switch (Mode)
		{
		case EEditMode::TileMap:
			TileMapMode();
			break;
		case EEditMode::Object:
			ObjectMode();
			break;
		default:
			break;
		}

		SaveAndLoad();
	}

	void SetGameMode(ARandomTileMapTest* _GameMode)
	{
		RandomTileGameMode = _GameMode;
	}

private:
	ARandomTileMapTest* RandomTileGameMode = nullptr;

};

ARandomTileMapTest::ARandomTileMapTest()
	: DungeonMap(DUNGEON_HEIGHT, std::vector<char>(DUNGEON_WIDTH, ' '))
{
	// �������� ���ּž� �մϴ�.
	// �̰� UI�����Ұ��� 
	GetWorld()->CreateCollisionProfile("Monster");

	TileMapRenderer = CreateDefaultSubObject<UTileMapRenderer>();

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	TileMapRenderer = CreateDefaultSubObject<UTileMapRenderer>();
	TileMapRenderer->SetupAttachment(RootComponent);
	TileMapRenderer->SetTileSetting(ETileMapType::Iso, "Tile", { 128.0f, 63.0f }, { 128.0f, 192.0f }, { 0.0f, 0.0f });

	// CreateDefaultSubObject<>

	// ī�޶� �����Ÿ� �ڷ� ���� 
	// ī�޶� ��ġ������ ������ ����� �Ұ��̴�.
	std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -1000.0f, 1.0f });
	Camera->GetCameraComponent()->SetZSort(0, true);

	RoomList.reserve(20);

}

ARandomTileMapTest::~ARandomTileMapTest()
{
}

void ARandomTileMapTest::Tick(float _DeltaTime)
{
	// �θ� ȣ��
	AActor::Tick(_DeltaTime);
}



void ARandomTileMapTest::LevelChangeStart()
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
		TileMapWindow = UEngineGUI::FindGUIWindow<UTileMapWindow>("TileMapWindow");

		if (nullptr == TileMapWindow)
		{
			TileMapWindow = UEngineGUI::CreateGUIWindow<UTileMapWindow>("TileMapWindow");
		}

		TileMapWindow->SetGameMode(this);

		TileMapWindow->SetActive(true);
		TileMapWindow->TileMapRenderer = TileMapRenderer.get();
	}

}

void ARandomTileMapTest::DrawRoom(const Rect& _Room)
{
	// �׵θ� �� �𼭸��� �׸���
	// �𼭸�: 4�� ������ / ��: �׵θ� / ����: �ٴ�
	int x1 = _Room.X;
	int y1 = _Room.Y;
	int x2 = _Room.X + _Room.Width - 1;
	int y2 = _Room.Y + _Room.Height - 1;

	if (0 > x1 || 0 > y1 || 40 <= x2 || 40 <= y2 )
	{
		return;
	}

	++RoomCount;

	RoomData NewRoomData{ _Room, RoomCount };
	RoomList.push_back(NewRoomData);

	// �𼭸� ǥ��(����: �»��->����->���ϴ�->���ϴ�)
	DungeonMap[y1][x1] = 'A';
	DungeonMap[y1][x2] = 'B';
	DungeonMap[y2][x1] = 'C';
	DungeonMap[y2][x2] = 'E';

	// ���Ϻ�
	for (int x = x1 + 1; x < x2; ++x)
	{
		DungeonMap[y1][x] = '#';
		DungeonMap[y2][x] = '#';
	}
	// �¿캮
	for (int y = y1 + 1; y < y2; ++y)
	{
		DungeonMap[y][x1] = '#';
		DungeonMap[y][x2] = '#';
	}
	// ���� �ٴ�
	for (int y = y1 + 1; y < y2; ++y)
	{
		for (int x = x1 + 1; x < x2; ++x)
		{
			DungeonMap[y][x] = '.';
		}
	}
}

void ARandomTileMapTest::ConnectRooms(const Rect& _Origin, const Rect& _NewRoom)
{
	// �� �簢�� �� ���� ����� �� ���� ã�� �� �� �� ������ �������� ����.
	// ���⼭�� �ܼ��ϰ� '���� ����� ���� or ���� ��'�� �Ǵ��ؼ� ó�� (�ǹ����� �Ÿ� ����� �� ����ȭ ����)

	// origin���� �߽�
	Point OriginCenter
	{
		_Origin.X + _Origin.Width / 2,
		_Origin.Y + _Origin.Height / 2
	};
	// newRoom���� �߽�
	Point NewCenter
	{
		_NewRoom.X + _NewRoom.Width / 2,
		_NewRoom.Y + _NewRoom.Height / 2
	};

	HallwayInfo Info;
	// ����� ���� �������� ������ ���� (x ���̰� ũ�� ���� ����, y ���̰� ũ�� ���� ����)
	int dx = NewCenter.X - OriginCenter.X;
	int dy = NewCenter.Y - OriginCenter.Y;

	if (std::abs(dx) > std::abs(dy)) {
		// ���� ����
		Info.From = { (dx > 0 ? _Origin.X + _Origin.Width - 2 : _Origin.X + 1),
					  OriginCenter.Y };
		Info.To = { (dx > 0 ? _NewRoom.X + 1 : _NewRoom.X + _NewRoom.Width - 2),
					  NewCenter.Y };
		Info.Size = dx > 0 ? _Origin.Width : _NewRoom.Width;
	}
	else {
		// ���� ����
		Info.From = { OriginCenter.X,
					  (dy > 0 ? _Origin.Y + _Origin.Height - 2 : _Origin.Y + 1) };
		Info.To = { NewCenter.X,
					  (dy > 0 ? _NewRoom.Y + 1 : _NewRoom.Y + _NewRoom.Height - 2) };
		Info.Size = dy > 0 ? _Origin.Height : _NewRoom.Height;
	}
	HallwayList.push_back(Info);
}

std::vector<ARandomTileMapTest::Rect> ARandomTileMapTest::Subdivide(const Rect& _Area, const Rect& _PlacedRoom)
{
	std::vector<Rect> Result;

	int x1 = _Area.X;
	int y1 = _Area.Y;
	int x2 = _Area.X + _Area.Width;
	int y2 = _Area.Y + _Area.Height;

	int rx1 = _PlacedRoom.X;
	int ry1 = _PlacedRoom.Y;
	int rx2 = _PlacedRoom.X + _PlacedRoom.Width;
	int ry2 = _PlacedRoom.Y + _PlacedRoom.Height;

	// ���� �������� 4�� ���� ��� (��, �Ʒ�, ����, ������)
	// ��, �� ������ �ּ��� 1Ÿ�� �̻��� ������ �־�� ��ȿ�ϰ� ���
	// ���� ���̿� 2Ÿ�� ������ �ּ� �波�� ���� �ʵ��� ��
	// Top
	if (ry1 - y1 > 0)
	{
		Rect TopRect
		{
			x1 + 1,  // ��ü �׵θ� ���
			y1 + 1,
			_Area.Width - 2,
			(ry1 - y1) - 1
		};
		Result.push_back(TopRect);
	}
	// Bottom
	if (y2 - ry2 > 0)
	{
		Rect BottomRect
		{
			x1 + 1,
			ry2,
			_Area.Width - 2,
			(y2 - ry2) - 1
		};
		Result.push_back(BottomRect);
	}
	// Left
	if (rx1 - x1 > 0)
	{
		Rect LeftRect
		{
			x1 + 1,
			ry1,
			(rx1 - x1) - 1,
			_PlacedRoom.Height
		};
		Result.push_back(LeftRect);
	}
	// Right
	if (x2 - rx2 > 0)
	{
		Rect RightRect
		{
			rx2,
			ry1,
			(x2 - rx2) - 1,
			_PlacedRoom.Height
		};
		Result.push_back(RightRect);
	}

	return Result;
}

void ARandomTileMapTest::CreateRoom(const Rect& _Area, Rect* _OriginatingRoom, bool _IsFirstRoom, bool _ForceLargeSetPiece)
{
	// ������ �ʹ� ������ Ż��
	if (!_Area.IsValid())
	{
		return;
	}

	// �� ũ�⸦ ���� ���� (���� ù ��° �濡 SetPiece�� ��ġ�ؾ� �Ѵٸ� ���� ������ ����)
	int RoomW = (_ForceLargeSetPiece) ? std::max<int>(8, std::min<int>(_Area.Width - 1, MAX_ROOM_SIZE1))
		: Random.RandomInt(MIN_ROOM_SIZE1, std::min<int>(_Area.Width - 1, MAX_ROOM_SIZE1));
	int RoomH = (_ForceLargeSetPiece) ? std::max<int>(8, std::min<int>(_Area.Height - 1, MAX_ROOM_SIZE1))
		: Random.RandomInt(MIN_ROOM_SIZE1, std::min<int>(_Area.Height - 1, MAX_ROOM_SIZE1));

	// ���� ���� ��ġ�� ���� ����
	int PosX = Random.RandomInt(_Area.X + 1, _Area.X + _Area.Width - RoomW - 1);
	int PosY = Random.RandomInt(_Area.Y + 1, _Area.Y + _Area.Height - RoomH - 1);

	Rect NewRoom{ PosX, PosY, RoomW, RoomH };

	// ���� ������ �׸���
	DrawRoom(NewRoom);
	
	// ���� ���� ������ ���� ���������� ����
	if (_OriginatingRoom)
	{
		ConnectRooms(*_OriginatingRoom, NewRoom);
	}

	// ���� �������� ���� ������ 4���� ������
	auto SubAreas = Subdivide(_Area, NewRoom);
	for (auto& Sub : SubAreas)
	{
		// �� ������ 2Ÿ�� ���� ���(�� ����)�Ͽ�, ��������� �ٸ� ���� ���鵵��
		if (Sub.IsValid())
		{
			CreateRoom(Sub, &NewRoom, false, false);
		}
	}
}

void ARandomTileMapTest::DrawHallways()
{
	for (const auto& Hallway : HallwayList)
	{
		Point From = Hallway.From;
		Point To = Hallway.To;

		// ���� ��(width)�� 1~3 ���̷� ���� ����
		int HallwayWidth = /*Hallway.Size - 1;*/Random.RandomInt(1, 3);

		// Bresenham Ȥ�� �ܼ� �ܰ��� ���� �������� ������ �׸���.
		// ���⼭�� �ܼ��ϰ� x->y ������ ���������� �׸��� ������ �ÿ�.

		// x Ȥ�� y ���� ���� ����
		int StepX = (From.X < To.X) ? 1 : -1;
		int StepY = (From.Y < To.Y) ? 1 : -1;

		// ���� ���� �̵�, �� ���� ���� �̵� (Ȥ�� �� �ݴ�)
		// �ǹ������� �� �� �������� �־� Zigzag ���·� �׸� ���� ����
		// 1) x ���� from.x���� to.x���� �̵�
		for (int x = From.X; x != To.X; x += StepX)
		{
			for (int w = 0; w < HallwayWidth; ++w)
			{
				int DrawY = From.Y + w;
				if (DrawY >= 0 && DrawY < DUNGEON_HEIGHT && x >= 0 && x < DUNGEON_WIDTH)
				{
					// ��('#')�� ������ ��('D')��, �ٴ�(' ')�̸� ����('.')��
					if (DungeonMap[DrawY][x] == '#')
					{
						// ���� �̹� ���� ���� �ִ��� üũ
						bool CanPlaceDoor = true;
						for (int dy = -1; dy <= 1; ++dy)
						{
							for (int dx2 = -1; dx2 <= 1; ++dx2)
							{
								int ny = DrawY + dy;
								int nx = x + dx2;
								if (ny >= 0 && ny < DUNGEON_HEIGHT && nx >= 0 && nx < DUNGEON_WIDTH)
								{
									if (DungeonMap[ny][nx] == 'D' || DungeonMap[ny][nx] == '1' || DungeonMap[ny][nx] == '2')
									{
										CanPlaceDoor = false;
										break;
									}
								}
							}
							if (!CanPlaceDoor)
							{
								break;
							}
						}
						DungeonMap[DrawY][x] = (CanPlaceDoor ? 'D2' : '.');
					}
					else if (DungeonMap[DrawY][x] == ' ')
					{
						DungeonMap[DrawY][x] = '.';
					}
				}
			}
		}
		// 2) y ���� from.y���� to.y���� �̵�
		for (int y = From.Y; y != To.Y; y += StepY)
		{
			for (int w = 0; w < HallwayWidth; ++w)
			{
				int DrawX = To.X + w * StepX;
				if (y >= 0 && y < DUNGEON_HEIGHT && DrawX >= 0 && DrawX < DUNGEON_WIDTH)
				{
					if (DungeonMap[y][DrawX] == '#')
					{
						bool CanPlaceDoor = true;
						for (int dy = -1; dy <= 1; ++dy)
						{
							for (int dx2 = -1; dx2 <= 1; ++dx2)
							{
								int ny = y + dy;
								int nx = DrawX + dx2;
								if (ny >= 0 && ny < DUNGEON_HEIGHT && nx >= 0 && nx < DUNGEON_WIDTH)
								{
									if (DungeonMap[ny][nx] == 'D' || DungeonMap[ny][nx] == '1' || DungeonMap[ny][nx] == '2')
									{
										CanPlaceDoor = false;
										break;
									}
								}
							}
							if (!CanPlaceDoor) break;
						}
						DungeonMap[y][DrawX] = (CanPlaceDoor ? 'D1' : '.');
					}
					else if (DungeonMap[y][DrawX] == ' ')
					{
						DungeonMap[y][DrawX] = '.';
					}
				}
			}
		}
	}
}

void ARandomTileMapTest::CleanupDungeon()
{
	for (int y = 0; y < DUNGEON_HEIGHT; ++y)
	{
		for (int x = 0; x < DUNGEON_WIDTH; ++x)
		{
			// Corner Tiles
			if (DungeonMap[y][x] == 'A' || DungeonMap[y][x] == 'B' || DungeonMap[y][x] == 'C' || DungeonMap[y][x] == 'E')
			{
				DungeonMap[y][x] = '#';
			}
		}
	}

	// ����, �� ���� ������ ����. '.' ������ ����(' ')�� ������ ��('#')���� ġȯ
	for (int y = 1; y < DUNGEON_HEIGHT - 1; ++y)
	{
		for (int x = 1; x < DUNGEON_WIDTH - 1; ++x)
		{
			if (DungeonMap[y][x] == ' ')
			{
				// �ֺ��� '.'�� �ϳ��� ������ ������ �����
				bool NearFloor = false;
				for (int dy = -1; dy <= 1; ++dy)
				{
					for (int dx2 = -1; dx2 <= 1; ++dx2)
					{
						if (DungeonMap[y + dy][x + dx2] == '.' || DungeonMap[y + dy][x + dx2] == 'D')
						{
							NearFloor = true;
							break;
						}
					}
					if (NearFloor) break;
				}
				if (NearFloor)
				{
					DungeonMap[y][x] = '#';
				}
			}
		}
	}

	// ���������� ' ' (�ƹ��͵� ���� ����)�� '.'���� �ٲٰų� �״�� �δ� �� ���ϴ� �� ���� ����
	// ���⼭�� �״�� �ξ� ���������� "�ܺ�"�� ǥ����
}

bool ARandomTileMapTest::FillVoidAreas()
{
	int FilledCountBefore = 0;
	// ������� '.'�� Ÿ�� ���� ����
	for (int y = 0; y < DUNGEON_HEIGHT; ++y)
	{
		for (int x = 0; x < DUNGEON_WIDTH; ++x)
		{
			if (DungeonMap[y][x] == '.') FilledCountBefore++;
		}
	}

	// �� "�� ����(' ')"�� BFS/DFS�� Ž���Ͽ�, �ش� ������ �����ִ�(��� ��谡 ��)�� Ȯ��
	// �׸��� �� ������ �簢�� ���¸� ���� �� �ִ���(5��5 �̻� 12��14 ����)�� �����ϰ� �õ�
	// ���⼭�� ������ �� ������ ���� ��ĵ�Ͽ� ������ ū ���簢���� ã�� ����� �ÿ�

	bool DidFill = false;
	for (int attempt = 0; attempt < 10; ++attempt)
	{
		int w = Random.RandomInt(FILL_RECT_MIN_W, FILL_RECT_MAX_W);
		int h = Random.RandomInt(FILL_RECT_MIN_H, FILL_RECT_MAX_H);
		int StartX = Random.RandomInt(1, DUNGEON_WIDTH - w - 1);
		int StartY = Random.RandomInt(1, DUNGEON_HEIGHT - h - 1);

		// �ش� ������ ���� ' '�̰ų� '#'���� �ѷ��ο� �־�� �ٴ����� ä�� �� �ִ� (������ üũ)
		bool CanFill = true;
		for (int y = StartY; y < StartY + h; ++y)
		{
			for (int x = StartX; x < StartX + w; ++x)
			{
				if (DungeonMap[y][x] != ' ')
				{
					CanFill = false;
					break;
				}
			}
			if (false == CanFill)
			{
				break;
			}
		}
		// ä���
		if (CanFill)
		{
			// ���� �� �׵θ��� ���� '#' ���� �뷫�� üũ (�ǹ������� ��Ȯ�� ��� �������� BFS�� Ȯ���ϴ� ���� ����)
			for (int x = StartX; x < StartX + w; ++x)
			{
				if (DungeonMap[StartY - 1][x] != '#' || DungeonMap[StartY + h][x] != '#')
				{
					CanFill = false;
					break;
				}
			}
			for (int y = StartY; y < StartY + h; ++y)
			{
				if (DungeonMap[y][StartX - 1] != '#' || DungeonMap[y][StartX + w] != '#')
				{
					CanFill = false; break;
				}
			}
		}
		if (CanFill)
		{
			for (int y = StartY; y < StartY + h; ++y)
			{
				for (int x = StartX; x < StartX + w; ++x)
				{
					DungeonMap[y][x] = '.';
				}
			}
			DidFill = true;
		}
	}

	int FilledCountAfter = 0;
	for (int y = 0; y < DUNGEON_HEIGHT; ++y)
	{
		for (int x = 0; x < DUNGEON_WIDTH; ++x)
		{
			if (DungeonMap[y][x] == '.')
			{
				FilledCountAfter++;
			}
		}
	}

	// 700�� �̻��� '.'�� Ȯ���ߴ��� Ȯ��
	return (FilledCountAfter >= FLOOR_THRESHOLD);
}

bool ARandomTileMapTest::GenerateDungeon()
{
	// �� �ʱ�ȭ
	for (int y = 0; y < DUNGEON_HEIGHT; ++y)
	{
		for (int x = 0; x < DUNGEON_WIDTH; ++x)
		{
			DungeonMap[y][x] = ' ';
		}
	}
	HallwayList.clear();

	// ��ü �������� �׵θ� 1ĭ�� ������ ���θ� ������� �� ����
	Rect FullArea{ BORDER_SIZE, BORDER_SIZE,
					DUNGEON_WIDTH - BORDER_SIZE * 2,
					DUNGEON_HEIGHT - BORDER_SIZE * 2 };

	// ù ���� SetPiece ���� ���� ���� (������ �� ũ��)
	bool ForceLargeSetPiece = true;
	CreateRoom(FullArea, nullptr, true, ForceLargeSetPiece);

	// ���� �׸���
	DrawHallways();

	// Cleanup
	CleanupDungeon();

	// Fill Voids
	int tries = 0;
	while (tries < MAX_FILL_TRIES)
	{
		if (FillVoidAreas())
		{
			// ��ǥ�� ����
			return true;
		}
		tries++;
	}
	// ��ǥ('.' 700�� �̻�)�� �� ��ġ�� ����
	RoomList.clear();

	return false;
}
