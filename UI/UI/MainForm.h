#pragma once
#include "BoardForm.h"
#include "AI.h"
#include "AIMedium.h"
#include "AIHard.h"
namespace UI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//

		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btEasy;
	private: System::Windows::Forms::Button^  btMedium;
	private: System::Windows::Forms::Button^  btHard;
	private: System::Windows::Forms::Button^  btOnline;
	protected:

	protected:

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
			this->btEasy = (gcnew System::Windows::Forms::Button());
			this->btMedium = (gcnew System::Windows::Forms::Button());
			this->btHard = (gcnew System::Windows::Forms::Button());
			this->btOnline = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// btEasy
			// 
			this->btEasy->Location = System::Drawing::Point(79, 12);
			this->btEasy->Name = L"btEasy";
			this->btEasy->Size = System::Drawing::Size(119, 49);
			this->btEasy->TabIndex = 0;
			this->btEasy->Text = L"Easy";
			this->btEasy->UseVisualStyleBackColor = true;
			this->btEasy->Click += gcnew System::EventHandler(this, &MainForm::btEasy_Click);
			// 
			// btMedium
			// 
			this->btMedium->Location = System::Drawing::Point(79, 67);
			this->btMedium->Name = L"btMedium";
			this->btMedium->Size = System::Drawing::Size(119, 49);
			this->btMedium->TabIndex = 1;
			this->btMedium->Text = L"Medium";
			this->btMedium->UseVisualStyleBackColor = true;
			this->btMedium->Click += gcnew System::EventHandler(this, &MainForm::btMedium_Click);
			// 
			// btHard
			// 
			this->btHard->Location = System::Drawing::Point(79, 122);
			this->btHard->Name = L"btHard";
			this->btHard->Size = System::Drawing::Size(119, 49);
			this->btHard->TabIndex = 2;
			this->btHard->Text = L"Hard";
			this->btHard->UseVisualStyleBackColor = true;
			this->btHard->Click += gcnew System::EventHandler(this, &MainForm::btHard_Click);
			// 
			// btOnline
			// 
			this->btOnline->Location = System::Drawing::Point(79, 177);
			this->btOnline->Name = L"btOnline";
			this->btOnline->Size = System::Drawing::Size(119, 49);
			this->btOnline->TabIndex = 3;
			this->btOnline->Text = L"Play Online!";
			this->btOnline->UseVisualStyleBackColor = true;
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 247);
			this->Controls->Add(this->btOnline);
			this->Controls->Add(this->btHard);
			this->Controls->Add(this->btMedium);
			this->Controls->Add(this->btEasy);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void btEasy_Click(System::Object^  sender, System::EventArgs^  e) {
			UI::BoardForm^ boardForm = gcnew UI::BoardForm(Piece::Color::Red);
			AI^ ai = gcnew AI(Piece::Color::Black, boardForm);
			boardForm->myEnemy = ai;
			boardForm->Show();
			boardForm->play();
	}
private: System::Void btMedium_Click(System::Object^  sender, System::EventArgs^  e) {
			UI::BoardForm^ boardForm = gcnew UI::BoardForm(Piece::Color::Red);
			AI^ ai = gcnew AIMedium(Piece::Color::Black, boardForm);
			boardForm->myEnemy = ai;
			boardForm->Show();
			boardForm->play();
}
private: System::Void btHard_Click(System::Object^  sender, System::EventArgs^  e) {
			UI::BoardForm^ boardForm = gcnew UI::BoardForm(Piece::Color::Red);
			AI^ ai = gcnew AIHard(Piece::Color::Black, boardForm, 7);
			boardForm->myEnemy = ai;
			boardForm->Show();
			boardForm->play();
}
};
}
