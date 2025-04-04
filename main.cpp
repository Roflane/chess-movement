#define LOG(...) std::cout << __VA_ARGS__ << ' '
#define CIN(...) std::cin >> __VA_ARGS__;
#define ushort unsigned short
#include <iostream>

class Chess {
private:
	// Fields
	char _board[8][8];
public:
	Chess() : _board{} {}

	// Methods
	void fillBoard() {
		for (ushort i = 0; i < 8; ++i) {
			for (ushort j = 0; j < 8; ++j) {
				if (_board[i][j] == 0) {
					_board[i][j] = '0';
				}
			}
		}
	}

	void drawBoard() {
		system("cls");
		for (ushort i = 0; i < 8; ++i) {
			for (ushort j = 0; j < 8; ++j) {
				std::cout << _board[i][j] << ' ';
			}
			std::cout << '\n';
		}
	}

	void spawnFigure(char figure, ushort row, ushort col) {
		_board[row][col] = figure;
	}

	void clear(ushort row, ushort col) {
		system("cls");
		_board[row][col] = '0';
	}
};

struct Pos {
	ushort col, row;
};

namespace MoveType {
	namespace Pawn {
		const ushort SINGLE = 1;
		const ushort DOUBLE = 2;
	}
	namespace Knight {
		const ushort TOPLEFT = 1;
		const ushort TOPRIGHT = 2;
		const ushort BOTTOMLEFT = 3;
		const ushort BOTTOMRIGHT = 4;
	}
	namespace Bishop {
		const ushort TOPLEFT = 1;
		const ushort TOPRIGHT = 2;
		const ushort BOTTOMLEFT = 3;
		const ushort BOTTOMRIGHT = 4;
	}
	namespace Rook {
		const ushort FORWARD = 1;
		const ushort BACK = 2;
		const ushort LEFT = 3;
		const ushort RIGHT = 4;
	}
	namespace King {
		const ushort FORWARD = 1;
		const ushort BACK = 2;
		const ushort LEFT = 3;
		const ushort RIGHT = 4;
		const ushort TOPLEFT = 5;
		const ushort TOPRIGHT = 6;
		const ushort BOTTOMLEFT = 7;
		const ushort BOTTOMRIGHT = 8;
	}
	namespace Queen {
		const ushort SFORWARD = 1;
		const ushort SBACK = 2;
		const ushort SLEFT = 3;
		const ushort SRIGHT = 4;
		const ushort STOPLEFT = 5;
		const ushort STOPRIGHT = 6;
		const ushort SBOTTOMLEFT = 7;
		const ushort SBOTTOMRIGHT = 8;
	}
}

class Pawn {
protected:
	// Fields
	Pos _pos;
	char _figure;
public:
	Pawn(char figure, Pos pos) : _figure(figure), _pos(pos) {}

	// Properties
	char getFigure() const { return _figure; }
	auto getRow() const -> decltype(_pos.row) { return _pos.row; }
	auto getCol() const -> decltype(_pos.col) { return _pos.col; }

	// Methods
	virtual void move(ushort moveType) {
		switch (moveType) {
		case MoveType::Pawn::SINGLE:
			if (_pos.row > 0) _pos.row -= 1;
			break;
		case MoveType::Pawn::DOUBLE:
			if (_pos.row < 6) _pos.row -= 2;
			break;
		}
	}

	virtual void move(ushort moveType, ushort steps) {}
};

class Knight : public Pawn {
public:
	Knight(char figure, Pos pos) : Pawn(figure, pos) {}

