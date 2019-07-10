#include "Header.h"

class BinaryTree
{
private:
	struct Node
	{
		string key;
		string val;
		Node* parent;
		Node* left;
		Node* right;
	};
	Node* root;
	void ShowNode(Node* root, string alph)
	{
		if (root->left) { ShowNode(root->left, alph); }
		if (root->key[0] == alph[0])
		{
			arr[sizeArr] = root->key + " " + char(29) + " " + root->val; sizeArr++;
		}
		if (root->right) { ShowNode(root->right, alph); }
	}
	void DeleteNode(Node*& root)
	{
		if (root->left) { DeleteNode(root->left); }
		if (root->right) { DeleteNode(root->right); }
		delete root;
		root = nullptr;
	}
	void DeleteTree(Node*& root)
	{
		if (!root)  return;
		DeleteNode(root);
	}
	void CopyNode(Node*& root)
	{
		if (!root)return;
		AddToTree(root->key, root->val);
		if (root->left)
		{
			CopyNode(root->left);
		}
		if (root->right)
		{
			CopyNode(root->right);
		}
	}
	Node* FinedMin(Node* root)
	{
		if (!root->left) return root;
		FinedMin(root->left);
	}
	Node* SearchByKey(Node * cur, string key)
	{
		if (cur == nullptr || cur->key == key)
			return cur;
		Node * pFind = nullptr;
		if (key < cur->key)
		{
			pFind = SearchByKey(cur->left, key);
		}
		if (pFind) return pFind;
		if (key > cur->key)
		{
			pFind = SearchByKey(cur->right, key);
		}
		if (pFind) return pFind;
		return nullptr;
	}
	Node* SearchByVal(Node* root, string val)
	{
		if (root == nullptr || root->val == val)
			return root;
		Node * pFind = nullptr;
		pFind = SearchByVal(root->left, val);
		if (pFind) return pFind;
		pFind = SearchByVal(root->right, val);
		if (pFind) return pFind;
		return nullptr;
	}

public:
	int sizeArr = 0;	string* arr;
	BinaryTree() { root = nullptr; arr = new string[100]; }
	~BinaryTree() { delete root; delete[] arr; }
	Node*& GetNode() { return root; }

	void DeleteArr(int pos)
	{
		if (sizeArr == 0) return;
		string *temp = new string[sizeArr - 1];
		for (size_t i = 0; i < pos; i++)
		{
			temp[i] = arr[i];
		}
		for (size_t i = pos; i < sizeArr - 1; i++)
		{
			temp[i] = arr[i + 1];
		}
		sizeArr -= 1;
		delete[] arr;
		arr = temp;
	}
	void Change_Tree(string key, string change_key, string val)
	{

		Node * pNew = new Node();
		pNew->key = key;
		pNew->val = val;
		pNew->parent = pNew->right = pNew->left = nullptr;
		if (!root)
		{
			root = pNew;
			return;
		}
		Node* cur = root;
		while (cur)
		{
			if (key == cur->key)
			{
				delete pNew;
				cur->key = change_key;
				cur->val = val;
				return;
			}
			if (key < cur->key)
			{
				if (cur->left == nullptr)
				{
					pNew->parent = cur;
					cur->left = pNew;
					return;
				}
				cur = cur->left;
			}
			if (key > cur->key)
			{
				if (cur->right == nullptr)
				{
					pNew->parent = cur;
					cur->right = pNew;
					return;
				}
				cur = cur->right;
			}
		}
	}
	void AddToTree(string key, string val)
	{
		Node * pNew = new Node();
		pNew->key = key;
		pNew->val = val;
		pNew->parent = pNew->right = pNew->left = nullptr;
		if (!root)
		{
			root = pNew;
			return;
		}
		Node* cur = root;
		while (cur)
		{
			if (key == cur->key)
			{
				delete pNew;
				cur->val = val;
				return;
			}
			if (key < cur->key)
			{
				if (cur->left == nullptr)
				{
					pNew->parent = cur;
					cur->left = pNew;
					return;
				}
				cur = cur->left;
			}
			if (key > cur->key)
			{
				if (cur->right == nullptr)
				{
					pNew->parent = cur;
					cur->right = pNew;
					return;
				}
				cur = cur->right;
			}
		}
	}
	void DeleteAllTree()
	{
		if (!root)  return;
		DeleteNode(root);
	}
	void SearchForMainByKey(string key)
	{
		if (!root) return;
		Node * pFind = SearchByKey(root, key);
		if (pFind)
		{
			SetConsoleCP(1251);
			SetConsoleOutputCP(1251);
			SetPos(19, 7); cout << pFind->val;
			SetConsoleCP(866);
			SetConsoleOutputCP(866);
		}
		else
		{
			SetPos(19, 7); SetColor(4); cout << "Word not found!"; SetColor(15);
		}
	}
	void SearchForMainByVal(string val)
	{
		if (!root) return;
		Node * pFind = SearchByVal(root, val);
		if (pFind)
		{
			SetPos(19, 7); cout << pFind->key;
		}
		else
		{
			SetPos(19, 7); SetColor(4); cout << "Word not found!"; SetColor(15);
		}
	}
	void DeleteForMainByKey(string key)
	{
		if (!root) return;
		Node *pDel = SearchByKey(root, key);
		if (!pDel) { SetPos(28, 18); cout << "No such element\n"; return; }
		Node* parent = pDel->parent;
		if (parent)
		{
			if (parent->left == pDel)
			{
				parent->left = nullptr;
			}
			if (parent->right == pDel)
			{
				parent->right = nullptr;
			}
		}
		else root = nullptr;
		CopyNode(pDel->left);
		CopyNode(pDel->right);
		DeleteTree(pDel);
		return;
	}
	void ShowTree(string alph)
	{
		if (!root) return;
		ShowNode(root, alph);
	}

