#pragma once
#include <EngineCore/GameMode.h>
#include <EngineBase/EngineRandom.h>
#include <algorithm>

static const int DUNGEON_WIDTH = 40;
static const int DUNGEON_HEIGHT = 40;
static const int MIN_ROOM_SIZE1 = 5;
static const int MAX_ROOM_SIZE1 = 9;
static const int BORDER_SIZE = 1;
static const int FLOOR_THRESHOLD = 600;
static const int FILL_RECT_MIN_W = 5;
static const int FILL_RECT_MIN_H = 5;
static const int FILL_RECT_MAX_W = 12;
static const int FILL_RECT_MAX_H = 14;
static const int MAX_FILL_TRIES = 100;



// 설명 :
class ARandomTileMapTest : public AGameMode
{
public:
	
	struct Point
	{
		int X;
		int Y;
	};

	// 사각 영역 정의용 구조체
	struct Rect
	{
		int X;      // 좌상단 X
		int Y;      // 좌상단 Y
		int Width;
		int Height;

		// 사각 영역이 유효한(너무 작지 않은)지 확인
		bool IsValid() const
		{
			return (Width >= MIN_ROOM_SIZE1 && Height >= MIN_ROOM_SIZE1);
		}
	};

	// 복도(잇는 길) 정보를 임시 저장할 구조체
	struct HallwayInfo
	{
		Point From;
		Point To;
		int Size;
	};
	
	struct RoomData
	{
		Rect RoomRect;
		int RoomNum;
	};

	// 지도 배열(문자형)
	std::vector<std::vector<char>> DungeonMap;

	std::vector<RoomData> RoomList;

	// 복도 정보를 저장하는 벡터
	std::vector<HallwayInfo> HallwayList;

	// 사각형 내부에 방을 그리는 함수
	// 모서리는 'A', 'B', 'C', 'E' 등으로 표기, 벽('#'), 바닥('.')를 그린다.
	void DrawRoom(const Rect& _Room);
	

	// 두 방 사이를 연결할 복도 정보 (임시) 생성
	void ConnectRooms(const Rect& _Origin, const Rect& _NewRoom);
	
    std::vector<Rect> Subdivide(const Rect& _Area, const Rect& _PlacedRoom);
    
	void CreateRoom(const Rect& _Area, Rect* _OriginatingRoom = nullptr, bool _IsFirstRoom = false, bool _ForceLargeSetPiece = false);
	
    void DrawHallways();
    
	void CleanupDungeon();
	
    // Flood Fill 등을 이용해 특정 영역이 벽으로 둘러싸여있는지 찾고, 조건(최소 5×5, 최대 12×14)에 부합하면 바닥('.')으로 채움
    bool FillVoidAreas();
    
	// 던전을 생성하는 메인 함수
	bool GenerateDungeon();
	


	// constrcuter destructer
	ARandomTileMapTest();
	~ARandomTileMapTest();

	// delete Function
	ARandomTileMapTest(const ARandomTileMapTest& _Other) = delete;
	ARandomTileMapTest(ARandomTileMapTest&& _Other) noexcept = delete;
	ARandomTileMapTest& operator=(const ARandomTileMapTest& _Other) = delete;
	ARandomTileMapTest& operator=(ARandomTileMapTest&& _Other) noexcept = delete;

	void Tick(float _DeltaTime);

	UEngineRandom Random;
	
	int RoomCount = 0;
	
protected:
	void LevelChangeStart() override;

private:
	
	std::shared_ptr<class UTileMapWindow> TileMapWindow;

	std::shared_ptr<class USpriteRenderer> PivotSpriteRenderer;

	std::shared_ptr<class UTileMapRenderer> TileMapRenderer;
};