#pragma once
#include <EngineCore/GameMode.h>

const int WIDTH = 30;
const int HEIGHT = 30;
const int MIN_ROOM_SIZE = 5;
const int MAX_ROOM_SIZE = 20;

enum class ETileType
{
	EMPTY,
	WALL,
};

struct FRoom
{
	int X = 0;
	int Y = 0;
	int Width = 0;
	int Height = 0;

	FRoom(int _X, int _Y, int _Width, int _Height)
		: X(_X), Y(_Y), Width(_Width), Height(_Height) {}

	bool Intersects(const FRoom& _Other) const
	{
		return !(X + Width <= _Other.X || X >= _Other.X + _Other.Width || Y + Height <= _Other.Y || Y >= _Other.Y + _Other.Height);
	}
};

struct FRoomNode
{
	int X = 0;
	int Y = 0;
	int Width = 0;
	int Height = 0;

	FRoom Room;

	FRoomNode* _Left = nullptr;
	FRoomNode* _Right = nullptr;

	FRoomNode(int _X, int _Y, int _Width, int _Height)
		: X(_X), Y(_Y), Width(_Width), Height(_Height), Room(0, 0, 0, 0) {}
};

void GenerateDungeon(std::vector<std::vector<ETileType>>& _Map);
void Traverse(FRoomNode* _Node, std::vector<FRoom>& _Rooms);
void DeleteBSPTree(FRoomNode* Node);

// Ό³Έν :
class ARandomTileMap : public AGameMode
{
public:
	
	// constrcuter destructer
	ARandomTileMap();
	~ARandomTileMap();

	// delete Function
	ARandomTileMap(const ARandomTileMap& _Other) = delete;
	ARandomTileMap(ARandomTileMap&& _Other) noexcept = delete;
	ARandomTileMap& operator=(const ARandomTileMap& _Other) = delete;
	ARandomTileMap& operator=(ARandomTileMap&& _Other) noexcept = delete;

	void Tick(float _DeltaTime);

	//void PrintMap(const std::vector<std::vector<ETileType>>& _Map);


protected:
	void LevelChangeStart() override;

private:

	std::shared_ptr<class UTileMapWindow> TileMapWindow;

	std::shared_ptr<class USpriteRenderer> PivotSpriteRenderer;

	std::shared_ptr<class UTileMapRenderer> TileMapRenderer;
};

