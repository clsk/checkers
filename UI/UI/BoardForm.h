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
			//
			//TODO: Add the constructor code here
			//
			Game::instance().create_board();

			Game::instance().create_pieces();
			loadPieces();
			Board& board = Game::instance().get_board();
			board.print();
			cout << endl;
		}

		void loadPieces()
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(BoardForm::typeid));
			Board& board = Game::instance().get_board();
			for (int y = 0; y < 8; y++) {
				for (int x = 0; x < 8; x += 2) {
					int xi = x;
					if (y % 2 > 0)
						xi = x+1;
					Piece* piece = board.get_node(::Point(xi,y))->piece;
					if (piece != nullptr)
					{
						if (piece->color == Piece::Red) {
							PictureBox^ pb = gcnew PictureBox();
							pb->BackColor = System::Drawing::Color::Transparent;
							pb->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pbRedPiece.Image")));
							//pb->Location = System::Drawing::Point((x*58)+13, (y*58)+13);
							pb->Name = L"pbRedPiece"+x.ToString() + "_" + y.ToString();
							pb->Size = System::Drawing::Size(52, 52);
							pb->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
							pb->Visible = true;
							this->tplBoard->Controls->Add(pb, xi + 1, y + 1);
						}
						else if (piece->color == Piece::Black) {
						}
					}
				}
			}
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
	private: System::Windows::Forms::PictureBox^  pbRedPiece;


	private:
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
			this->pbRedPiece = (gcnew System::Windows::Forms::PictureBox());
			this->tplBoard->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbRedPiece))->BeginInit();
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
			this->tplBoard->Controls->Add(this->pbRedPiece, 5, 5);
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
			// pbRedPiece
			// 
			this->pbRedPiece->BackColor = System::Drawing::Color::Transparent;
			this->pbRedPiece->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pbRedPiece.Image")));
			this->pbRedPiece->Location = System::Drawing::Point(248, 250);
			this->pbRedPiece->Name = L"pbRedPiece";
			this->pbRedPiece->Size = System::Drawing::Size(52, 52);
			this->pbRedPiece->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pbRedPiece->TabIndex = 0;
			this->pbRedPiece->TabStop = false;
			// 
			// BoardForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(753, 558);
			this->Controls->Add(this->tplBoard);
			this->Name = L"BoardForm";
			this->Text = L"BoardForm";
			this->tplBoard->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbRedPiece))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion


private: System::Void tplBoard_MouseClick(System::Object^  sender, System::Windows::Forms::MouseEventArgs^  e) {
			 int x = -1;
			 if (e->X > 13 && e->X < 477)
			 {
				 x = (e->X - 13) / 58;
			 }

			 int y = -1;
			 if (e->Y > 13 && e->Y < 477)
			 {
				 y = (e->Y-13) / 58;
			 }

			 MessageBox::Show("(" + x + "," + y + ")");

			 if (x == 5 && y == 5)
			 {
				 this->tplBoard->Controls->Remove(pbRedPiece);
				 this->tplBoard->Controls->Add(pbRedPiece, 5, 6);
			 }
}
};
}
