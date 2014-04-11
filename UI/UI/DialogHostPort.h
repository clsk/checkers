#pragma once

namespace UI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for DialogHostPort
	/// </summary>
	public ref class DialogHostPort : public System::Windows::Forms::Form
	{
	public:
		String^ hostname;
		String^ port;

		DialogHostPort(void)
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
		~DialogHostPort()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  button2;
	private: System::Windows::Forms::Label^  lblHostname;
	private: System::Windows::Forms::Label^  lblPort;
	private: System::Windows::Forms::TextBox^  tbHostname;
	private: System::Windows::Forms::TextBox^  tbPort;
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
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->lblHostname = (gcnew System::Windows::Forms::Label());
			this->lblPort = (gcnew System::Windows::Forms::Label());
			this->tbHostname = (gcnew System::Windows::Forms::TextBox());
			this->tbPort = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(12, 78);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Cancel";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &DialogHostPort::button1_Click);
			// 
			// button2
			// 
			this->button2->Location = System::Drawing::Point(115, 78);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(75, 23);
			this->button2->TabIndex = 1;
			this->button2->Text = L"Connect";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &DialogHostPort::button2_Click);
			// 
			// lblHostname
			// 
			this->lblHostname->AutoSize = true;
			this->lblHostname->Location = System::Drawing::Point(9, 14);
			this->lblHostname->Name = L"lblHostname";
			this->lblHostname->Size = System::Drawing::Size(55, 13);
			this->lblHostname->TabIndex = 2;
			this->lblHostname->Text = L"Hostname";
			// 
			// lblPort
			// 
			this->lblPort->AutoSize = true;
			this->lblPort->Location = System::Drawing::Point(9, 53);
			this->lblPort->Name = L"lblPort";
			this->lblPort->Size = System::Drawing::Size(26, 13);
			this->lblPort->TabIndex = 3;
			this->lblPort->Text = L"Port";
			// 
			// tbHostname
			// 
			this->tbHostname->Location = System::Drawing::Point(70, 12);
			this->tbHostname->Name = L"tbHostname";
			this->tbHostname->Size = System::Drawing::Size(120, 20);
			this->tbHostname->TabIndex = 4;
			// 
			// tbPort
			// 
			this->tbPort->Location = System::Drawing::Point(70, 46);
			this->tbPort->Name = L"tbPort";
			this->tbPort->Size = System::Drawing::Size(120, 20);
			this->tbPort->TabIndex = 5;
			// 
			// DialogHostPort
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(207, 113);
			this->Controls->Add(this->tbPort);
			this->Controls->Add(this->tbHostname);
			this->Controls->Add(this->lblPort);
			this->Controls->Add(this->lblHostname);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Name = L"DialogHostPort";
			this->Text = L"DialogHostPort";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
				 hostname = tbHostname->Text;
				 port = tbPort->Text;
				 this->DialogResult = System::Windows::Forms::DialogResult::OK;
	}
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
				 this->DialogResult = System::Windows::Forms::DialogResult::Cancel;
	}
	};
}