	bool SaveToFile(string filename, Node * root)
	{
		if (!root) return false;
		ofstream out(filename, ios_base::trunc);
		SaveNodeToFile(root, out);
		out.close();
		return true;
	}
	void SaveNodeToFile(Node * cur, ofstream &out)
	{
		if (cur->left)	SaveNodeToFile(cur->left, out);
		if (cur->right)	SaveNodeToFile(cur->right, out);
		out << cur->key << ":" << cur->val << ".";
	}
	bool ReadFromFile(string filename1)
	{
		ifstream in(filename1);
		char key[25];
		char val[25];
		while (!in.eof())
		{
			in.getline(key, 25, ':');
			if (in.eof()) break;
			in.getline(val, 25, '.');
			if (in.eof()) break;
			int k = atoi(key);
			AddToTree(key, val);
		}
		in.close();
		return true;
	}
};
struct Setting
{
private:
	short int m_pos;
	short int choice;
	int x_pos, y_pos, widht, height;
public:
	short int GetPos() { return m_pos; }
	short int GetCho() { return choice; }
	void SetPos(short int p) { m_pos += p; }
	void SetCho(short int c) { choice = c; }
	void Clear(short int l) { m_pos = l; }
	int GetWidht() { return widht; }
	int GetHeight() { return height; }
	int GetX() { return x_pos; }
	int GetY() { return y_pos; }
	void Change_Exel(int w, int h)
	{
		widht += w; height += h;
	}
	void Fill_Exel(int x, int y, int w, int h)
	{
		x_pos = x; y_pos = y; widht = w; height = h;
	}
	Setting() : x_pos(0), y_pos(0), widht(0), height(0), m_pos(0), choice(-1)
	{

	}
};
Setting S;

