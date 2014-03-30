#pragma once
#include "../../Board.h"
#include <iostream>

#define BOARD_MARGIN 13
#define SQUARE_DIMENSIONS 58 // 58x58

using std::cout;
using std::endl;
namespace UI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	public ref class BoardForm : public System::Windows::Forms::Form
	{
		bool myTurn = false;
	public:
		BoardForm(void)
		{
			InitializeComponent();
			Board::getInstance().create_pieces();

			loadPieces();
		}

		void loadPieces()
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(BoardForm::typeid));
			Piece **redPieces = Board::getInstance().red_pieces;
			Piece **blackPieces = Board::getInstance().black_pieces;

			for (int i = 0; i < PIECES_COUNT; i++)
			{
				// red piece
				PictureBox^ pb = gcnew PictureBox();
				pb->BackColor = System::Drawing::Color::Transparent;
				pb->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"red")));
				pb->Size = System::Drawing::Size(52, 52);
				pb->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
				pb->Visible = true;
				pb->Tag = System::Drawing::Point(redPieces[i]->location->pos.x, redPieces[i]->location->pos.y);
				this->tplBoard->Controls->Add(pb, redPieces[i]->location->pos.x + 1, redPieces[i]->location->pos.y + 1);			
				pb->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &BoardForm::piece_MouseClick);

				// black piece
				pb = gcnew PictureBox();
				pb->BackColor = System::Drawing::Color::Transparent;
				pb->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"black")));
				pb->Size = System::Drawing::Size(52, 52);
				pb->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
				pb->Visible = true;
				pb->Tag = System::Drawing::Point(blackPieces[i]->location->pos.x, blackPieces[i]->location->pos.y);
				this->tplBoard->Controls->Add(pb, blackPieces[i]->location->pos.x + 1, blackPieces[i]->location->pos.y + 1);			
				pb->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &BoardForm::piece_MouseClick);
			}

		}

		void movePiece(System::Drawing::Point from, System::Drawing::Point to)
		{
			 Board::getInstance().move_piece(::Point(from.X, from.Y), ::Point(to.X, to.Y));
			 pbSelected->Tag = to;
			 pbSelected->BackColor = Color::Transparent;
			 tplBoard->Controls->Remove(pbSelected);
			 tplBoard->Controls->Add(pbSelected, to.X + 1, to.Y + 1);
		}

		void crownIfNeeded(PictureBox^ pb, int x, int y)
		{
			 if (y == 7 || y == 0)
			 {
				 Piece *piece = Board::getInstance().get_piece(::Point(x, y));
				 if (!piece->is_king)
				 {
					 Board::getInstance().crown_piece(piece);
					 System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(BoardForm::typeid));
					 pb->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(piece->color == Piece::Color::Red ? L"red_king" : L"black_king")));
				 }
			 }
		}

	protected:
		~BoardForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TableLayoutPanel^  tplBoard;



	private:
		PictureBox^ pbSelected = nullptr;
		std::pair<Board::NodePair, Board::NodePair>*possibleMoves = nullptr;
		Board::TreeNodePtr* possibleJumps = nullptr;
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(BoardForm::typeid));
			this->tplBoard = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->SuspendLayout();
			// 
			// tplBoard
			// 
			this->tplBoard->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"tplBoard.BackgroundImage")));
			this->tplBoard->ColumnCount = 10;
			this->tplBoard->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 13)));
			this->tplBoard->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 58)));
			this->tplBoard->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 58)));
			this->tplBoard->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 58)));
			this->tplBoard->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 58)));
			this->tplBoard->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 58)));
			this->tplBoard->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 58)));
			this->tplBoard->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 58)));
			this->tplBoard->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 58)));
			this->tplBoard->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Absolute, 13)));
			this->tplBoard->Location = System::Drawing::Point(109, 31);
			this->tplBoard->Name = L"tplBoard";
			this->tplBoard->RowCount = 10;
			this->tplBoard->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 15)));
			this->tplBoard->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 58)));
			this->tplBoard->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 58)));
			this->tplBoard->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 58)));
			this->tplBoard->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 58)));
			this->tplBoard->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 58)));
			this->tplBoard->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 58)));
			this->tplBoard->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 58)));
			this->tplBoard->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 58)));
			this->tplBoard->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Absolute, 13)));
			this->tplBoard->Size = System::Drawing::Size(490, 493);
			this->tplBoard->TabIndex = 0;
			this->tplBoard->MouseClick += gcnew System::Windows::Forms::MouseEventHandler(this, &BoardForm::tplBoard_MouseClick);
			// 
			// BoardForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(753, 558);
			this->Controls->Add(this->tplBoard);
			this->Name = L"BoardForm";
			this->Text = L"BoardForm";
			this->ResumeLayout(false);

		}
#pragma endregion


