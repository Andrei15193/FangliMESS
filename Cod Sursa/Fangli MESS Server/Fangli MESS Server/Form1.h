//Macrouri
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#define PORT    "15193"
#define LEN     512
#define TV_SEC  0
#define TV_uSEC 0

//Includeuri
#include <fstream>
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

//Librarii
#pragma comment (lib, "Ws2_32.lib")

#pragma once

namespace FangliMESSServer {

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
		ref class socklist
			{
			public:
				System::String ^Nume;
				SOCKET Sock;
				socklist ^Urmator;
				
				socklist(System::String ^nume, SOCKET sock)
				{
					this->Nume = nume;
					this->Sock = sock;
				}
			};
		ref class server
		{
		public:
			int len;
			
			socklist ^SockList, ^Ultim;
			server()
			{
				this->len = 0;
			}
		};
		server ^Server;

		System::Windows::Forms::Button^  button1;
		System::Windows::Forms::Label^  label1;
		System::Windows::Forms::RichTextBox^  richTextBox1;
		System::Windows::Forms::TextBox^  textBox1;
		System::Windows::Forms::Timer^  timer1;
		
		System::Windows::Forms::MenuStrip^  menuStrip1;

		System::ComponentModel::IContainer^  components;
	protected:
		~Form1()
		{
			//Declaratii
			int i;

			//Curatare
			if (components)
				delete components;
			for (i = 0; i < this->Server->len; i++, this->Server->SockList = this->Server->SockList->Urmator)
				closesocket(this->Server->SockList->Sock);
		}
	public:
		Form1()
		{
			//Declaratii
			addrinfo *rez, init;
			SOCKET srv;
			WSADATA wsa;

			//Initializari
			InitializeComponent();
			this->Server = gcnew Form1::server();

			//Pornire server
			// Pregatire getaddrinfo()
			ZeroMemory(&init, sizeof init);
			init.ai_family = AF_INET;
			init.ai_socktype = SOCK_STREAM;
			init.ai_protocol = IPPROTO_TCP;
			init.ai_flags = AI_PASSIVE;

			// WSAStartup()
			if (WSAStartup(MAKEWORD(2, 2), &wsa))
				this->richTextBox1->Text += L"Eroare WSAStartup()\n";

			// getaddrinfo()
			if (getaddrinfo(0, PORT, &init, &rez))
				this->richTextBox1->Text += L"Eroare getaddrinfo()\n";

			// socket()
			if ((srv = socket(rez->ai_family, rez->ai_socktype, rez->ai_protocol)) == INVALID_SOCKET)
				this->richTextBox1->Text += L"Eroare socket()\n";

			// bind()
			if (bind(srv, rez->ai_addr, static_cast<int>(rez->ai_addrlen)) == SOCKET_ERROR)
				this->richTextBox1->Text += L"Eroare bind()\n";

			// listen()
			if (listen(srv, SOMAXCONN) == SOCKET_ERROR)
				this->richTextBox1->Text += L"Eroare listen()\n";

			// Curatare
			freeaddrinfo(rez);

			// Cazuri
			//  Pornire nereusita
			if (srv == INVALID_SOCKET)
				this->richTextBox1->Text += L"Eroare de pornire";
			//  Pornire reusita
			else
			{
				this->richTextBox1->Text += L"Server pornit\n--------------------------\n";
				this->Server->SockList = gcnew Form1::socklist("FangliMESS Admin", srv);
				this->Server->Ultim = this->Server->SockList;
				++this->Server->len;
				this->timer1->Enabled = true;
			}
		}

#pragma region Windows Form Designer generated code
		void InitializeComponent()
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->richTextBox1 = (gcnew System::Windows::Forms::RichTextBox());
			this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			this->timer1 = (gcnew System::Windows::Forms::Timer(this->components));
			this->SuspendLayout();
			// 
			// menuStrip1
			// 
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->RenderMode = System::Windows::Forms::ToolStripRenderMode::System;
			this->menuStrip1->Size = System::Drawing::Size(294, 24);
			this->menuStrip1->TabIndex = 0;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(208, 334);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(75, 23);
			this->button1->TabIndex = 1;
			this->button1->Text = L"Trimite";
			this->button1->UseCompatibleTextRendering = true;
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Form1::Trimite);
			// 
			// label1
			// 
			this->label1->Font = (gcnew System::Drawing::Font(L"Arial", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->label1->Location = System::Drawing::Point(12, 33);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(271, 35);
			this->label1->TabIndex = 2;
			this->label1->Text = L"FangliMESS Server";
			this->label1->TextAlign = System::Drawing::ContentAlignment::TopCenter;
			// 
			// richTextBox1
			// 
			this->richTextBox1->BackColor = System::Drawing::SystemColors::Window;
			this->richTextBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->richTextBox1->Location = System::Drawing::Point(12, 71);
			this->richTextBox1->Name = L"richTextBox1";
			this->richTextBox1->ReadOnly = true;
			this->richTextBox1->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Vertical;
			this->richTextBox1->Size = System::Drawing::Size(270, 257);
			this->richTextBox1->TabIndex = 3;
			this->richTextBox1->Text = L"";
			// 
			// textBox1
			// 
			this->textBox1->Location = System::Drawing::Point(12, 335);
			this->textBox1->MaxLength = 478;
			this->textBox1->Name = L"textBox1";
			this->textBox1->Size = System::Drawing::Size(189, 22);
			this->textBox1->TabIndex = 4;
			// 
			// timer1
			// 
			this->timer1->Interval = 1;
			this->timer1->Tick += gcnew System::EventHandler(this, &Form1::Timer);
			// 
			// Form1
			// 
			this->AcceptButton = this->button1;
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::None;
			this->ClientSize = System::Drawing::Size(294, 368);
			this->Controls->Add(this->textBox1);
			this->Controls->Add(this->richTextBox1);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->menuStrip1);
			this->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menuStrip1;
			this->Name = L"Form1";
			this->Text = L"FangliMESS Server";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
private:
	//Functii
	// cif()
	int cif(int n)
	{
		//Declaratii
		int s = 0;

		//Obtinerea numarului de cifre
		do s++; while (n /= 10);

		//Returnare
		return s;
	}
	// cauta()
	bool cauta(System::String ^str)
	{
		//Declaratii
		int i;
		Form1::socklist ^j = this->Server->SockList;

		//Cautare
		for (i = 0; i < this->Server->len; i++, j = j->Urmator)
			if (!System::String::Compare(str, j->Nume))
				return false;

		//Returnare
		return true;
	}
	// conect()
	void conect()
	{
		//Declaratii
		int i, k, len;
		char rcv[LEN], snd[LEN];
		Form1::socklist ^j = this->Server->SockList->Urmator;
		System::String ^str;
		SOCKET client;
		fd_set fd;
		timeval ti;

		//Pregatire select()
		fd.fd_array[0] = this->Server->SockList->Sock;
		fd.fd_count = 1;
		ti.tv_sec = TV_SEC;
		ti.tv_usec = TV_uSEC;

		//select()
		if (select(1, &fd, 0, 0, &ti))
		{
			//accept()
			client = accept(this->Server->SockList->Sock, 0, 0);

			//Primire nume
			i = recv(client, rcv, LEN, 0);
			rcv[i] = 0;

			//Conversie
			str = gcnew System::String(rcv);

			//Cautare
			if (this->cauta(str))
			{
				//Trimitere lista de conectati
				for (i = 1; i < this->Server->len; i++, j = j->Urmator)
				{
					//Formare mesaj
					len = cif(j->Nume->Length);
					itoa(j->Nume->Length, snd, 10);
					strncat_s(snd, " ", LEN);
					for (k = 0; k < j->Nume->Length; k++)
						snd[k + len +1] = static_cast<char>(j->Nume[k]);
					snd[j->Nume->Length + len +1] = 0;

					//Trimitere
					send(client, snd, static_cast<int>(strlen(snd)), 0);
				}
				//Trimitere mesaj de final
				send(client, " ", 1, 0);

				//Formare mesaj
				itoa(static_cast<int>(strlen(rcv)), snd, 10);
				strncat_s(snd, " ", LEN -1);
				strncat_s(snd, rcv, LEN -1);
				len = static_cast<int>(strlen(snd));

				//Trimitere la toti cei conectati
				j = this->Server->SockList->Urmator;
				for (i = 1; i < this->Server->len; i++, j = j->Urmator)
					send(j->Sock, snd, len, 0);

				//Adaugare in lista
				this->Server->Ultim->Urmator = gcnew Form1::socklist(str, client);
				this->Server->Ultim = this->Server->Ultim->Urmator;
				++this->Server->len;

				//Mesaj
				this->richTextBox1->Text += L" --> S-a conectat " + str + L"\n";
			}
			// Nume existent
			else
				closesocket(client);
		}
	}
	// Trimite
	System::Void Trimite(System::Object ^sender, System::EventArgs ^e)
	{
		//Declaratii
		int i, len;
		char snd[LEN];
		Form1::socklist ^j = this->Server->SockList->Urmator;

		//Conversie lungime mesaj
		len = this->Server->SockList->Nume->Length + this->textBox1->Text->Length +2;
		itoa(len, snd, 10);
		len = cif(len);

		//Adaugare spatiu liber
		snd[len] = ' ';

		//Conversie nume
		for (i = 0; i < this->Server->SockList->Nume->Length; i++)
			snd[i + len +1] = static_cast<char>(this->Server->SockList->Nume[i]);

		//Adaugare ": "
		snd[this->Server->SockList->Nume->Length + len +1] = ':';
		snd[this->Server->SockList->Nume->Length + len +2] = ' ';

		//Conversie mesaj
		for (i = 0; i < this->textBox1->Text->Length; i++)
			snd[i + this->Server->SockList->Nume->Length + len +3] = static_cast<char>(this->textBox1->Text[i]);

		//Semnalare final de sir
		snd[this->textBox1->Text->Length + this->Server->SockList->Nume->Length + len +3] = 0;

		//Memorare lungiem de sir
		len = static_cast<int>(strlen(snd));

		//Trimitere mesaj la toti cei conectati
		for (i = 1; i < this->Server->len; i++, j = j->Urmator)
			send(j->Sock, snd, len, 0);

		//Afisare mesaj
		this->richTextBox1->Text += this->Server->SockList->Nume + L": " + this->textBox1->Text + L"\n";

		//Reinitializare
		this->textBox1->Text = L"";
	}
	// Timer
	System::Void Timer(System::Object ^sender, System::EventArgs ^e)
	{
		//Declaratii
		int k, ok, n;
		char rcv[LEN], snd[LEN];
		bool p;
		fd_set fd;
		timeval ti;
		Form1::socklist ^i, ^j = this->Server->SockList;

		//S-a conectat cineva?
		this->conect();

		//Am primit mesaje?
		ti.tv_sec = TV_SEC;
		ti.tv_usec = TV_uSEC;
		//Parcurgere lista de conectati
		for (k = 1; k < this->Server->len; k++, j = j->Urmator)
		{
			//Pregatire select()
			fd.fd_array[0] = j->Urmator->Sock;
			fd.fd_count = 1;
			p = true;

			//select()
			if (select(1, &fd, 0, 0, &ti))
			{
				//Primire mesaj de inceput
				ok = recv(j->Urmator->Sock, rcv, 1, 0);
				
				//Cazuri
				// Inca conectat
				if (ok > 0)
				{
					//Obtinere lungime de sir
					n = 0;
					do if(rcv[0] != ' ')
					{
						n = n * 10 + rcv[0] - '0';
						ok = recv(j->Urmator->Sock, rcv, 1, 0);
					}
					else
						ok = 0;
					while (ok > 0);

					//cazuri
					// Inca conectat
					if (!ok)
					{
						//Citire sir de lungime n
						recv(j->Urmator->Sock, rcv, n, 0);
						rcv[n] = 0;

						//Afisare mesaj
						this->richTextBox1->Text += gcnew System::String(rcv) + L"\n";
					}
					// Deconectat
					else
						p = false;
				}
				// Deconectat
				else
					p = false;

				//Cazuri
				// Se trimite mesajul
				if (p)
				{	
					//Formare mesaj
					itoa(n, snd, 10);
					strncat_s(snd, " ", LEN);
					strncat_s(snd, rcv, LEN);

					//Memorare lungime de sir
					n = static_cast<int>(strlen(snd));

					//Se da vestea-n targ
					i = this->Server->SockList->Urmator;
					for (ok = 1; ok < this->Server->len; ok++, i = i->Urmator)
						send(i->Sock, snd, n, 0);
				}
				// Deconectat
				else
				{
					//Mesaj
					this->richTextBox1->Text += L" --> S-a deconectat " + j->Urmator->Nume + L"\n";

					//Formare mesaj
					n = j->Urmator->Nume->Length;
					itoa(n , snd, 10);
					n = cif(n);
					snd[n] = ' ';

					//Conversie
					for (ok = 0; ok < j->Urmator->Nume->Length; ok++)
						snd[ok + n +1] = static_cast<char>(j->Urmator->Nume[ok]);
					snd[j->Urmator->Nume->Length + n +1] = 0;

					//Memorare lungime sir
					n = static_cast<int>(strlen(snd));

					//Se da vestea-n targ
					i = this->Server->SockList->Urmator;
					for (ok = 1; ok < this->Server->len; ok++, i = i->Urmator)
						send(i->Sock, snd, n, 0);

					//Stergem ultimul din lista?
					if (this->Server->Ultim == j->Urmator)
						this->Server->Ultim = j;

					//Eliminare din lista
					j->Urmator = j->Urmator->Urmator;
					--this->Server->len;
				}
			}
		}
	}
};
}