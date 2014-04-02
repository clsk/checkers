#pragma once
#include "../../Board.h"
#include "IEnemy.h"
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
		Piece::Color myColor = Piece::Color::Red;

	public:
		IEnemy^ myEnemy;
		BoardForm(Piece::Color color) : myColor(color)
		{
			InitializeComponent();
			Board::getInstance().create_pieces();

			loadPieces();
		}
		void play()
		{
			myTurn = true;
			if (Board::getInstance().has_possible_jumps(myColor))
				statusLabel->Text = "Make a jump";
			else
				statusLabel->Text = "Make a move";
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
			 PictureBox^ pb = (PictureBox^)tplBoard->GetControlFromPosition(from.X + 1, from.Y + 1);
			 Board::getInstance().move_piece(::Point(from.X, from.Y), ::Point(to.X, to.Y));
			 pb->Tag = to;
			 pb->BackColor = Color::Transparent;
			 tplBoard->Controls->Remove(pb);
			 tplBoard->Controls->Add(pb, to.X + 1, to.Y + 1);
		}

		void jumpPiece(System::Drawing::Point from, Board::TreeNodePtr nodePtr)
		{
			 // delete killed piece
			 Board::getInstance().remove_piece(nodePtr->killed->piece);
			 tplBoard->Controls->Remove(tplBoard->GetControlFromPosition(nodePtr->killed->pos.x + 1, nodePtr->killed->pos.y + 1));

			 // Move to new place
			 movePiece(from, System::Drawing::Point(nodePtr->pos->pos.x, nodePtr->pos->pos.y));
		}

		bool crownIfNeeded(int x, int y)
		{
			 if (y == 7 || y == 0)
			 {
				 Piece *piece = Board::getInstance().get_piece(::Point(x, y));
				 if (!piece->is_king)
				 {
					 PictureBox^ pb = (PictureBox^)tplBoard->GetControlFromPosition(x + 1, y + 1);
					 Board::getInstance().crown_piece(piece);
					 System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(BoardForm::typeid));
					 pb->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(piece->color == Piece::Color::Red ? L"red_king" : L"black_king")));
					 return true;
				 }
			 }

			 return false;
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
		Board::TreeNodePtr*possibleMoves = nullptr;
		Board::TreeNodePtr* possibleJumps = nullptr;
	private: System::Windows::Forms::StatusStrip^  statusStrip1;
	private: System::Windows::Forms::ToolStripStatusLabel^  statusLabel;
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
			this->statusStrip1 = (gcnew System::Windows::Forms::StatusStrip());
			this->statusLabel = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->statusStrip1->SuspendLayout();
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
			// statusStrip1
			// 
			this->statusStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) { this->statusLabel });
			this->statusStrip1->Location = System::Drawing::Point(0, 536);
			this->statusStrip1->Name = L"statusStrip1";
			this->statusStrip1->Size = System::Drawing::Size(753, 22);
			this->statusStrip1->TabIndex = 1;
			this->statusStrip1->Text = L"statusStrip1";
			// 
			// statusLabel
			// 
			this->statusLabel->Name = L"statusLabel";
			this->statusLabel->Size = System::Drawing::Size(57, 17);
			this->statusLabel->Text = L"Welcome";
			// 
			// BoardForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(753, 558);
			this->Controls->Add(this->statusStrip1);
			this->Controls->Add(this->tplBoard);
			this->Name = L"BoardForm";
			this->Text = L"BoardForm";
			this->statusStrip1->ResumeLayout(false);
			this->statusStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion


