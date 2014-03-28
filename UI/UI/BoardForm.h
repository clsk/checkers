#pragma once
#include "../../Game.h"
#include <iostream>

using std::cout;
using std::endl;
namespace UI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for BoardForm
	/// </summary>
	public ref class BoardForm : public System::Windows::Forms::Form
	{
	public:
		BoardForm(void)
		{
			InitializeComponent();
			Game::instance().create_board();
			Game::instance().create_pieces();

			loadPieces();
		}

		void loadPieces()
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(BoardForm::typeid));
			Piece **redPieces = Game::instance().red_pieces;
			Piece **blackPieces = Game::instance().black_pieces;

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
			 Game::instance().get_board().move_piece(::Point(from.X, from.Y), ::Point(to.X, to.Y));
			 pbSelected->Tag = to;
			 pbSelected->BackColor = Color::Transparent;
			 tplBoard->Controls->Remove(pbSelected);
			 tplBoard->Controls->Add(pbSelected, to.X + 1, to.Y + 1);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
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
		std::pair<Node*, Node*>*possibleMoves = nullptr;
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
				 pb->BackColor = Color::Aqua;
				 pbSelected = pb;
				 Piece *piece = Game::instance().get_board().get_piece(::Point(point.X, point.Y));
				 Game::TreeNodePtr treeNode = Game::instance().possible_jumps(piece, 1);
				 if (treeNode->left == nullptr && treeNode->right == nullptr)
					 possibleMoves = new std::pair<Node*, Node*>(Game::instance().possible_moves(piece));
				 else
				 {
					 if (treeNode->left != nullptr)
						 MessageBox::Show("1. possible jump (" + treeNode->left->pos->pos.x + "," + treeNode->left->pos->pos.y + ")");
					 else if (treeNode->right != nullptr)
					 {
						 MessageBox::Show("1. possible jump (" + treeNode->right->pos->pos.x + "," + treeNode->right->pos->pos.y + ")");
					 }
				 }
			 }
			 else if (pb == pbSelected)
			 {
				 pb->BackColor = Color::Transparent;
				 pbSelected = nullptr;
				 if (possibleMoves != nullptr)
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
			 int x = -1;
			 if (e->X > 13 && e->X < 477)
			 {
				 x = (e->X - 13) / 58;
			 }
			 else
				 return;

			 int y = -1;
			 if (e->Y > 13 && e->Y < 477)
			 {
				 y = (e->Y - 13) / 58;
			 }
			 else
				 return;

			 if (possibleMoves != nullptr)
			 {
				 if ((possibleMoves->first != nullptr && possibleMoves->first->pos.x == x && possibleMoves->first->pos.y == y) ||
					 (possibleMoves->second != nullptr && possibleMoves->second->pos.x == x && possibleMoves->second->pos.y == y) )
				 {
					 System::Drawing::Point from = (System::Drawing::Point)pbSelected->Tag;
					 movePiece(from, System::Drawing::Point(x, y));
					 pbSelected = nullptr;
					 delete possibleMoves;
					 possibleMoves = nullptr;
				 }
			 }
			 //MessageBox::Show("(" + x + "," + y + ")");
}
};
}
