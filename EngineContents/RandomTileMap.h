#pragma once
#include <EngineCore/GameMode.h>

const int WIDTH = 50;
const int HEIGHT = 50;
const int MIN_ROOM_SIZE = 5;
const int MAX_ROOM_SIZE = 10;

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

	bool Intersects(const FRoom& _Other) const
	{
		return !(X + Width <= _Other.X || X >= _Other.X + _Other.Width || Y + Height <= _Other.Y || Y >= _Other.Y + _Other.Height);
	}
};

struct FRoomNode
{
	FRoom Room;

	FRoomNode* _Left = nullptr;
	FRoomNode* _Right = nullptr;
};

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

	void PrintMap(const std::vector<std::vector<ETileType>>& _Map);


protected:
	void LevelChangeStart() override;

private:

	std::shared_ptr<class UTileMapWindow> TileMapWindow;

	std::shared_ptr<class USpriteRenderer> PivotSpriteRenderer;

	std::shared_ptr<class UTileMapRenderer> TileMapRenderer;
};

