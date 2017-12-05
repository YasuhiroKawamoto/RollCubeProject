#pragma once
class TurnManager
{
public:
	enum TurnID
	{
		PLAYER_MOVE,
		PLAYER_ACTION,
		ENEMY_MOVE,
		ENEMY_ACTION,

		ALL_TURNS
	};
	void ChangeTurn(TurnID turn) { m_turn = turn; }
	TurnID GetTurn() { return m_turn; }
	~TurnManager(){}
public :
	static TurnManager* GetInstance();
private:
	TurnManager();
private:
	TurnID m_turn;
private:
	static TurnManager* s_instance;

};

