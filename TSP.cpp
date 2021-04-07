#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Node {
public:
	int m_iLevel;
	int* m_pPath;
	int m_iBound;

	Node(int _iLevel, int* _pPath, int _iN) {
		m_iLevel = _iLevel;

		m_pPath = new int[_iN + 1];

		if (_pPath == NULL) {
			for (int i = 0; i <= _iN; i++) {
				m_pPath[i] = 0;
			}
		}
		else {
			for (int i = 0; i <= _iN; i++) {
				m_pPath[i] = _pPath[i];
			}
		}
	}

	void bound(int _iN, int** _pMatrix) {
		int iB = 0;
		bool* arrPassRow = new bool[_iN + 1];
		for (int i = 1; i <= _iN; i++) {
			arrPassRow[i] = false;
		}

		for (int i = 1; i <= m_iLevel; i++) {
			iB += _pMatrix[m_pPath[i]][m_pPath[i - 1]];
			arrPassRow[m_pPath[i - 1]] = true;
		}

		for (int y = 1; y <= _iN; y++) {
			if (arrPassRow[y] == true)
				continue;

			int min = 9000;

			for (int x = 1; x <= _iN; x++) {

				if (_pMatrix[x][y] != 0 && _pMatrix[x][y] < min) {
					min = _pMatrix[x][y];
				}
			}

			iB += min;
		}

		m_iBound = iB;
	}

	int calLength(int _iN, int** _pMatrix) {
		int iB = 0;
		for (int i = 1; i <= _iN; i++) {
			iB += _pMatrix[m_pPath[i]][m_pPath[i - 1]];
		}

		return iB;
	}

	void addRemain(int _iN) {
		bool* check = new bool[_iN + 1];
		for (int i = 1; i <= _iN; i++) {
			check[i] = false;
		}

		for (int i = 0; i < m_iLevel; i++) {
			check[m_pPath[i]] = true;
		}

		int remain = 0;
		for (int i = 1; i <= _iN; i++) {
			if (check[i] == false) {
				remain = i;
				break;
			}
		}

		m_pPath[m_iLevel] = remain;
		m_pPath[m_iLevel + 1] = 1;
	}
};

class Heap {
private:
	Node** m_pArr;
	int m_iHeapSize;
	int CAPACITY;

public:
	Heap() {
		CAPACITY = 100000;

		m_pArr = new Node*[CAPACITY];

		for (int i = 0; i < CAPACITY; i++) {
			m_pArr[i] = NULL;
		}

		m_iHeapSize = 0;
	}

	void shiftdown(int index) {
		Node* siftkey = m_pArr[index];
		int parent = index;
		int smallchild;
		bool found = false;
		while (2 * parent <= m_iHeapSize && !found)
		{
			if (2 * parent < m_iHeapSize && m_pArr[2 * parent]->m_iBound > m_pArr[2 * parent]->m_iBound + 1)
				smallchild = 2 * parent + 1;
			else
				smallchild = 2 * parent;
			if (siftkey->m_iBound > m_pArr[smallchild]->m_iBound)
			{
				m_pArr[parent] = m_pArr[smallchild];
				parent = smallchild;
			}
			else
				found = true;
		}
		m_pArr[parent] = siftkey;
	}

	void insert(Node* pNode) {
		m_pArr[m_iHeapSize + 1] = pNode;
		m_iHeapSize++;
		for (int i = m_iHeapSize; i >= 1; i = i / 2)
		{
			if (i == 1)
			{
				m_pArr[i] = pNode;
				break;
			}
			else if (pNode->m_iBound > m_pArr[i / 2]->m_iBound)
			{
				m_pArr[i] = m_pArr[i / 2];
			}
			else
			{
				m_pArr[i] = pNode;
				break;
			}
		}
	}

	Node* remove() {
		Node* temp = m_pArr[1];
		m_pArr[1] = m_pArr[m_iHeapSize];
		m_iHeapSize--;
		shiftdown(1);
		return temp;
	}


	bool isEmpty() {
		return m_iHeapSize == 0;
	}

};

class TSP {
private:
	Heap* m_kheap;
	int m_iN;
	int m_iMinlength;
	int** m_pMatrix;
	int* m_pOpttour;

public:
	TSP() {
		m_kheap = new Heap();
		m_iMinlength = 9000;
		m_pOpttour = NULL;
	}

	void inputFile(ifstream& _ifStream) {
		_ifStream >> m_iN;

		m_pMatrix = new int*[m_iN + 1];
		for (int i = 1; i <= m_iN; i++) {
			m_pMatrix[i] = new int[m_iN + 1];
		}

		for (int y = 1; y <= m_iN; y++) {
			for (int x = 1; x <= m_iN; x++) {
				_ifStream >> m_pMatrix[x][y];
			}
		}
	}

	void travel() {
		Node* v = new Node(0, NULL, m_iN);
		v->m_pPath[v->m_iLevel] = 1;
		v->bound(m_iN, m_pMatrix);

		m_kheap->insert(v);

		while (m_kheap->isEmpty() == false) {
			v = m_kheap->remove();

			if (v->m_iBound < m_iMinlength) {

				if (v->m_iLevel == m_iN - 2) {
					Node* u = new Node(v->m_iLevel + 1, v->m_pPath, m_iN);
					u->m_pPath[u->m_iLevel] = 1;
					u->bound(m_iN, m_pMatrix);
					u->addRemain(m_iN);

					int iBound = u->calLength(m_iN, m_pMatrix);
					if (iBound < m_iMinlength) {
						m_iMinlength = iBound;
						m_pOpttour = u->m_pPath;
					}
				}
				else {
					for (int i = 2; i <= m_iN; i++) {
						bool cont = false;
						for (int k = 1; k <= v->m_iLevel; k++) {
							if (v->m_pPath[k] == i) {
								cont = true;
								break;
							}
						}
						if (cont == true)
							continue;

						Node* u = new Node(v->m_iLevel + 1, v->m_pPath, m_iN);
						u->m_pPath[u->m_iLevel] = i;
						u->bound(m_iN, m_pMatrix);

						if (u->m_iBound < m_iMinlength)
							m_kheap->insert(u);
					}
				}
			}
		}
	}

	void output() {

		ofstream ofStream;
		ofStream.open("output.txt");

		ofStream << m_iMinlength << endl;

		for (int i = 0; i <= m_iN; i++) {
			ofStream << m_pOpttour[i] << endl;
		}

		ofStream.close();
	}

};

void main() {

	string strFileName; 
	ifstream ifStream; 
	TSP* kTsp = new TSP();

	cout << "input file name?";
	cin >> strFileName;

	ifStream.open(strFileName);

	kTsp->inputFile(ifStream);

	ifStream.close();

	kTsp->travel();

	kTsp->output();
}