private: System::Void piece_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if (myTurn == false)
				 return;

			 PictureBox^ pb = (PictureBox^)sender;
			 System::Drawing::Point point = (System::Drawing::Point)pb->Tag;
			 Piece *piece = Board::getInstance().get_piece(::Point(point.X, point.Y));
			 if (piece->color != myColor)
				 return;

			 // MessageBox::Show("(" + point.X + "," + point.Y + ")");
			 if (pbSelected == nullptr)
			 {
				 // New piece selected
				 pb->BackColor = Color::Aqua;
				 pbSelected = pb;
				 Board::TreeNodePtr treeNode = Board::getInstance().possible_jumps(piece, 1);
				 // If there are jumps to make, dont worry about possible moves
				 if (treeNode->jumps[Node::TOP_LEFT] != nullptr || treeNode->jumps[Node::TOP_RIGHT] != nullptr ||
					 treeNode->jumps[Node::BOTTOM_LEFT] != nullptr || treeNode->jumps[Node::BOTTOM_RIGHT])
					 possibleJumps = new Board::TreeNodePtr(treeNode);
				 else
					 possibleMoves = new Board::TreeNodePtr(Board::getInstance().possible_moves(piece));
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
				 // Ignore this click
			 }
}
private: System::Void tplBoard_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 if (myTurn == false)
				 return;

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
				 if (possibleJumps->get()->jumps[Node::TOP_LEFT] != nullptr && possibleJumps->get()->jumps[Node::TOP_LEFT]->pos->pos.x == x && possibleJumps->get()->jumps[Node::TOP_LEFT]->pos->pos.y == y)
				 {
					 newPos = possibleJumps->get()->jumps[Node::TOP_LEFT];
				 }
				 else if (possibleJumps->get()->jumps[Node::TOP_RIGHT] != nullptr && possibleJumps->get()->jumps[Node::TOP_RIGHT]->pos->pos.x == x && possibleJumps->get()->jumps[Node::TOP_RIGHT]->pos->pos.y == y)
				 {
					 newPos = possibleJumps->get()->jumps[Node::TOP_RIGHT];
				 }
				 else if (possibleJumps->get()->jumps[Node::BOTTOM_LEFT] != nullptr && possibleJumps->get()->jumps[Node::BOTTOM_LEFT]->pos->pos.x == x && possibleJumps->get()->jumps[Node::BOTTOM_LEFT]->pos->pos.y == y)
				 {
					 newPos = possibleJumps->get()->jumps[Node::BOTTOM_LEFT];
				 }
				 else if (possibleJumps->get()->jumps[Node::BOTTOM_RIGHT] != nullptr && possibleJumps->get()->jumps[Node::BOTTOM_RIGHT]->pos->pos.x == x && possibleJumps->get()->jumps[Node::BOTTOM_RIGHT]->pos->pos.y == y)
				 {
					 newPos = possibleJumps->get()->jumps[Node::BOTTOM_RIGHT];
				 }

				 if (newPos != nullptr)
				 {
					 System::Drawing::Point from = (System::Drawing::Point)pbSelected->Tag;

					 jumpPiece(from, newPos);
					 // delete possibleJumps
					 delete possibleJumps;
					 possibleJumps = nullptr;
					 
					 bool crowned = crownIfNeeded(x, y);
					 // if there are more jumps to make, select piece again
					 Board::TreeNodePtr treeNode = Board::getInstance().possible_jumps(Board::getInstance().get_piece(::Point(x,y)), 1);
					 if (!crowned && (treeNode->jumps[Node::TOP_LEFT] != nullptr || treeNode->jumps[Node::TOP_RIGHT] != nullptr ||
						 treeNode->jumps[Node::BOTTOM_LEFT] != nullptr || treeNode->jumps[Node::BOTTOM_RIGHT]))
					 {
						 // select piece again
						 pbSelected->BackColor = Color::Aqua;
						 possibleJumps = new Board::TreeNodePtr(treeNode);
					 }
					 else
					 {
						 pbSelected = nullptr;
						 myTurn = false;
						 myEnemy->play();
					 }
				 }
			 }
			 else if (possibleMoves != nullptr)
			 {
				 if ((possibleMoves->get()->jumps[Node::TOP_LEFT] != nullptr && possibleMoves->get()->jumps[Node::TOP_LEFT]->pos->pos.x == x && possibleMoves->get()->jumps[Node::TOP_LEFT]->pos->pos.y == y) ||
					 (possibleMoves->get()->jumps[Node::TOP_RIGHT] != nullptr && possibleMoves->get()->jumps[Node::TOP_RIGHT]->pos->pos.x == x && possibleMoves->get()->jumps[Node::TOP_RIGHT]->pos->pos.y == y) ||
					 (possibleMoves->get()->jumps[Node::BOTTOM_LEFT] != nullptr && possibleMoves->get()->jumps[Node::BOTTOM_LEFT]->pos->pos.x == x && possibleMoves->get()->jumps[Node::BOTTOM_LEFT]->pos->pos.y == y) ||
					 (possibleMoves->get()->jumps[Node::BOTTOM_RIGHT] != nullptr && possibleMoves->get()->jumps[Node::BOTTOM_RIGHT]->pos->pos.x == x && possibleMoves->get()->jumps[Node::BOTTOM_RIGHT]->pos->pos.y == y))
				 {
					 System::Drawing::Point from = (System::Drawing::Point)pbSelected->Tag;
					 movePiece(from, System::Drawing::Point(x, y));
					 crownIfNeeded(x, y);
					 pbSelected = nullptr;
					 delete possibleMoves;
					 possibleMoves = nullptr;
					 myTurn = false;
					 myEnemy->play();
				 }
			 }
}
};
}