	void move(ushort moveType) override {
		switch (moveType) {
		case MoveType::Knight::TOPLEFT:
			if (_pos.row > 1 && _pos.col > 0) { _pos.row -= 2; _pos.col -= 1; }
			break;
		case MoveType::Knight::TOPRIGHT:
			if (_pos.row > 1 && _pos.col < 7) { _pos.row -= 2; _pos.col += 1; }
			break;
		case MoveType::Knight::BOTTOMLEFT:
			if (_pos.row < 6 && _pos.col > 0) { _pos.row += 2; _pos.col -= 1; }
			break;
		case MoveType::Knight::BOTTOMRIGHT:
			if (_pos.row < 6 && _pos.col < 7) { _pos.row += 2; _pos.col += 1; }
			break;
		}
	}
};

class Bishop : public Pawn {
public:
	Bishop(char figure, Pos pos) : Pawn(figure, pos) {}

	void move(ushort moveType, ushort steps) override {
		switch (moveType) {
		case MoveType::Bishop::TOPLEFT:
			if (_pos.row >= steps && _pos.col >= steps) { _pos.row -= steps; _pos.col -= steps; }
			break;
		case MoveType::Bishop::TOPRIGHT:
			if (_pos.row >= steps && _pos.col + steps <= 7) { _pos.row -= steps; _pos.col += steps; }
			break;
		case MoveType::Bishop::BOTTOMLEFT:
			if (_pos.row + steps <= 7 && _pos.col >= steps) { _pos.row += steps; _pos.col -= steps; }
			break;
		case MoveType::Bishop::BOTTOMRIGHT:
			if (_pos.row + steps <= 7 && _pos.col + steps <= 7) { _pos.row += steps; _pos.col += steps; }
			break;
		}
	}
};

class Rook : public Pawn {
public:
	Rook(char figure, Pos pos) : Pawn(figure, pos) {}

	void move(ushort moveType, ushort steps) override {
		switch (moveType) {
		case MoveType::Rook::FORWARD:
			if (_pos.row >= steps) _pos.row -= steps;
			break;
		case MoveType::Rook::BACK:
			if (_pos.row + steps <= 7) _pos.row += steps;
			break;
		case MoveType::Rook::LEFT:
			if (_pos.col >= steps) _pos.col -= steps;
			break;
		case MoveType::Rook::RIGHT:
			if (_pos.col + steps <= 7) _pos.col += steps;
			break;
		}
	}
};

class King : public Pawn {
public:
	King(char figure, Pos pos) : Pawn(figure, pos) {}

	void move(ushort moveType, ushort steps) override {
		switch (moveType) {
		case MoveType::King::FORWARD:
			if (_pos.row > 0) _pos.row -= 1;
			break;
		case MoveType::King::BACK:
			if (_pos.row < 7) _pos.row += 1;
			break;
		case MoveType::King::LEFT:
			if (_pos.col > 0) _pos.col -= 1;
			break;
		case MoveType::King::RIGHT:
			if (_pos.col < 7) _pos.col += 1;
			break;
		case MoveType::King::TOPLEFT:
			if (_pos.row > 0 && _pos.col > 0) { _pos.row -= 1; _pos.col -= 1; }
			break;
		case MoveType::King::TOPRIGHT:
			if (_pos.row > 0 && _pos.col < 7) { _pos.row -= 1; _pos.col += 1; }
			break;
		case MoveType::King::BOTTOMLEFT:
			if (_pos.row < 7 && _pos.col > 0) { _pos.row += 1; _pos.col -= 1; }
			break;
		case MoveType::King::BOTTOMRIGHT:
			if (_pos.row < 7 && _pos.col < 7) { _pos.row += 1; _pos.col += 1; }
			break;
		}
	}
};

class Queen : public Pawn {
public:
	Queen(char figure, Pos pos) : Pawn(figure, pos) {}