void MiniExel_1(int x, int y, int w, int h)
{
	char symMaps;;
	SetPos(x, y); for (int i = 0; i < w; i++)
	{
		if (i == 0) { symMaps = 213; cout << symMaps; }
		if (i == w - 1) { symMaps = 184; cout << symMaps; }
		else { symMaps = 205; cout << symMaps; }
	}
	SetPos(x, y + h); for (int i = 0; i < w; i++)
	{
		if (i == 0) { symMaps = 212; cout << symMaps; }
		if (i == w - 1) { symMaps = 190; cout << symMaps; }
		else { symMaps = 205; cout << symMaps; }
	}
	for (size_t i = 0; i < h - 1; i++)
	{
		SetPos(x, y + i + 1); symMaps = 179; cout << symMaps;
		SetPos(x + w, y + i + 1); symMaps = 179; cout << symMaps;
	}
}
void MiniExel_2(int x, int y, int w, int h)
{
	char symMaps;;
	SetPos(x, y); for (int i = 0; i < w; i++)
	{
		if (i == 0) { symMaps = 213; cout << symMaps; }
		if (i == w - 1) { symMaps = 184; cout << symMaps; }
		else { symMaps = 205;	cout << symMaps; }
	}
	SetPos(x, y + 2); for (int i = 0; i < w; i++)
	{
		if (i == 0) { symMaps = 198; cout << symMaps; }
		if (i == w - 1) { symMaps = 181; cout << symMaps; }
		else { symMaps = 205; cout << symMaps; }
	}
	SetPos(x, y + h); for (int i = 0; i < w; i++)
	{
		if (i == 0) { symMaps = 212; cout << symMaps; }
		if (i == w - 1) { symMaps = 190; cout << symMaps; }
		else { symMaps = 205; cout << symMaps; }
	}
}
void ClearWindow(int x, int y, int num_x, int num_y, int m_pos)
{
	for (int j = 0; j < num_y; j++)
	{
		for (int i = 0; i < num_x; i++)
		{
			SetPos(x + i + m_pos, y + j); cout << " ";
		}
	}
}

string GetString(string temp, int size, int col)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	char k; string n = temp; short int flgS = 0, c = size, q = size;
	for (int i = 0; i < c; i++)
	{
		SetColor(4); cout << n[i]; SetColor(15);
	}
	while (1)
	{
		k = _getch();
		if (int(k) == 27)
		{
			n = " ";
			return n;
		}
		if ((k == ' ') && (c != 0) && (q != 0))
		{
			SetColor(col); printf("%c", k); SetColor(15);
			n += k;
			c++;
			q++;
		}
		if ((k >= 'A') && (k <= 'Z') || (k >= 'a') && (k <= 'z') || (k >= 'À') && (k <= 'ß') || (k >= 'à') && (k <= 'ï') || (k >= 'ð') && (k <= 'ÿ'))
		{
			SetColor(col); printf("%c", k); SetColor(15);
			n += k;
			c++;
			q++;
		}
		if (k == '\b' && c != 0 || q >= 21)
		{
			_putch(8);
			_putch(' ');
			_putch(8);
			q--;
			string temp;
			for (size_t i = 0; i < n.size(); i++)
			{
				temp = n.substr(0, n.size() - 1);
			}
			n = temp;
			if (q < 0) q = 0;
			c--;
			if (c <= 0) { flgS = 0; c = 0; }
		}
		if ((k == 13) && (c != 0) && (q != 0) && (q > 1)) break;
	}
	if (flgS == -1) n = " ";

	transform(n.begin(), n.end(), n.begin(), ::tolower);
	for (size_t i = 0; i < n.size(); i++)
	{
		if (n[i] >= 'À' && n[i] <= 'Ï')
		{
			n[i] += 'à' - 'À';
		}
		else if (n[i] >= 'Ð' && n[i] <= 'ß')
		{
			n[i] += 'ð' - 'Ð';
		}
	}
	return n;
}
string GetString(string temp, string temp_2, int size, int col, int ed_pos)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	int plus_1 = 0, plus_2 = 0;
	char k; string n = temp; short int flgS = 0, c = size, q = size;
	for (int i = 0; i < c; i++)
	{
		SetColor(4); cout << n[i]; SetColor(15);
	}

	while (1)
	{
		SetPos(31 + size + plus_2, ed_pos); SetColor(6); cout << " " << char(29) << " " << temp_2; SetColor(15);

		k = _getch();
		if ((k == ' ') && (c != 0) && (q != 0))
		{
			SetPos(31 + size + plus_1, ed_pos); SetColor(col); cout << k; SetColor(15);
			plus_1++;
			plus_2++;
			n += k;
			c++;
			q++;
		}
		if ((k >= 'A') && (k <= 'Z') || (k >= 'a') && (k <= 'z') || (k >= 'À') && (k <= 'ß') || (k >= 'à') && (k <= 'ï') || (k >= 'ð') && (k <= 'ÿ'))
		{
			SetPos(31 + size + plus_1, ed_pos); SetColor(col); cout << k; SetColor(15);
			plus_1++;
			plus_2++;
			n += k;
			c++;
			q++;
		}
		if (k == '\b' && c != 0 || q >= 17)
		{
			plus_1--;
			plus_2--;
			_putch(8);
			_putch(' ');
			_putch(8);
			q--;
			string temp;
			for (size_t i = 0; i < n.size(); i++)
			{
				temp = n.substr(0, n.size() - 1);
			}
			n = temp;
			if (q < 0) q = 0;
			c--;
			if (c <= 0) { flgS = 0; c = 0; }
		}
		if ((k == 13) && (c != 0) && (q != 0) && (q > 1)) break;
	}
	if (flgS == -1) n = " ";

	transform(n.begin(), n.end(), n.begin(), ::tolower);
	for (size_t i = 0; i < n.size(); i++)
	{
		if (n[i] >= 'À' && n[i] <= 'Ï')
		{
			n[i] += 'à' - 'À';
		}
		else if (n[i] >= 'Ð' && n[i] <= 'ß')
		{
			n[i] += 'ð' - 'Ð';
		}
	}
	
	return n;
}

