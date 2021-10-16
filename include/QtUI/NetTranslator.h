// enum class PieceOwner : uint32_t
// {
// 	White,
// 	Black
// };

// enum class Pieces : uint32_t
// {
// 	King,
// 	Queen,
// 	Rook,
// 	Bishop,
// 	Knight,
// 	Pawn
// };

enum class GameMessage : uint32_t
{
	
	GetStatus,
	Ping,
	YourTurn,
	
	Client_Accepted,
	Client_AssignID,
	Client_Verify,
	Client_RegisterWithServer,
	Client_UnregisterWithServer,

	Game_BeginGame,
	Game_EndGame,
	Game_UpdatePlayer	
};

// struct PieceMove {
	
// 	Pieces PieceType;
// 	pos To;
// 	pos From;
// };
	
// struct PlayerDescription
// {
// 	uint32_t UniqueID = 0;
// 	uint32_t Affiliation = 0;

// 	uint32_t PiecesAlive = 16;
// };

