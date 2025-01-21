#pragma once
#include <EngineCore/GameMode.h>
#include <EngineBase/EngineRandom.h>
#include <algorithm>

static const int DUNGEON_WIDTH = 40;
static const int DUNGEON_HEIGHT = 40;
static const int MIN_ROOM_SIZE1 = 4;
static const int MAX_ROOM_SIZE1 = 9;
static const int BORDER_SIZE = 1;
static const int FLOOR_THRESHOLD = 700;
static const int FILL_RECT_MIN_W = 5;
static const int FILL_RECT_MIN_H = 5;
static const int FILL_RECT_MAX_W = 12;
static const int FILL_RECT_MAX_H = 14;
static const int MAX_FILL_TRIES = 100;


// 설명 :
class ARandomTileMapTest : public AGameMode
{
public:
	
	struct Point {
		int x;
		int y;
	};

	// 사각 영역 정의용 구조체
	struct Rect {
		int x;      // 좌상단 X
		int y;      // 좌상단 Y
		int width;
		int height;

		// 사각 영역이 유효한(너무 작지 않은)지 확인
		bool isValid() const {
			return (width >= MIN_ROOM_SIZE1 && height >= MIN_ROOM_SIZE1);
		}
	};

	// 복도(잇는 길) 정보를 임시 저장할 구조체
	struct HallwayInfo {
		Point from;
		Point to;
	};
	
	// 지도 배열(문자형)
	std::vector<std::vector<char>> dungeonMap;

	// 복도 정보를 저장하는 벡터
	std::vector<HallwayInfo> hallwayList;

	// 사각형 내부에 방을 그리는 함수
	// 모서리는 'A', 'B', 'C', 'E' 등으로 표기, 벽('#'), 바닥('.')를 그린다.
	void drawRoom(const Rect& room);
	

	// 두 방 사이를 연결할 복도 정보 (임시) 생성
	void connectRooms(const Rect& origin, const Rect& newRoom);
	
    std::vector<Rect> subdivide(const Rect& area, const Rect& placedRoom);
    
	void createRoom(const Rect& area, Rect* originatingRoom = nullptr, bool isFirstRoom = false, bool forceLargeSetPiece = false);
	
    void drawHallways();
    
	void cleanupDungeon();
	
    // Flood Fill 등을 이용해 특정 영역이 벽으로 둘러싸여있는지 찾고, 조건(최소 5×5, 최대 12×14)에 부합하면 바닥('.')으로 채움
    bool fillVoidAreas();
    
	// 던전을 생성하는 메인 함수
	bool generateDungeon();
	


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

	
protected:
	void LevelChangeStart() override;

private:
	
	std::shared_ptr<class UTileMapWindow> TileMapWindow;

	std::shared_ptr<class USpriteRenderer> PivotSpriteRenderer;

	std::shared_ptr<class UTileMapRenderer> TileMapRenderer;
};