	void move(ushort moveType) override {
		switch (moveType) {
		case MoveType::Queen::SFORWARD: _pos.row -= 1; break;
		case MoveType::Queen::SBACK: _pos.row += 1;    break;
		case MoveType::Queen::SLEFT: _pos.col -= 1;    break;
		case MoveType::Queen::SRIGHT: _pos.col += 1;   break;
		case MoveType::Queen::STOPLEFT: _pos.row -= 1; _pos.col -= 1;     break;
		case MoveType::Queen::STOPRIGHT: _pos.row -= 1; _pos.col += 1;	  break;
		case MoveType::Queen::SBOTTOMLEFT: _pos.row += 1; _pos.col -= 1;  break;
		case MoveType::Queen::SBOTTOMRIGHT: _pos.row += 1; _pos.col += 1; break;
		}
	}
};

int main() {
	ushort col = 4, row = 4;
	Pos startPos{ col, row };

	Pawn   pawn('P', Pos(startPos.col, startPos.row));
	Knight knight('K', Pos(startPos.col, startPos.row));
	Bishop bishop('B', Pos(startPos.col, startPos.row));
	Rook   rook('R', Pos(startPos.col, startPos.row));
	King   king('I', Pos(startPos.col, startPos.row));
	Queen  queen('Q', Pos(startPos.col, startPos.row));

	Chess chess;
	chess.fillBoard();

	LOG("Choose one of the following pieces: Pawn (1), Knight (2), Bishop (3), Rook (4), King (5), Queen (6) -");
	while (true) {
		Pawn *currentPiece = nullptr;
		ushort pieceSelect, pawnDir;
		CIN(pieceSelect);

		switch (pieceSelect) {
		case 1:
			currentPiece = &pawn;
			chess.spawnFigure(currentPiece->getFigure(), currentPiece->getRow(), currentPiece->getCol());
			chess.drawBoard();

			LOG("Choose pawn direction: forward by 1 cell (1), forward by 2 cell (2) -");
			CIN(pawnDir);

			if (pawnDir > 0) { chess.clear(currentPiece->getRow(), currentPiece->getCol()); }
			switch (pawnDir) {
			case 1: currentPiece->move(MoveType::Pawn::SINGLE); break;
			case 2: currentPiece->move(MoveType::Pawn::DOUBLE); break;
			}

			chess.spawnFigure(currentPiece->getFigure(), currentPiece->getRow(), currentPiece->getCol());
			chess.drawBoard();
			break;
		case 2:
			currentPiece = &knight;
			chess.spawnFigure(currentPiece->getFigure(), currentPiece->getRow(), currentPiece->getCol());
			chess.drawBoard();

			LOG("Choose knight direction: topleft (1), topright (2), bottomleft (3), bottomright (4) -");
			CIN(pawnDir);

			if (pawnDir > 0) { chess.clear(currentPiece->getRow(), currentPiece->getCol()); }
			switch (pawnDir) {
			case 1: currentPiece->move(MoveType::Knight::TOPLEFT);     break;
			case 2: currentPiece->move(MoveType::Knight::TOPRIGHT);    break;
			case 3: currentPiece->move(MoveType::Knight::BOTTOMLEFT);  break;
			case 4: currentPiece->move(MoveType::Knight::BOTTOMRIGHT); break;
			}
			chess.spawnFigure(currentPiece->getFigure(), currentPiece->getRow(), currentPiece->getCol());
			chess.drawBoard();
			break;
		case 3:
			currentPiece = &bishop;
			chess.spawnFigure(currentPiece->getFigure(), currentPiece->getRow(), currentPiece->getCol());
			chess.drawBoard();

			LOG("Choose bishop direction: toptopleft (1), topright (2), bottomleft (3), bottomright (4) -");
			CIN(pawnDir);

			if (pawnDir > 0) { chess.clear(currentPiece->getRow(), currentPiece->getCol()); }
			switch (pawnDir) {
			case 1: currentPiece->move(MoveType::Bishop::TOPLEFT, 1);     break;
			case 2: currentPiece->move(MoveType::Bishop::TOPRIGHT, 1);    break;
			case 3: currentPiece->move(MoveType::Bishop::BOTTOMLEFT, 1);  break;
			case 4: currentPiece->move(MoveType::Bishop::BOTTOMRIGHT, 1); break;
			}
			chess.spawnFigure(currentPiece->getFigure(), currentPiece->getRow(), currentPiece->getCol());
			chess.drawBoard();
			break;
		case 4:
			currentPiece = &rook;
			chess.spawnFigure(currentPiece->getFigure(), currentPiece->getRow(), currentPiece->getCol());
			chess.drawBoard();

			LOG("Choose rook direction: forward (1), back (2), left (3), right (4) -");
			CIN(pawnDir);

			if (pawnDir > 0) { chess.clear(currentPiece->getRow(), currentPiece->getCol()); }
			switch (pawnDir) {
			case 1: currentPiece->move(MoveType::Rook::FORWARD, 3); break;
			case 2: currentPiece->move(MoveType::Rook::BACK, 3);    break;
			case 3: currentPiece->move(MoveType::Rook::LEFT, 3);    break;
			case 4: currentPiece->move(MoveType::Rook::RIGHT, 3);   break;
			}
			chess.spawnFigure(currentPiece->getFigure(), currentPiece->getRow(), currentPiece->getCol());
			chess.drawBoard();
			break;
		case 5:
			currentPiece = &king;
			chess.spawnFigure(currentPiece->getFigure(), currentPiece->getRow(), currentPiece->getCol());
			chess.drawBoard();

			LOG("Choose king direction: forward (1), back (2), left (3), right (4), toptopleft (5), topright (6), bottomleft (7), bottomright (8) -");
			CIN(pawnDir);

			if (pawnDir > 0) { chess.clear(currentPiece->getRow(), currentPiece->getCol()); }
			switch (pawnDir) {
			case 1: currentPiece->move(MoveType::King::FORWARD, 1);     break;
			case 2: currentPiece->move(MoveType::King::BACK, 1);        break;
			case 3: currentPiece->move(MoveType::King::LEFT, 1);        break;
			case 4: currentPiece->move(MoveType::King::RIGHT, 1);       break;
			case 5: currentPiece->move(MoveType::King::TOPLEFT, 1);     break;
			case 6: currentPiece->move(MoveType::King::TOPRIGHT, 1);    break;
			case 7: currentPiece->move(MoveType::King::BOTTOMLEFT, 1);  break;
			case 8: currentPiece->move(MoveType::King::BOTTOMRIGHT, 1); break;
			}
			chess.spawnFigure(currentPiece->getFigure(), currentPiece->getRow(), currentPiece->getCol());
			chess.drawBoard();
			break;
		case 6:
			currentPiece = &queen;
			chess.spawnFigure(currentPiece->getFigure(), currentPiece->getRow(), currentPiece->getCol());
			chess.drawBoard();

			LOG("Choose queen direction: forward (1), back (2), left (3), right (4), toptopleft (5), topright (6), bottomleft (7), bottomright (8) -");
			CIN(pawnDir);

			if (pawnDir > 0) { chess.clear(currentPiece->getRow(), currentPiece->getCol()); }
			switch (pawnDir) {
			case 1: currentPiece->move(MoveType::Queen::SFORWARD);    break;
			case 2: currentPiece->move(MoveType::Queen::SBACK);        break;
			case 3: currentPiece->move(MoveType::Queen::SLEFT);        break;
			case 4: currentPiece->move(MoveType::Queen::SRIGHT);       break;
			case 5: currentPiece->move(MoveType::Queen::STOPLEFT);     break;
			case 6: currentPiece->move(MoveType::Queen::STOPRIGHT);    break;
			case 7: currentPiece->move(MoveType::Queen::SBOTTOMLEFT);  break;
			case 8: currentPiece->move(MoveType::Queen::SBOTTOMRIGHT); break;
			}
			chess.spawnFigure(currentPiece->getFigure(), currentPiece->getRow(), currentPiece->getCol());
			chess.drawBoard();
			break;
		}
	}
}
