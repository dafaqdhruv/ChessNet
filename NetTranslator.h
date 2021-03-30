

enum class GamePieces : uint32_t
{
	King,
	Queen,
	Rook,
	Bishop,
	Knight,
	Pawn
}

enum class GameMessage : uint32_t
{
	
	Server_GetStatus,
	Server_GetPing,

	Client_Accepted,
	Client_AssignID,
	Client_RegisterWithServer,
	Client_UnregisterWithServer,

	Game_BeginGame,
	Game_EndGame,
	Game_UpdatePlayer,	
};

struct PieceMove {
	
	GamePieces PieceType;
	pos To;
	pos From;
};
	
struct PlayerDescription
{
	uint32_t UniqueID = 0;
	uint32_t Affiliation = 0;

	uint32_t PiecesAlive = 16;
};

