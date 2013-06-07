//Macrouri
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#define PORT     "15193"
#define TV_SEC   0
#define TV_uSEC  0
#define LEN      512
#define NUME_LEN 30
#define FISIER   "set.txt"

//Includeuri
#include <fstream>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

//Librarii
#pragma comment (lib, "ws2_32.lib")

#pragma once

namespace FangliMESS
{
	//Spatii de nume
	using namespace std;
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	//Definitii
	public ref class Form1 : public System::Windows::Forms::Form
	{
	private:
		ref class mouse
		{
		public:
			bool Apasa;
			ref class delta
			{
			public:
				int X, Y;
				delta()
				{
					this->X = this->Y =0;
				}
			}Delta;
			mouse()
			{
				this->Apasa = false;
			}
		};
		ref class client
		{
		public:
			System::String ^IP, ^Nume;
			SOCKET Sock;

			client()
			{
				this->Sock = INVALID_SOCKET;
			}
			bool Conectare()
			{	
				//Declaratii
				int i;
				char ip[21];
				addrinfo *rez, init;

				//Conversie
				for (i = 0; i < this->IP->Length; i++)
					ip[i] = static_cast<char>(this->IP[i]);
				ip[this->IP->Length] = 0;

				//Pregatire getaddrinfo()
				ZeroMemory(&init, sizeof init);
				init.ai_family = AF_UNSPEC;
				init.ai_socktype = SOCK_STREAM;
				init.ai_protocol = IPPROTO_TCP;

				//getaddrinfo()
				if (getaddrinfo(ip, PORT, &init, &rez))
					return false;

				//socket()
				if ((this->Sock = socket(rez->ai_family, rez->ai_socktype, rez->ai_protocol)) == INVALID_SOCKET)
					return false;

				//connect()
				if (connect(this->Sock, rez->ai_addr, static_cast<int>(rez->ai_addrlen)) == SOCKET_ERROR)
				{
					closesocket(this->Sock);
					this->Sock = INVALID_SOCKET;
					return false;
				}

				//Curatare
				freeaddrinfo(rez);

				//Returnare
				return true;
			}
		};
		mouse Mouse;
		client ^Client;

		System::Windows::Forms::Timer ^timer1;
		System::Windows::Forms::ListBox ^listBox1;
		System::Windows::Forms::RichTextBox ^richTextBox1;
		System::Windows::Forms::PictureBox ^pictureBox1;
		System::Windows::Forms::TextBox ^textBox1, ^textBox2;
		System::Windows::Forms::Label ^label1, ^label2, ^label3, ^label4;
		System::Windows::Forms::Button ^button1, ^button2, ^button3, ^button4;
		
		System::Windows::Forms::MenuStrip ^menuStrip1;
		System::Windows::Forms::ToolStripSeparator ^toolStripSeparator1;
		System::Windows::Forms::ToolStripMenuItem ^programToolStripMenuItem, ^deconectareToolStripMenuItem, ^iesireToolStripMenuItem, ^conectareToolStripMenuItem;

		System::ComponentModel::IContainer ^components;
	protected:
		~Form1()
		{
			//Curatare
			if (components)
				delete components;
			if (this->Client->Sock != INVALID_SOCKET)
				closesocket(this->Client->Sock);
			WSACleanup();
		}

	public:
		Form1()
		{
			//Declaratii
			char ip[21];
			fstream f(FISIER, ios::in);
			WSAData wsa;

			//Initializari
			InitializeComponent();
			this->Client = gcnew Form1::client;
			this->textBox1->Focus();

			//WSAStartup()
			if (WSAStartup(MAKEWORD(2,2), &wsa))
				this->label3->Text = L"Eroare WSAStartup()";

			//Citire IP
			f.get(ip, 20);
			if (f)
				this->Client->IP = gcnew System::String(ip);
			else
				this->Client->IP = "localhost";

			//Curatare
			f.close();
		}

#pragma region Windows Form Designer generated code
		//Initializare
		void InitializeComponent()
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->programToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->conectareToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->deconectareToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->iesireToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			this->menuStrip1->SuspendLayout();
			this->SuspendLayout();
			// 
			// timer1
			// 
			this->timer1->Interval = 1;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::timer1_Tick);
			// 
			// listBox1
			// 
			this->listBox1->Enabled = false;
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 16;
			this->listBox1->Location = System::Drawing::Point(251, 59);
			this->listBox1->Name = L"listBox1";
			this->listBox1->ScrollAlwaysVisible = true;
			this->listBox1->Size = System::Drawing::Size(128, 180);
			this->listBox1->Sorted = true;
			this->listBox1->TabIndex = 11;
			this->listBox1->TabStop = false;
			this->listBox1->Visible = false;
			// 
			// richTextBox1
			// 
			this->richTextBox1->BackColor = System::Drawing::Color::White;
			this->richTextBox1->Enabled = false;
			this->richTextBox1->Location = System::Drawing::Point(16, 59);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->ReadOnly = true;
			this->richTextBox1->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Vertical;
			this->richTextBox1->Size = System::Drawing::Size(229, 180);
			this->richTextBox1->TabIndex = 10;
			this->richTextBox1->TabStop = false;
			this->richTextBox1->Text = L"";
			this->richTextBox1->Visible = false;
			// 
			// pictureBox1
			// 
			this->pictureBox1->BackColor = System::Drawing::Color::Transparent;
			this->pictureBox1->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox1.BackgroundImage")));
			this->pictureBox1->Location = System::Drawing::Point(100, 60);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(200, 100);
			this->pictureBox1->TabIndex = 8;
			this->pictureBox1->TabStop = false;
			this->pictureBox1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Mouse_Move);
			this->pictureBox1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Mouse_Down);
			this->pictureBox1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Mouse_Up);
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(155, 170);
			this->textBox1->MaxLength = 30;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(145, 22);
			this->textBox1->TabIndex = 2;
			// 
			// textBox2
			// 
			this->textBox2->Enabled = false;
			this->textBox2->Location = System::Drawing::Point(16, 245);
			this->textBox2->MaxLength = 478;
			this->textBox2->Name = L"textBox2";
			this->textBox2->Size = System::Drawing::Size(229, 22);
			this->textBox2->TabIndex = 12;
			this->textBox2->Visible = false;
			// 
			// label1
			// 
			this->label1->BackColor = System::Drawing::Color::Transparent;
			this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(12, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(290, 17);
			this->label1->TabIndex = 0;
			this->label1->Text = L"FangliMESS";
			this->label1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Mouse_Move);
			this->label1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Mouse_Down);
			this->label1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Mouse_Up);
			// 
			// label2
			// 
			this->label2->BackColor = System::Drawing::Color::Transparent;
			this->label2->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label2->Location = System::Drawing::Point(81, 173);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(68, 16);
			this->label2->TabIndex = 1;
			this->label2->Text = L"Nume: ";
			this->label2->TextAlign = System::Drawing::ContentAlignment::MiddleRight;
			this->label2->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Mouse_Move);
			this->label2->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Mouse_Down);
			this->label2->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Mouse_Up);
			// 
			// label3
			// 
			this->label3->BackColor = System::Drawing::Color::Transparent;
			this->label3->Font = (gcnew System::Drawing::Font(L"Arial", 20.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label3->Location = System::Drawing::Point(0, 235);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(400, 40);
			this->label3->TabIndex = 3;
			this->label3->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			this->label3->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Mouse_Move);
			this->label3->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Mouse_Down);
			this->label3->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Mouse_Up);
			// 
			// label4
			// 
			this->label4->BackColor = System::Drawing::Color::Transparent;
			this->label4->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->label4->ForeColor = System::Drawing::Color::Black;
			this->label4->Location = System::Drawing::Point(16, 275);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(364, 17);
			this->label4->TabIndex = 9;
			this->label4->Text = L"Atestat Informatica 2011, Fangli Andrei";
			this->label4->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->label4->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Mouse_Move);
			this->label4->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Mouse_Down);
			this->label4->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Mouse_Up);
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::Transparent;
			this->button1->FlatAppearance->BorderColor = System::Drawing::Color::Black;
			this->button1->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->button1->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Location = System::Drawing::Point(155, 202);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(90, 25);
			this->button1->TabIndex = 4;
			this->button1->TabStop = false;
			this->button1->Text = L"Conectare";
			this->button1->UseCompatibleTextRendering = true;
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::Conectare);
			// 
			// button2
			// 
			this->button2->BackColor = System::Drawing::Color::Transparent;
			this->button2->FlatAppearance->BorderColor = System::Drawing::Color::Black;
			this->button2->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->button2->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Font = (gcnew System::Drawing::Font(L"Webdings", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(2)));
			this->button2->Location = System::Drawing::Point(360, 9);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(19, 17);
			this->button2->TabIndex = 5;
			this->button2->TabStop = false;
			this->button2->Text = L"r";
			this->button2->TextAlign = System::Drawing::ContentAlignment::BottomCenter;
			this->button2->UseCompatibleTextRendering = true;
			this->button2->UseVisualStyleBackColor = false;
			this->button2->Click += gcnew System::EventHandler(this, &Form1::Iesire);
			// 
			// button3
			// 
			this->button3->BackColor = System::Drawing::Color::Transparent;
			this->button3->FlatAppearance->BorderColor = System::Drawing::Color::Black;
			this->button3->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->button3->FlatAppearance->MouseOverBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), 
				static_cast<System::Int32>(static_cast<System::Byte>(128)), static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->Font = (gcnew System::Drawing::Font(L"Webdings", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(2)));
			this->button3->Location = System::Drawing::Point(335, 9);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(19, 17);
			this->button3->TabIndex = 6;
			this->button3->TabStop = false;
			this->button3->Text = L"0";
			this->button3->TextAlign = System::Drawing::ContentAlignment::BottomCenter;
			this->button3->UseCompatibleTextRendering = true;
			this->button3->UseVisualStyleBackColor = false;
			this->button3->Click += gcnew System::EventHandler(this, &Form1::Minimizare);
			// 
			// button4
			// 
			this->button4->BackColor = System::Drawing::Color::Transparent;
			this->button4->Enabled = false;
			this->button4->FlatAppearance->BorderColor = System::Drawing::Color::White;
			this->button4->FlatAppearance->MouseDownBackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(192)), 
				static_cast<System::Int32>(static_cast<System::Byte>(0)), static_cast<System::Int32>(static_cast<System::Byte>(0)));
			this->button4->FlatAppearance->MouseOverBackColor = System::Drawing::Color::Maroon;
			this->button4->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button4->Font = (gcnew System::Drawing::Font(L"Arial", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->button4->ForeColor = System::Drawing::Color::White;
			this->button4->Location = System::Drawing::Point(251, 245);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(128, 22);
			this->button4->TabIndex = 13;
			this->button4->TabStop = false;
			this->button4->Text = L"Trimite";
			this->button4->UseCompatibleTextRendering = true;
			this->button4->UseVisualStyleBackColor = false;
			this->button4->Visible = false;
			this->button4->Click += gcnew System::EventHandler(this, &Form1::Trimitere);
			// 
			// menuStrip1
			// 
			this->menuStrip1->AutoSize = false;
			this->menuStrip1->BackColor = System::Drawing::Color::Transparent;
			this->menuStrip1->Dock = System::Windows::Forms::DockStyle::None;
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->programToolStripMenuItem});
			this->menuStrip1->Location = System::Drawing::Point(1, 32);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
			this->menuStrip1->Size = System::Drawing::Size(398, 24);
			this->menuStrip1->Stretch = false;
			this->menuStrip1->TabIndex = 7;
			this->menuStrip1->Text = L"menuStrip1";
			this->menuStrip1->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Mouse_Up);
			this->menuStrip1->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Mouse_Down);
			this->menuStrip1->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Mouse_Move);
			// 
			// programToolStripMenuItem
			// 
			this->programToolStripMenuItem->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->programToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(4) {this->conectareToolStripMenuItem, 
				this->deconectareToolStripMenuItem, this->toolStripSeparator1, this->iesireToolStripMenuItem});
			this->programToolStripMenuItem->Name = L"programToolStripMenuItem";
			this->programToolStripMenuItem->Size = System::Drawing::Size(59, 20);
			this->programToolStripMenuItem->Text = L"Program";
			this->programToolStripMenuItem->TextImageRelation = System::Windows::Forms::TextImageRelation::TextAboveImage;
			// 
			// conectareToolStripMenuItem
			// 
			this->conectareToolStripMenuItem->Name = L"conectareToolStripMenuItem";
			this->conectareToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Alt | System::Windows::Forms::Keys::C));
			this->conectareToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->conectareToolStripMenuItem->Text = L"Conectare";
			this->conectareToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::Conectare);
			// 
			// deconectareToolStripMenuItem
			// 
			this->deconectareToolStripMenuItem->Enabled = false;
			this->deconectareToolStripMenuItem->Name = L"deconectareToolStripMenuItem";
			this->deconectareToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Alt | System::Windows::Forms::Keys::D));
			this->deconectareToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->deconectareToolStripMenuItem->Text = L"Deconectare";
			this->deconectareToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::Deconectare);
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(178, 6);
			// 
			// iesireToolStripMenuItem
			// 
			this->iesireToolStripMenuItem->DisplayStyle = System::Windows::Forms::ToolStripItemDisplayStyle::Text;
			this->iesireToolStripMenuItem->Name = L"iesireToolStripMenuItem";
			this->iesireToolStripMenuItem->ShortcutKeys = static_cast<System::Windows::Forms::Keys>((System::Windows::Forms::Keys::Alt | System::Windows::Forms::Keys::F4));
			this->iesireToolStripMenuItem->Size = System::Drawing::Size(181, 22);
			this->iesireToolStripMenuItem->Text = L"Iesire";
			this->iesireToolStripMenuItem->TextImageRelation = System::Windows::Forms::TextImageRelation::TextAboveImage;
			this->iesireToolStripMenuItem->Click += gcnew System::EventHandler(this, &Form1::Iesire);
			// 
			// Form1
			// 
			this->AcceptButton = this->button1;
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->BackColor = System::Drawing::Color::Silver;
			this->BackgroundImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"$this.BackgroundImage")));
			this->ClientSize = System::Drawing::Size(400, 300);
			this->Controls->Add(this->button4);
			this->Controls->Add(this->textBox2);
			this->Controls->Add(this->listBox1);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->button2);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->menuStrip1);
			this->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip1;
			this->MaximizeBox = false;
			this->Name = L"Form1";
			this->Text = L"FangliMESS";
			this->TransparencyKey = System::Drawing::Color::Silver;
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Mouse_Up);
			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Mouse_Down);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &Form1::Mouse_Move);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private:
	//Functii
	// cif()
	int cif(int n)
	{
		int s = 0;
		do s++; while(n = n/10);
		return s;
	}
	// Schimb()
	void Schimb()
	{
		this->textBox1->Enabled = !this->textBox1->Enabled;
		this->textBox1->Visible = !this->textBox1->Visible;
		this->textBox2->Enabled = !this->textBox2->Enabled;
		this->textBox2->Visible = !this->textBox2->Visible;

		this->richTextBox1->Enabled = !this->richTextBox1->Enabled;
		this->richTextBox1->Visible = !this->richTextBox1->Visible;
		this->pictureBox1->Enabled = !this->pictureBox1->Enabled;
		this->pictureBox1->Visible = !this->pictureBox1->Visible;

		this->listBox1->Enabled = !this->listBox1->Enabled;
		this->listBox1->Visible = !this->listBox1->Visible;

		this->label2->Enabled = !this->label2->Enabled;
		this->label2->Visible = !this->label2->Visible;
		this->label3->Enabled = !this->label3->Enabled;
		this->label3->Visible = !this->label3->Visible;

		this->button1->Enabled = !this->button1->Enabled;
		this->button1->Visible = !this->button1->Visible;
		this->button4->Enabled = !this->button4->Enabled;
		this->button4->Visible = !this->button4->Visible;

		this->conectareToolStripMenuItem->Enabled = !this->conectareToolStripMenuItem->Enabled;
		this->deconectareToolStripMenuItem->Enabled = !this->deconectareToolStripMenuItem->Enabled;

		this->timer1->Enabled = !this->timer1->Enabled;

		this->Update();
	}
	// Conectare()
	System::Void Conectare(System::Object ^sender, System::EventArgs ^e)
	{
		//Declaratii
		int n, i = -1;
		char snd[LEN], rcv[LEN];

		//Initializare
		this->Client->Nume = this->textBox1->Text;

		//Cazuri
		// Exista nume
		if (System::String::Compare(this->textBox1->Text, ""))
		{
			//Conectare la server
			if (this->Client->Conectare())
			{
				//Conversie
				for (i = 0; i < this->Client->Nume->Length; i++)
					snd[i] = static_cast<char>(this->Client->Nume[i]);
				snd[this->Client->Nume->Length] = 0;

				//Trimitere mesaj
				send(this->Client->Sock, snd, static_cast<int>(strlen(snd)), 0);

				//Primire mesaj
				i = recv(this->Client->Sock, rcv, 1, 0);

				//Cazuri
				// Nume in uz
				if (i <= 0)
				{
					closesocket(this->Client->Sock);
					this->label3->Text = L"Nume in uz";
				}
				// Primire lista de conectati
				else
				{
					do if (rcv[0] != ' ')
					{
						//Citire lungime de sir
						n = 0;
						do{
							n = n * 10 + rcv[0] - '0';
							i = recv(this->Client->Sock, rcv, 1, 0);
						}while(rcv[0] != ' ' && i > 0);

						//Cazuri
						// Sir primit
						if (i > 0)
						{
							//Citire nume de lungime n
							recv(this->Client->Sock, rcv, n, 0);
							rcv[n] = 0;

							//Adaugare in lista de conectati
							this->listBox1->Items->Add(gcnew System::String(rcv));

							//Preluare 'inceput' de mesaj
							i = recv(this->Client->Sock, rcv, 1, 0);
						}
						// Server deconectat
						else
						{
							//Inchidere conexiune
							closesocket(this->Client->Sock);

							//Mesaj
							this->label3->Text = L"Conexiune intrerupta";
						}
					}
					else
						i = 0;
					while (i > 0);

					//Cazuri
					// Conexiune reusita
					if (!i)
					{
						this->Schimb();
						this->listBox1->Items->Add(this->Client->Nume);
						this->AcceptButton = this->button4;
						this->label1->Text += L" - " + this->Client->Nume;
						this->Text += L" - " + this->Client->Nume;
						this->textBox2->Focus();
					}
					// Conexiune nereusita
					else
					{
						this->listBox1->Items->Clear();
						this->textBox1->Focus();
						this->label3->Text = "Inchis";
					}
				}
			}
			// Conexiune nereusita
			else
				this->label3->Text = L"Conexiune nereusita";
		}
		// Nume inexistent
		else
			this->label3->Text = L"Introduceti un nume";
	}
	// Deconectare()
	System::Void Deconectare(System::Object ^sender, System::EventArgs ^e)
	{
		//Schimb()
		this->Schimb();

		//Inchidere conexiune
		closesocket(this->Client->Sock);

		//Reinitializare
		this->AcceptButton = this->button1;
		this->Client->Sock = INVALID_SOCKET;
		this->listBox1->Items->Clear();
		this->richTextBox1->Text = L"";
		this->textBox2->Text = L"";
		this->label1->Text = L"FangliMESS";
		this->label3->Text = L"";
		this->Text = L"FangliMESS";
		this->textBox1->Focus();
	}
	// Iesire()
	System::Void Iesire(System::Object ^sender, System::EventArgs ^e)
	{
		this->~Form1();
	}
	// Minimizare
	System::Void Minimizare(System::Object^  sender, System::EventArgs^  e)
	{
		//Cazuri
		// Conectat
		if (this->Client->Sock != INVALID_SOCKET)
			this->textBox2->Focus();
		// Neconectat
		else
			this->textBox1->Focus();
		//Minimizare
		this->WindowState = System::Windows::Forms::FormWindowState::Minimized;
		//Update
		this->Update();
	}
	// Trimitere
	System::Void Trimitere(System::Object^  sender, System::EventArgs^  e)
	{
		//Declaratii
		int i, len, s;
		char snd[LEN];

		//Cazuri
		// Avem ce trimite?
		if (System::String::Compare(this->textBox2->Text, ""))
		{
			//Transformare
			itoa(this->Client->Nume->Length + this->textBox2->Text->Length +2, snd, 10);
			s = cif(this->Client->Nume->Length + this->textBox2->Text->Length +2);

			//Adaugare spatiu
			snd[s] = ' ';

			//Conversie nume
			for (i = 0; i < this->Client->Nume->Length; i++)
				snd[i + s +1] = static_cast<char>(this->Client->Nume[i]);

			//Adaugare ": "
			snd[this->Client->Nume->Length + s +1] = ':';
			snd[this->Client->Nume->Length + s +2] = ' ';

			//Conversie mesaj
			for (i = 0; i < this->textBox2->Text->Length; i++)
				snd[i + this->Client->Nume->Length + s + 3] = static_cast<char>(this->textBox2->Text[i]);
			snd[this->textBox2->Text->Length + this->Client->Nume->Length + s +3] = 0;

			//Trimitere mesaj
			send(this->Client->Sock, snd, this->textBox2->Text->Length + this->Client->Nume->Length + s +3, 0);

			//Reinitializare
			this->textBox2->Text = L"";
		}
	}
	//Mouse
	// Mouse up
	System::Void Mouse_Up(System::Object ^sender, System::Windows::Forms::MouseEventArgs ^e)
	{
		this->Mouse.Apasa = false;
	}
	// Mouse move
	System::Void Mouse_Move(System::Object ^sender, System::Windows::Forms::MouseEventArgs ^e)
	{
		if (this->Mouse.Apasa)
			this->Location = System::Drawing::Point(this->Cursor->Position.X - this->Mouse.Delta.X, this->Cursor->Position.Y - this->Mouse.Delta.Y);
	}
	// Mouse down
	System::Void Mouse_Down(System::Object ^sender, System::Windows::Forms::MouseEventArgs ^e)
	{
		this->Mouse.Apasa = true;
		this->Mouse.Delta.X = this->Cursor->Position.X - this->Location.X;
		this->Mouse.Delta.Y = this->Cursor->Position.Y - this->Location.Y;
	}
	//Timer
	System::Void timer1_Tick(System::Object^  sender, System::EventArgs^  e)
	{
		//Declaratii
		int i, n = 0;
		char rcv[LEN];
		System::String ^str;
		fd_set fd;
		timeval ti;

		//Pregatire select()
		fd.fd_array[0] = this->Client->Sock;
		fd.fd_count = 1;
		ti.tv_sec = TV_SEC;
		ti.tv_usec = TV_uSEC;

		//select()
		if (select(1, &fd, 0, 0, &ti))
		{
			//Primire mesaj
			i = recv(this->Client->Sock, rcv, 1, 0);
			if (i > 0)
			{
				do{
					//Conversie
					n = n*10 + rcv[0] - '0';

					//Citirea urmatorului caracter
					i = recv(this->Client->Sock, rcv, 1, 0);
				}while (i > 0 && rcv[0] != ' ');

				//Cazuri
				// Inca conectat
				if (i > 0)
				{
					//Citire mesaj de lungime n
					i = recv(this->Client->Sock, rcv, n, 0);
					rcv[n] = 0;

					//Cazuri
					// Am primit un mesaj
					if (strchr(rcv, ':'))
					{
						this->richTextBox1->Text += gcnew System::String(rcv) + L"\n";
						this->richTextBox1->Focus();
						this->richTextBox1->SelectionStart = this->richTextBox1->Text->Length;
						this->textBox2->Focus();
					}
					// S-a (de)conectat cineva
					else
					{
						//Conversie
						str = gcnew System::String(rcv);

						//  Conectat
						if (!this->listBox1->Items->Contains(str))
							this->listBox1->Items->Add(str);
						//  Deconectat
						else
							this->listBox1->Items->Remove(str);
					}
				}
				// Deconectat
				else
					this->Deconectare(sender, e);
			}
			else
				this->Deconectare(sender, e);
		}
	}
};
}