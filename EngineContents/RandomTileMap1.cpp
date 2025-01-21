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

				//SRV입니다
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
				// 엔터를 치지 않는개념.
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
					if (RandomTileGameMode->generateDungeon()) {
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
						if ('#' == static_cast<int>(RandomTileGameMode->dungeonMap[y][x]))
						{
							TileMapRenderer->SetTile(x, y, 0);
						}

						if ('.' == static_cast<int>(RandomTileGameMode->dungeonMap[y][x]))
						{
							TileMapRenderer->SetTile(x, y, 1);
						}

						if ('1' == static_cast<int>(RandomTileGameMode->dungeonMap[y][x]))
						{
							TileMapRenderer->SetTile(x, y, 2);
						}

						if ('2' == static_cast<int>(RandomTileGameMode->dungeonMap[y][x]))
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
				RandomTileGameMode->drawHallways();
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
				MSGASSERT("리소스 폴더를 찾지 못했습니다.");
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
					// 여기 저장된다는 이야기
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
				MSGASSERT("리소스 폴더를 찾지 못했습니다.");
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
	: dungeonMap(DUNGEON_HEIGHT, std::vector<char>(DUNGEON_WIDTH, ' '))
{
	// 레벨마다 해주셔야 합니다.
	// 이걸 UI공유할건지 
	GetWorld()->CreateCollisionProfile("Monster");

	TileMapRenderer = CreateDefaultSubObject<UTileMapRenderer>();

	std::shared_ptr<UDefaultSceneComponent> Default = CreateDefaultSubObject<UDefaultSceneComponent>();
	RootComponent = Default;

	TileMapRenderer = CreateDefaultSubObject<UTileMapRenderer>();
	TileMapRenderer->SetupAttachment(RootComponent);
	TileMapRenderer->SetTileSetting(ETileMapType::Iso, "Tile", { 128.0f, 63.0f }, { 128.0f, 192.0f }, { 0.0f, 0.0f });

	// CreateDefaultSubObject<>

	// 카메라를 일정거리 뒤로 가서 
	// 카메라 위치조정을 무조건 해줘야 할것이다.
	std::shared_ptr<ACameraActor> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation({ 0.0f, 0.0f, -1000.0f, 1.0f });
	Camera->GetCameraComponent()->SetZSort(0, true);

}

ARandomTileMapTest::~ARandomTileMapTest()
{
}

void ARandomTileMapTest::Tick(float _DeltaTime)
{
	// 부모 호출
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

void ARandomTileMapTest::drawRoom(const Rect& room)
{
	// 테두리 및 모서리를 그리기
	// 모서리: 4개 꼭짓점 / 벽: 테두리 / 내부: 바닥
	int x1 = room.x;
	int y1 = room.y;
	int x2 = room.x + room.width - 1;
	int y2 = room.y + room.height - 1;

	// 모서리 표시(순서: 좌상단->우상단->좌하단->우하단)
	dungeonMap[y1][x1] = 'A';
	dungeonMap[y1][x2] = 'B';
	dungeonMap[y2][x1] = 'C';
	dungeonMap[y2][x2] = 'E';

	// 상하벽
	for (int x = x1 + 1; x < x2; ++x) {
		dungeonMap[y1][x] = '#';
		dungeonMap[y2][x] = '#';
	}
	// 좌우벽
	for (int y = y1 + 1; y < y2; ++y) {
		dungeonMap[y][x1] = '#';
		dungeonMap[y][x2] = '#';
	}
	// 내부 바닥
	for (int y = y1 + 1; y < y2; ++y) {
		for (int x = x1 + 1; x < x2; ++x) {
			dungeonMap[y][x] = '.';
		}
	}
}

void ARandomTileMapTest::connectRooms(const Rect& origin, const Rect& newRoom)
{
	// 두 사각형 간 가장 가까운 두 변을 찾아 그 중 한 지점을 랜덤으로 선택.
	// 여기서는 단순하게 '가장 가까운 수평 or 수직 변'을 판단해서 처리 (실무에선 거리 계산을 더 정교화 가능)

	// origin방의 중심
	Point originCenter{
		origin.x + origin.width / 2,
		origin.y + origin.height / 2
	};
	// newRoom방의 중심
	Point newCenter{
		newRoom.x + newRoom.width / 2,
		newRoom.y + newRoom.height / 2
	};

	HallwayInfo info;
	// 가까운 축을 기준으로 복도를 연결 (x 차이가 크면 수평 연결, y 차이가 크면 수직 연결)
	int dx = newCenter.x - originCenter.x;
	int dy = newCenter.y - originCenter.y;

	if (std::abs(dx) > std::abs(dy)) {
		// 수평 연결
		info.from = { (dx > 0 ? origin.x + origin.width - 2 : origin.x + 1),
					  originCenter.y };
		info.to = { (dx > 0 ? newRoom.x + 1 : newRoom.x + newRoom.width - 2),
					  newCenter.y };
	}
	else {
		// 수직 연결
		info.from = { originCenter.x,
					  (dy > 0 ? origin.y + origin.height - 2 : origin.y + 1) };
		info.to = { newCenter.x,
					  (dy > 0 ? newRoom.y + 1 : newRoom.y + newRoom.height - 2) };
	}
	hallwayList.push_back(info);
}

std::vector<ARandomTileMapTest::Rect> ARandomTileMapTest::subdivide(const Rect& area, const Rect& placedRoom)
{
	std::vector<Rect> result;

	int x1 = area.x;
	int y1 = area.y;
	int x2 = area.x + area.width;
	int y2 = area.y + area.height;

	int rx1 = placedRoom.x;
	int ry1 = placedRoom.y;
	int rx2 = placedRoom.x + placedRoom.width;
	int ry2 = placedRoom.y + placedRoom.height;

	// 방을 기준으로 4개 영역 계산 (위, 아래, 왼쪽, 오른쪽)
	// 단, 각 영역에 최소한 1타일 이상의 공간이 있어야 유효하게 취급
	// 영역 사이에 2타일 간격을 둬서 방끼리 붙지 않도록 함
	// Top
	if (ry1 - y1 > 0) {
		Rect topRect{
			x1 + 1,  // 전체 테두리 고려
			y1 + 1,
			area.width - 2,
			(ry1 - y1) - 1
		};
		result.push_back(topRect);
	}
	// Bottom
	if (y2 - ry2 > 0) {
		Rect bottomRect{
			x1 + 1,
			ry2,
			area.width - 2,
			(y2 - ry2) - 1
		};
		result.push_back(bottomRect);
	}
	// Left
	if (rx1 - x1 > 0) {
		Rect leftRect{
			x1 + 1,
			ry1,
			(rx1 - x1) - 1,
			placedRoom.height
		};
		result.push_back(leftRect);
	}
	// Right
	if (x2 - rx2 > 0) {
		Rect rightRect{
			rx2,
			ry1,
			(x2 - rx2) - 1,
			placedRoom.height
		};
		result.push_back(rightRect);
	}

	return result;
}

void ARandomTileMapTest::createRoom(const Rect& area, Rect* originatingRoom, bool isFirstRoom, bool forceLargeSetPiece)
{
	// 영역이 너무 작으면 탈출
	if (!area.isValid()) return;

	// 방 크기를 랜덤 결정 (만약 첫 번째 방에 SetPiece를 배치해야 한다면 강제 사이즈 조절)
	int roomW = (forceLargeSetPiece) ? std::max<int>(8, std::min<int>(area.width - 1, MAX_ROOM_SIZE1))
		: Random.RandomInt(MIN_ROOM_SIZE1, std::min<int>(area.width - 1, MAX_ROOM_SIZE1));
	int roomH = (forceLargeSetPiece) ? std::max<int>(8, std::min<int>(area.height - 1, MAX_ROOM_SIZE1))
		: Random.RandomInt(MIN_ROOM_SIZE1, std::min<int>(area.height - 1, MAX_ROOM_SIZE1));

	// 방을 놓을 위치를 랜덤 결정
	int posX = Random.RandomInt(area.x + 1, area.x + area.width - roomW - 1);
	int posY = Random.RandomInt(area.y + 1, area.y + area.height - roomH - 1);

	Rect newRoom{ posX, posY, roomW, roomH };

	// 방을 지도에 그린다
	drawRoom(newRoom);

	// 기존 방이 있으면 복도 연결정보를 저장
	if (originatingRoom) {
		connectRooms(*originatingRoom, newRoom);
	}

	// 방을 기준으로 남은 영역을 4개로 나누고
	auto subAreas = subdivide(area, newRoom);
	for (auto& sub : subAreas) {
		// 각 영역을 2타일 정도 축소(벽 간격)하여, 재귀적으로 다른 방을 만들도록
		if (sub.isValid()) {
			createRoom(sub, &newRoom, false, false);
		}
	}
}

void ARandomTileMapTest::drawHallways()
{
	for (const auto& hallway : hallwayList) {
		Point from = hallway.from;
		Point to = hallway.to;

		// 복도 폭(width)을 1~3 사이로 랜덤 결정
		int hallwayWidth = Random.RandomInt(1, 3);

		// Bresenham 혹은 단순 단계적 연결 로직으로 라인을 그린다.
		// 여기서는 단순하게 x->y 방향을 순차적으로 그리는 접근을 시연.

		// x 혹은 y 방향 순서 결정
		int stepX = (from.x < to.x) ? 1 : -1;
		int stepY = (from.y < to.y) ? 1 : -1;

		// 수평 먼저 이동, 그 다음 수직 이동 (혹은 그 반대)
		// 실무에서는 좀 더 랜덤성을 주어 Zigzag 형태로 그릴 수도 있음
		// 1) x 축을 from.x에서 to.x까지 이동
		for (int x = from.x; x != to.x; x += stepX) {
			for (int w = 0; w < hallwayWidth; ++w) {
				int drawY = from.y + w;
				if (drawY >= 0 && drawY < DUNGEON_HEIGHT && x >= 0 && x < DUNGEON_WIDTH) {
					// 벽('#')를 만나면 문('D')로, 바닥(' ')이면 복도('.')로
					if (dungeonMap[drawY][x] == '#') {
						// 문은 이미 인접 문이 있는지 체크
						bool canPlaceDoor = true;
						for (int dy = -1; dy <= 1; ++dy) {
							for (int dx2 = -1; dx2 <= 1; ++dx2) {
								int ny = drawY + dy;
								int nx = x + dx2;
								if (ny >= 0 && ny < DUNGEON_HEIGHT && nx >= 0 && nx < DUNGEON_WIDTH) {
									if (dungeonMap[ny][nx] == 'D') {
										canPlaceDoor = false;
										break;
									}
								}
							}
							if (!canPlaceDoor) break;
						}
						dungeonMap[drawY][x] = (canPlaceDoor ? 'D2' : '.');
					}
					else if (dungeonMap[drawY][x] == ' ') {
						dungeonMap[drawY][x] = '.';
					}
				}
			}
		}
		// 2) y 축을 from.y에서 to.y까지 이동
		for (int y = from.y; y != to.y; y += stepY) {
			for (int w = 0; w < hallwayWidth; ++w) {
				int drawX = to.x + w * stepX;
				if (y >= 0 && y < DUNGEON_HEIGHT && drawX >= 0 && drawX < DUNGEON_WIDTH) {
					if (dungeonMap[y][drawX] == '#') {
						bool canPlaceDoor = true;
						for (int dy = -1; dy <= 1; ++dy) {
							for (int dx2 = -1; dx2 <= 1; ++dx2) {
								int ny = y + dy;
								int nx = drawX + dx2;
								if (ny >= 0 && ny < DUNGEON_HEIGHT && nx >= 0 && nx < DUNGEON_WIDTH) {
									if (dungeonMap[ny][nx] == 'D') {
										canPlaceDoor = false;
										break;
									}
								}
							}
							if (!canPlaceDoor) break;
						}
						dungeonMap[y][drawX] = (canPlaceDoor ? 'D1' : '.');
					}
					else if (dungeonMap[y][drawX] == ' ') {
						dungeonMap[y][drawX] = '.';
					}
				}
			}
		}
	}
}

void ARandomTileMapTest::cleanupDungeon()
{
	for (int y = 0; y < DUNGEON_HEIGHT; ++y) {
		for (int x = 0; x < DUNGEON_WIDTH; ++x) {
			// Corner Tiles
			if (dungeonMap[y][x] == 'A' || dungeonMap[y][x] == 'B' ||
				dungeonMap[y][x] == 'C' || dungeonMap[y][x] == 'E') {
				dungeonMap[y][x] = '#';
			}
		}
	}

	// 복도, 방 사이 공간을 정리. '.' 주위에 공백(' ')이 있으면 벽('#')으로 치환
	for (int y = 1; y < DUNGEON_HEIGHT - 1; ++y) {
		for (int x = 1; x < DUNGEON_WIDTH - 1; ++x) {
			if (dungeonMap[y][x] == ' ') {
				// 주변에 '.'이 하나라도 있으면 벽으로 만든다
				bool nearFloor = false;
				for (int dy = -1; dy <= 1; ++dy) {
					for (int dx2 = -1; dx2 <= 1; ++dx2) {
						if (dungeonMap[y + dy][x + dx2] == '.' || dungeonMap[y + dy][x + dx2] == 'D') {
							nearFloor = true;
							break;
						}
					}
					if (nearFloor) break;
				}
				if (nearFloor) {
					dungeonMap[y][x] = '#';
				}
			}
		}
	}

	// 마지막으로 ' ' (아무것도 없는 공간)은 '.'으로 바꾸거나 그대로 두는 등 원하는 룰 적용 가능
	// 여기서는 그대로 두어 가시적으로 "외부"를 표현함
}

bool ARandomTileMapTest::fillVoidAreas()
{
	int filledCountBefore = 0;
	// 현재까지 '.'인 타일 수를 센다
	for (int y = 0; y < DUNGEON_HEIGHT; ++y) {
		for (int x = 0; x < DUNGEON_WIDTH; ++x) {
			if (dungeonMap[y][x] == '.') filledCountBefore++;
		}
	}

	// 각 "빈 공간(' ')"을 BFS/DFS로 탐색하여, 해당 구역이 닫혀있는(모든 경계가 벽)지 확인
	// 그리고 그 영역의 사각형 형태를 만들 수 있는지(5×5 이상 12×14 이하)를 랜덤하게 시도
	// 여기서는 간단히 빈 공간을 직접 스캔하여 적절히 큰 직사각형을 찾는 방식을 시연

	bool didFill = false;
	for (int attempt = 0; attempt < 10; ++attempt) {
		int w = Random.RandomInt(FILL_RECT_MIN_W, FILL_RECT_MAX_W);
		int h = Random.RandomInt(FILL_RECT_MIN_H, FILL_RECT_MAX_H);
		int startX = Random.RandomInt(1, DUNGEON_WIDTH - w - 1);
		int startY = Random.RandomInt(1, DUNGEON_HEIGHT - h - 1);

		// 해당 영역이 전부 ' '이거나 '#'으로 둘러싸여 있어야 바닥으로 채울 수 있다 (간단한 체크)
		bool canFill = true;
		for (int y = startY; y < startY + h; ++y) {
			for (int x = startX; x < startX + w; ++x) {
				if (dungeonMap[y][x] != ' ') {
					canFill = false;
					break;
				}
			}
			if (!canFill) break;
		}
		// 채우기
		if (canFill) {
			// 영역 밖 테두리가 전부 '#' 인지 대략적 체크 (실무에서는 정확히 폐쇄 공간인지 BFS로 확인하는 편이 좋음)
			for (int x = startX; x < startX + w; ++x) {
				if (dungeonMap[startY - 1][x] != '#' || dungeonMap[startY + h][x] != '#') {
					canFill = false; break;
				}
			}
			for (int y = startY; y < startY + h; ++y) {
				if (dungeonMap[y][startX - 1] != '#' || dungeonMap[y][startX + w] != '#') {
					canFill = false; break;
				}
			}
		}
		if (canFill) {
			for (int y = startY; y < startY + h; ++y) {
				for (int x = startX; x < startX + w; ++x) {
					dungeonMap[y][x] = '.';
				}
			}
			didFill = true;
		}
	}

	int filledCountAfter = 0;
	for (int y = 0; y < DUNGEON_HEIGHT; ++y) {
		for (int x = 0; x < DUNGEON_WIDTH; ++x) {
			if (dungeonMap[y][x] == '.') filledCountAfter++;
		}
	}

	// 700개 이상의 '.'을 확보했는지 확인
	return (filledCountAfter >= FLOOR_THRESHOLD);
}

bool ARandomTileMapTest::generateDungeon()
{
	// 맵 초기화
	for (int y = 0; y < DUNGEON_HEIGHT; ++y) {
		for (int x = 0; x < DUNGEON_WIDTH; ++x) {
			
			dungeonMap[y][x] = ' ';
		}
	}
	hallwayList.clear();

	// 전체 영역에서 테두리 1칸을 제외한 내부를 대상으로 방 생성
	Rect fullArea{ BORDER_SIZE, BORDER_SIZE,
					DUNGEON_WIDTH - BORDER_SIZE * 2,
					DUNGEON_HEIGHT - BORDER_SIZE * 2 };

	// 첫 방은 SetPiece 방일 수도 있음 (강제로 좀 크게)
	bool forceLargeSetPiece = true;
	createRoom(fullArea, nullptr, true, forceLargeSetPiece);

	// 복도 그리기
	drawHallways();

	// Cleanup
	cleanupDungeon();

	// Fill Voids
	int tries = 0;
	while (tries < MAX_FILL_TRIES) {
		if (fillVoidAreas()) {
			// 목표에 도달
			return true;
		}
		tries++;
	}
	// 목표('.' 700개 이상)에 못 미치면 실패
	return false;
}
