#pragma once

enum TileType {
	MOB,
	BLOCK,
	NPC,
	POTAL
};
struct Size {
	int width;
	int height;
};
struct Position {
	int x;
	int y;
};

struct Tile {
	int no;
	TileType type;
	Position pos;
};

class CMapData
{
public:
	CMapData(void);
	~CMapData(void);
	CMapData(std::string name, int width, int height);
	void setSize(Size size) {m_size = size;}
	Size getSize() {return m_size;}
	void addTile(int no, TileType type, int x, int y);
	Tile getTile(int index) {return m_tile[index];}
	Tile* getTiles() {return m_tile;}
private:
	std::string m_name;
	Tile m_tile[30];
	int m_tileCount;
	Size m_size;
};