void Translate_Word(BinaryTree obj)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	SetPos(6, 5); cout << "ENTER THE WORD (eng or rus):";
	SetPos(6, 7); cout << "TRANSLATION:";

	string word = "";

	InvisibleÑursor(TRUE);
	SetPos(35, 5); word = GetString("", 0, 15);
	InvisibleÑursor(FALSE);

	if ((word.substr(1, 1) >= "a") && (word.substr(1, 1) <= "z"))
	{
		obj.SearchForMainByKey(word);
	}
	else if ((word.substr(1, 1) >= "à") && (word.substr(1, 1) <= "ÿ"))
	{
		obj.SearchForMainByVal(word);
	}

	SetConsoleCP(866);
	SetConsoleOutputCP(866);

	SetPos(40, 9); cout << "Continue(Enter)"; SetPos(42, 10); cout << "Go out(Esc)";

	while (true)
	{
		switch (int ch = _getch())
		{
		case 13: {
			ClearWindow(35, 5, 20, 1, 0);
			ClearWindow(19, 7, 20, 1, 0);
			ClearWindow(40, 9, 15, 2, 0);
			Translate_Word(obj);
		} break;
		case 27: {
			Size_Console(35, 24);
			system("cls");
			S.SetCho(-1);
			S.Change_Exel(-26, -5);
			Show_Menu_Prog(obj);
		} break;
		}
	}
}
void Add_Word_To_Dictionary(BinaryTree &obj)
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	SetPos(6, 7);	cout << "ENTER THE WORD(eng):";
	SetPos(6, 9);	cout << "ENTER TRANSLATION(rus):";

	string word = "", val = "";

	InvisibleÑursor(TRUE);
	SetPos(27, 7); 	word = GetString("", 0, 15);
	SetPos(30, 9); 	val = GetString("", 0, 15);
	InvisibleÑursor(FALSE);

	if ((word.substr(1, 1) >= "a") && (val.substr(1, 1) <= "z"))
	{
		SetPos(30, 9); SetColor(4);  cout << "Incorrect data entry!"; SetColor(15);
	}
	else if ((word.substr(1, 1) >= "à") && (val.substr(1, 1) <= "ÿ"))
	{
		SetPos(30, 9); SetColor(4);  cout << "Incorrect data entry!"; SetColor(15);
	}
	else if ((word.length() == 1) && (val.length() == 1))
	{
		SetPos(43, 9); SetColor(4);  cout << "CENCEL INPUT"; SetColor(15);
	}
	else
	{
		if ((word.substr(1, 1) >= "a") && (word.substr(1, 1) <= "z")) { obj.AddToTree(word, val); }
		else if ((word[0] >= 'à') && (word[0] <= 'ÿ')) { obj.AddToTree(val, word); }
		SetPos(51, 9); SetColor(2); cout << "SAVE"; SetColor(15);
	}

	SetConsoleCP(866);
	SetConsoleOutputCP(866);

	SetPos(40, 11); cout << "Continue(Enter)"; SetPos(42, 12); cout << "Go out(Esc)";

	while (true)
	{
		switch (int ch = _getch())
		{
		case 13: {
			ClearWindow(27, 7, 23, 1, 0);
			ClearWindow(30, 9, 25, 1, 0);
			ClearWindow(40, 11, 15, 2, 0);
			Add_Word_To_Dictionary(obj);
		} break;
		case 27: {
			Size_Console(35, 24);
			system("cls");
			S.SetCho(-1);
			S.Change_Exel(-26, -5);
			Show_Menu_Prog(obj);
		} break;
		}
	}
};
void Navigate_The_Alphabet(BinaryTree &obj)
{
	const int sizeAlphabet = 26;
	char alphabet[26] = { 'A','B','C','D','E','F',
						  'G','H','I','J','K','L',
						  'M','N','O','P','Q','R',
						  'S','T','U','V','W','X',
								  'Y','Z' };
	while (true)
	{
		int x_pos = 9, y_pos = 8;

		for (int i = 0; i < sizeAlphabet; i++)
		{
			if (i % 6 == 0) { y_pos++; x_pos = 8; }
			if (i >= 24)
			{
				if (i == S.GetPos()) { SetPos(x_pos + 6, y_pos); SetColor(5); cout << alphabet[i]; SetColor(15); }
				else { SetPos(x_pos + 6, y_pos); cout << alphabet[i]; }
			}
			else
			{
				if (i == S.GetPos()) { SetPos(x_pos, y_pos); SetColor(5); cout << alphabet[i]; SetColor(15); }
				else { SetPos(x_pos, y_pos); cout << alphabet[i]; }
			}
			x_pos += 3;
		}

		switch (short int ch = _getch())
		{
		case 72: {
			if (S.GetPos() == 24 || S.GetPos() == 25) { S.SetPos(-4); }
			else if (S.GetPos() - 6 >= 0) { S.SetPos(-6); }
		} break;
		case 80: {
			if (S.GetPos() + 7 < sizeAlphabet - 1) { S.SetPos(6); }
			if (S.GetPos() >= 20 && S.GetPos() <= 21) { S.SetPos(4); }
		} break;
		case 75: {
			if (S.GetPos() >= 1) { S.SetPos(-1); }
		} break;
		case 77: {
			if (S.GetPos() < sizeAlphabet - 1) { S.SetPos(1); }
		} break;
		case 13: {
			MiniExel_1(27, 4, 44, 16);
			string alph;
			alph = alphabet[S.GetPos()];
			transform(alph.begin(), alph.end(), alph.begin(), ::tolower);
			S.SetCho(S.GetPos()); S.Clear(0);  obj.arr = new string[100];
			View_Edit_Words(obj, alph);
		} break;
		case 27: {
			Size_Console(35, 24);
			system("cls");
			S.Clear(2);
			S.SetCho(-1);
			S.Change_Exel(-42, -10);
			Show_Menu_Prog(obj);
		} break;
		}
	}
}

