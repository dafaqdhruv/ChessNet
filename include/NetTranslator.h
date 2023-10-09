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

	GetStatus,//0
	Ping,
	YourTurn, //2

	Client_Accepted,
	Client_AssignID,//4
	Client_Verify,
	Client_RegisterWithServer,//6
	Client_UnregisterWithServer,

	Game_BeginGame,//8
	Game_EndGame,
	Game_UpdatePlayer	//10
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