private: System::Void piece_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 PictureBox^ pb = (PictureBox^)sender;
			 System::Drawing::Point point = (System::Drawing::Point)pb->Tag;
			 // MessageBox::Show("(" + point.X + "," + point.Y + ")");
			 if (pbSelected == nullptr)
			 {
				 // New piece selected
				 pb->BackColor = Color::Aqua;
				 pbSelected = pb;
				 Piece *piece = Board::getInstance().get_piece(::Point(point.X, point.Y));
				 Board::TreeNodePtr treeNode = Board::getInstance().possible_jumps(piece, 1);
				 // If there are jumps to make, dont worry about possible moves
				 if (treeNode->left != nullptr || treeNode->right != nullptr)
					 possibleJumps = new Board::TreeNodePtr(treeNode);
				 else
					 possibleMoves = new std::pair<Board::NodePair, Board::NodePair>(Board::getInstance().possible_moves(piece));
			 }
			 else if (pb == pbSelected)
			 {
				 // Unselect
				 pb->BackColor = Color::Transparent;
				 pbSelected = nullptr;
				 if (possibleJumps != nullptr)
				 {
					 delete possibleJumps;
					 possibleJumps = nullptr;
				 }
				 else
				 {
					 delete possibleMoves;
					 possibleMoves = nullptr;
				 }
			 }
			 else 
			 {

			 }
}
private: System::Void tplBoard_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 // Get Board position based on click position
			 int x = -1;
			 if (e->X > BOARD_MARGIN && e->X < (SQUARE_DIMENSIONS*8) + BOARD_MARGIN)
			 {
				 x = (e->X - BOARD_MARGIN) / SQUARE_DIMENSIONS;
			 }
			 else
				 return;

			 int y = -1;
			 if (e->Y > BOARD_MARGIN && e->Y < (SQUARE_DIMENSIONS*8) + BOARD_MARGIN)
			 {
				 y = (e->Y - BOARD_MARGIN) / SQUARE_DIMENSIONS;
			 }
			 else
				 return;

			 // User should be attempting a kill because there are jumps to make
			 if (possibleJumps != nullptr)
			 {
				 Board::TreeNodePtr newPos = nullptr;
				 if (possibleJumps->get()->left != nullptr && possibleJumps->get()->left->pos->pos.x == x && possibleJumps->get()->left->pos->pos.y == y)
				 {
					 newPos = possibleJumps->get()->left;
				 }
				 else if (possibleJumps->get()->right != nullptr && possibleJumps->get()->right->pos->pos.x == x && possibleJumps->get()->right->pos->pos.y == y)
				 {
					 newPos = possibleJumps->get()->right;
				 }

				 if (newPos != nullptr)
				 {
					 // delete killed piece
					 Board::getInstance().remove_piece(newPos->killed->piece);
					 tplBoard->Controls->Remove(tplBoard->GetControlFromPosition(newPos->killed->pos.x + 1, newPos->killed->pos.y + 1));

					 // Move to new place
					 System::Drawing::Point from = (System::Drawing::Point)pbSelected->Tag;
					 movePiece(from, System::Drawing::Point(x, y));
					 // delete possibleJumps
					 delete possibleJumps;
					 possibleJumps = nullptr;
					 
					 crownIfNeeded(pbSelected, x, y);
					 // if there are more jumps to make, select piece again
					 Board::TreeNodePtr treeNode = Board::getInstance().possible_jumps(Board::getInstance().get_piece(::Point(x,y)), 1);
					 if (treeNode->left != nullptr || treeNode->right != nullptr)
					 {
						 // select piece again
						 pbSelected->BackColor = Color::Aqua;
						 possibleJumps = new Board::TreeNodePtr(treeNode);
					 }
					 else
					 {
						 pbSelected = nullptr;
					 }
				 }
			 }
			 else if (possibleMoves != nullptr)
			 {
				 if ((possibleMoves->first.first != nullptr && possibleMoves->first.first->pos.x == x && possibleMoves->first.first->pos.y == y) ||
					 (possibleMoves->first.second != nullptr && possibleMoves->first.second->pos.x == x && possibleMoves->first.second->pos.y == y) ||
					 (possibleMoves->second.first != nullptr && possibleMoves->second.first->pos.x == x && possibleMoves->second.first->pos.y == y) ||
					 (possibleMoves->second.second != nullptr && possibleMoves->second.second->pos.x == x && possibleMoves->second.second->pos.y == y) )

				 {
					 System::Drawing::Point from = (System::Drawing::Point)pbSelected->Tag;
					 movePiece(from, System::Drawing::Point(x, y));
					 crownIfNeeded(pbSelected, x, y);
					 pbSelected = nullptr;
					 delete possibleMoves;
					 possibleMoves = nullptr;
				 }
			 }
}
};
}