void Delete_Word(BinaryTree &obj, int &Begin_of_Page, int &End_of_Page, int &number_page)
{
	if (obj.sizeArr != 0)
	{
		string temp, arr = " ", arr1 = " "; char ch = (char)29;
		for (int i = 0; i < obj.arr[S.GetPos()].size(); i++)
		{
			if (obj.arr[S.GetPos()][i] == arr[0])
			{
				if (obj.arr[S.GetPos()][i + 1] == ch) { break; }
				temp += " ";
			}
			else { temp += obj.arr[S.GetPos()][i]; }
		}

		obj.DeleteForMainByKey(temp);

		if (obj.sizeArr > Begin_of_Page && End_of_Page > Begin_of_Page) {
			obj.DeleteArr(S.GetPos());

			if (obj.sizeArr < End_of_Page) {
				End_of_Page = End_of_Page - (End_of_Page - obj.sizeArr);

				if (End_of_Page <= Begin_of_Page && obj.sizeArr != 0) {
					Begin_of_Page -= 13; S.Clear(Begin_of_Page + 12); number_page--;
				}
			}
			else {
				End_of_Page = obj.sizeArr - (obj.sizeArr - End_of_Page);
			}
		}
		if (S.GetPos() == End_of_Page) { S.Clear(S.GetPos() - 1); }
		else { S.Clear(S.GetPos()); }
		ClearWindow(28, 6, 37, 13, 0);
	}
	else {
		SetPos(34, 11); SetColor(12); cout << "NO WORDS FOR THIS LETTER"; SetColor(15);
	}
}
void Change_Word(BinaryTree &obj, int edit_pos)
{
	string copy_1, copy_2, arr1 = " "; char ch = (char)29; int choice = 0;  bool stop = true;

	for (int i = 0; i < obj.arr[S.GetPos()].size(); i++)
	{
		if (obj.arr[S.GetPos()][i] == arr1[0])
		{
			if (obj.arr[S.GetPos()][i + 1] == ch) { break; }
			copy_1 += " ";
		}
		else { copy_1 += obj.arr[S.GetPos()][i]; }
	}

	unsigned size = copy_1.size();
	copy_2.assign(obj.arr[S.GetPos()].begin() + (size + 3), obj.arr[S.GetPos()].end());

	string temp = copy_1, temp_2 = copy_2;
	while (stop)
	{
		for (size_t i = 0; i < 2; i++)
		{
			if (choice == 0)
			{
				SetPos(31, edit_pos); SetColor(2); cout << copy_1; SetColor(15); cout << " " << char(29) << " "; cout << copy_2;
			}
			else
			{
				SetPos(31, edit_pos); cout << copy_1;  cout << " " << char(29) << " "; SetColor(2); cout << copy_2; SetColor(15);
			}
		}
		switch (short int ch = _getch())
		{
		case 75: {  if (choice > 0) { choice -= 1; } }break;
		case 77: { 	if (choice < 1) { choice += 1; } } break;
		case 13: {
			InvisibleÑursor(TRUE);
			if (choice == 0)
			{
				SetPos(31, edit_pos); copy_1 = GetString(copy_1, copy_2, copy_1.size(), 2, edit_pos);
				stop = false; choice = 1;
			}
			else
			{
				SetPos(34 + copy_1.size(), edit_pos); copy_2 = GetString(copy_2, copy_2.size(), 2);
				stop = false; choice = 2;
			}
			InvisibleÑursor(FALSE);
		} break;
		case 27:
			stop = false;
			break;
		}
	}

	if (temp == copy_1 && temp_2 == copy_2) { return; }

	ClearWindow(25, 21, 47, 1, 0);
	SetPos(35, 21); SetColor(2); cout << "CONFIRM (ENTER)"; SetColor(15); cout << " | "; SetColor(4); cout << "CANCEL(ESC)"; SetColor(15);
l:
	switch (short int ch = _getch())
	{
	case 27:
		ClearWindow(31, edit_pos, 40, 1, 0);
		break;
	case 13:
		if (choice == 1)
		{
			obj.DeleteForMainByKey(temp);
			obj.AddToTree(copy_1, copy_2);
			obj.arr[S.GetPos()] = copy_1 + " " + (char)29 + " " + copy_2;
		}
		else
		{
			obj.AddToTree(temp, copy_2);
			obj.arr[S.GetPos()] = copy_1 + " " + (char)29 + " " + copy_2;
		}
		break;
	default:
		goto l;
		break;
	}
}
void View_Edit_Words(BinaryTree &obj, string alph)
{
	SetPos(28, 5); cout << (char)16; for (size_t i = 0; i < 41; i++) { SetPos(29 + i, 5); cout << (char)248; } SetPos(70, 5); cout << (char)17;
	SetPos(28, 19); cout << (char)16; for (size_t i = 0; i < 41; i++) { SetPos(29 + i, 19); cout << (char)22; } SetPos(70, 19); cout << (char)17;

	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);

	obj.ShowTree(alph);

	int Begin_of_Page = 0, End_of_Page, Pos_Counter = 0;
	int number_page = 0, quantity_page = 0; int edit_pos = 0;

	if (obj.sizeArr > 13) { End_of_Page = 13; }
	else { End_of_Page = obj.sizeArr; }

	if (obj.sizeArr > 0)
	{
		number_page = obj.sizeArr;
		while (number_page % 13 > 0) { number_page -= 13; ++quantity_page; }
		number_page = 1;
	}
	else
	{
		SetPos(34, 11); SetColor(12); cout << "NO WORDS FOR THIS LETTER"; SetColor(15);
	}

	while (true)
	{
		transform(alph.begin(), alph.end(), alph.begin(), ::toupper);
		SetPos(35, 3); cout << "Eng-Rus dictionary >> " << alph;
		SetPos(65, 3); cout << "[" << number_page << "/" << quantity_page << "]";
		SetPos(32, 21); cout << "Edit(TAB) | Delete(DEL) | Back(ESC)";

		for (int i = Begin_of_Page, Y_Pos = Pos_Counter; i < End_of_Page; i++, Y_Pos++)
		{
			if (i == S.GetPos())
			{
				SetPos(29, 6 + Y_Pos); edit_pos = Y_Pos + 6;
				SetColor(2); cout << (char)26 << " "; SetColor(5);
				cout << obj.arr[i]; SetColor(15);
			}
			else
			{
				SetPos(29, 6 + Y_Pos);
				cout << " " << obj.arr[i] << "  ";
			}
		}

		switch (short int ch = _getch())
		{
		case 72: {
			if (S.GetPos() == Begin_of_Page && S.GetPos() != 0 && obj.sizeArr != 0)
			{
				ClearWindow(28, 6, 37, 13, 0);
				End_of_Page = obj.sizeArr - (obj.sizeArr - Begin_of_Page); Begin_of_Page -= 13;
				S.Clear(End_of_Page - 1); Pos_Counter = 0; number_page--;
			}
			else if (S.GetPos() >= 1) { S.SetPos(-1); }
		} break;
		case 80: {
			if (S.GetPos() < End_of_Page - 1)
			{
				S.SetPos(1);
			}
			else if (End_of_Page != obj.sizeArr && S.GetPos() == End_of_Page - 1)
			{
				if (End_of_Page * 2 > obj.sizeArr)
				{
					ClearWindow(28, 6, 37, 13, 0);
					Begin_of_Page = obj.sizeArr - (obj.sizeArr - End_of_Page); End_of_Page = obj.sizeArr;
					S.Clear(Begin_of_Page); Pos_Counter = 0;
				}
				else
				{
					ClearWindow(28, 6, 37, 13, 0);
					Begin_of_Page = obj.sizeArr - (obj.sizeArr - End_of_Page); End_of_Page = obj.sizeArr - (obj.sizeArr - (End_of_Page * 2));
					S.Clear(Begin_of_Page); Pos_Counter = 0;
				}
				number_page++;
			}
		} break;
		case 83: {
			Delete_Word(obj, Begin_of_Page, End_of_Page, number_page);
		} break;
		case 9: {
			ClearWindow(25, 21, 39, 1, 0);
			SetPos(27, 21); cout << "Select(ENTER) | Remove(BACKSPACE) | Back(ESC)";
			Change_Word(obj, edit_pos);
		} break;
		case 27: {
			SetConsoleCP(866);
			SetConsoleOutputCP(866);
			S.Clear(S.GetCho());
			for (size_t i = 0; i < obj.sizeArr; i++)
			{
				obj.arr[i] = " ";
			}
			obj.sizeArr = 0;
			ClearWindow(56, 3, 15, 1, 0);
			ClearWindow(28, 6, 43, 13, 0);

			Navigate_The_Alphabet(obj);
		} break;
		}
	}
}

