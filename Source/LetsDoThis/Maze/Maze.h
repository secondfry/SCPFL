#pragma once

#include "Array.h"
#include "Room.h"
#include "RoomDataStruct.h"
#include <map>
#include <random>

class Maze {
private:
  static std::mt19937 generator;
  static FString seed;
  static int roomDataVariantsCount;
  static std::map<int, const RoomData*> roomDataVariants;
  static std::map<int, std::map<int, Room*>> grid;
  static std::map<int, std::map<int, int>> heightMap;
  static std::map<int, std::map<int, int>> stateMap;
  static std::map<int, std::map<int, int>> costMap;
  static std::map<int, std::map<int, std::pair<int, int>>> jumpMap;
  static std::vector<FString> keyRooms;
  static int checksum;

public:
  static TArray<FRoomDataStruct>* GenerateMap(FString seed = Maze::GenerateSeed(), TArray<FString> requestedRooms = Maze::GetDefaultKeyRooms());
  static FString GenerateSeed();
  static TArray<FString> GetDefaultKeyRooms();
  static void InitChecksum();
  static void SeedRandom(FString seed = Maze::GenerateSeed());
  static void InitRoomLocations();
  static void InitRoomLocation(std::vector<DirectionVariant> dvs, Coordinates coords);
  static void ClearDataContainers();
  static void PlaceStart(FString name = "SPAWN_CLASSD");
  static void InitKeyRooms(TArray<FString> requestedRooms = { "CR_914", "CR_173" });
  static void PlaceAllKeyRooms();
  static Room* PlaceNextKeyRoom(Room* prevRoom, FString name);
  static RoomData* GetNextRoomData();
  static int RollNextRoom();
  static int RollRoomExit(int exits = 4);
  static int Roll(int min = 0, int max = 99);
  static bool IsNextRoomPlaceOccupied(Coordinates coords);
  static void CreateRoute(Room* prevRoom, Room* nextRoom);
  static void AddDirections(std::vector<std::pair<int, int>>& directions, std::pair<int, int> coords, int minX, int maxX, int minY, int maxY);
  static void AddDirectionsVertical(std::vector<std::pair<int, int>>& directions, std::pair<int, int> coords, int minY, int maxY);
  static void AddDirectionsHorizontal(std::vector<std::pair<int, int>>& directions, std::pair<int, int> coords, int minX, int maxX);
  static void SafeCreateCorridor(int x, int y);
  static TArray<FRoomDataStruct>* IterateGrid();
  static void AddGridExits(Room* room);
  static void CheckGridExit(Room* room, Direction dir);
  static void DeltaChecksum(Room* room);
  static bool VerifyChecksum();
  static FString GetSeed();
};

enum SearchState {
  checked,
  used,
  clean
};