void ExitProg(BinaryTree &obj)
{
	SetPos(12, 13); SetColor(2); cout << "SAVE CHANGES(ENTER)"; SetColor(15); cout << " | "; SetColor(4); cout << "DO NOT SAVE(ESC)"; SetColor(15);
l:
	switch (int ch = _getch())
	{
	case 27:
		obj.~BinaryTree();
		SetPos(15, 15); SetColor(12); cout << "IMPLEMENTED CHANGES NOT SAVED!"; SetColor(15); Sleep(1500); exit('0');
		break;
	case 13:
	{
		int x1 = 6, x2 = 6, x3 = 8;
		for (size_t i = 0; i < 49; i++)
		{
			SetPos(x2, 15); SetColor_Background(0, 15); cout << " ";
			x2 += 1;
		}
		for (size_t i = 0; i < 49; i++)
		{
			Sleep(80); SetPos(x1, 15); SetColor(204); cout << " ";
			x1 += 1;
		}
		if (obj.SaveToFile(filename1, obj.GetNode())); exit('0');
	}break;
	default:
		goto l;
		break;
	}


}
void Show_Menu_Prog(BinaryTree &obj)
{
	const int Size_Menu = 5; int g[4] = {};

	char Menu_Prog[6][30] = { {"TRANSLATE WORD"},
							  {"ADD TRANSLATION"},
							  {"OPEN VOCABULARY"},
							  {"CLEAR THE LIST"},
							  {"CLOSE THE PROGRAM"} };
	while (true)
	{
		MiniExel_1(S.GetX(), S.GetY(), S.GetWidht(), S.GetHeight());
		SetPos(7, 3);  cout << "  " << Menu_Prog[0] << "  ";
		SetPos(7, 4 + 1 + g[0]); cout << "  " << Menu_Prog[1] << "  ";
		SetPos(7, 5 + 2 + g[0] + g[1]); cout << "  " << Menu_Prog[2] << "  ";
		SetPos(7, 6 + 3 + g[0] + g[1] + g[2]); cout << "  " << Menu_Prog[3] << "  ";
		SetPos(7, 7 + 4 + g[0] + g[1] + g[2] + g[3]); cout << "  " << Menu_Prog[4] << "  ";
		if (S.GetPos() == 0) {
			SetPos(7, 3);
			SetColor(3); cout << (char)17 << " "; SetColor(6); cout << Menu_Prog[0]; SetColor(3); cout << " " << (char)16; SetColor(15);
		}
		if (S.GetPos() == 1) {
			SetPos(7, 4 + 1 + g[0]);
			SetColor(3); cout << (char)17 << " "; SetColor(6); cout << Menu_Prog[1]; SetColor(3); cout << " " << (char)16; SetColor(15);
		}
		if (S.GetPos() == 2) {
			SetPos(7, 5 + 2 + g[0] + g[1]);
			SetColor(3); cout << (char)17 << " "; SetColor(6); cout << Menu_Prog[2]; SetColor(3); cout << " " << (char)16; SetColor(15);
		}
		if (S.GetPos() == 3) {
			SetPos(7, 6 + 3 + g[0] + g[1] + g[2]);
			SetColor(3); cout << (char)17 << " "; SetColor(6); cout << Menu_Prog[3]; SetColor(3); cout << " " << (char)16; SetColor(15);
		}
		if (S.GetPos() == 4) {
			SetPos(7, 7 + 4 + g[0] + g[1] + g[2] + g[3]);
			SetColor(3); cout << (char)17 << " "; SetColor(6); cout << Menu_Prog[4]; SetColor(3); cout << " " << (char)16; SetColor(15);
		}

		if (S.GetCho() == 0)
		{
			g[0] -= 5;
			Translate_Word(obj);
		}
		if (S.GetCho() == 1)
		{
			g[1] -= 5;
			Add_Word_To_Dictionary(obj);
		}
		if (S.GetCho() == 2)
		{
			S.Clear(0); g[1] -= 7;
			Navigate_The_Alphabet(obj);
		}
		if (S.GetCho() == 4)
		{
			S.Clear(0);
			ExitProg(obj);
		}

		switch (short int ch = _getch())
		{
		case 72: {
			if (S.GetPos() >= 1) { S.SetPos(-1); }
		}break;
		case 80: {
			if (S.GetPos() < Size_Menu - 1) { S.SetPos(1); }
		} break;
		case 13: {
			if (S.GetPos() == 0)
			{
				Size_Console(60, 24);
				S.SetCho(S.GetPos());
				system("cls");
				g[0] += 5;
				S.Change_Exel(26, 5);
				MiniExel_2(5, 4, 50, 4);
			}
			if (S.GetPos() == 1)
			{
				Size_Console(60, 24);
				S.SetCho(S.GetPos());
				system("cls");
				g[1] += 5;
				S.Change_Exel(26, 5);
				MiniExel_2(5, 6, 50, 4);
			}
			if (S.GetPos() == 2)
			{
				Size_Console(76, 24);
				S.SetCho(S.GetPos());
				system("cls");
				g[2] += 7;
				S.Change_Exel(42, 10);
				MiniExel_1(5, 8, 21, 6);
			}
			if (S.GetPos() == 4) {
				Size_Console(60, 24);
				S.SetCho(S.GetPos());
				system("cls");
				S.Change_Exel(26, 5);
				MiniExel_2(5, 12, 50, 4);
			}
		} break;
		}
	}
}

void main()
{
	InvisibleÑursor(FALSE);
	CONSOLE_INFO();
	Size_Console(35, 24);
	BinaryTree obj;
	obj.ReadFromFile(filename1);
	S.Fill_Exel(4, 2, 26, 10);
	Show_Menu_Prog(obj);
}