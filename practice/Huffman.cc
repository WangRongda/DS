#include <iostream>
#include <fstream>
#include <string.h>
#include <iomanip>

using namespace std;

typedef struct {
	unsigned int weight;
    int parent, lchild, rchild;
    char character;
} HTNode, *HuffmanTree;


// Select two tree with minimum weight from HT, let weight of s1 < s2
void Select(HuffmanTree HT, int nCurrentNodeNum, int &s1, int &s2)
{
	int i;
	for (i = 1; i <= nCurrentNodeNum; i++)
	{
        if (-1 != HT[i].parent) {
			continue;
		}
		s1 = i;
		break;
	}
	for (++i; i <= nCurrentNodeNum; i++)
	{
        if (-1 != HT[i].parent) {
			continue;
		}
		s2 = i;
		break;
	}
    
	for (++i; i <= nCurrentNodeNum; i++)
	{
        if (-1 != HT[i].parent) {
			continue;
		}
        else if (HT[s1].weight <= HT[s2].weight && HT[i].weight < HT[s2].weight)
        {
            s2 = i;
            continue;
        }
        else if (HT[s1].weight > HT[s2].weight && HT[i].weight < HT[s1].weight)
        {
            s1 = s2;
            s2 = i;
        }
	} // for
} // Select

void BuildHfmTree(HuffmanTree &HT, unsigned int *weight, char *ch,
        int nLeafCount)
{
    if (nLeafCount <= 1) {
		return;
	}
	int nNodeCount = 2 * nLeafCount - 1;
	HT = new HTNode[nNodeCount + 1];
	int i;
	HTNode *pEachNode = HT + 1;

    for (i = 1; i <= nLeafCount; ++i, ++pEachNode, ++weight, ++ch) {
        *pEachNode = { *weight, -1, -1, -1, *ch };
	}
	for ( ;i <= nNodeCount; ++i, ++pEachNode) {
        *pEachNode = { 0, -1, -1, -1, '\0' };
	}

    // Build Huffman Tree
	for (i = nLeafCount + 1; i <= nNodeCount; ++i) {
		int s1, s2;
        // select two order of tree with least weight
		Select(HT, i - 1, s1, s2);
		HT[s1].parent = i;
		HT[s2].parent = i;

		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
    HT[0] = HT[nNodeCount]; // Copy root to HT[0] for handy

    // print HT
    for (int k = 0; k <= nNodeCount; k++)
    {
        cout << k << " | " ;
        cout << setw(5) << HT[k].weight;
        cout << setw(10) << HT[k].parent;
        cout << setw(10) << HT[k].lchild;
        cout << setw(10) << HT[k].rchild;
        cout << setw(10) << HT[k].character;
        cout << endl;
    }
} //BuildHfmTree

void InitHfmTree(HuffmanTree &HT, int &nChCount)
{
	cin >> nChCount;
    char ch[nChCount]; // Store character from input
    unsigned int weight[nChCount]; // Store weight from input
    ofstream hfmTree("hfmTree");
    hfmTree << nChCount;
	for (int i = 0; i < nChCount; i++)
	{
        cin >> ch[i];
        hfmTree << ch[i];
	}
    hfmTree << endl;
	for (int i = 0; i < nChCount; i++)
	{
		cin >> weight[i];
        hfmTree << weight[i];
	}
    hfmTree << endl;
	hfmTree.close();
    BuildHfmTree(HT, weight, ch, nChCount);
}

void readHfmFile(HuffmanTree &HT, int &nChCount)
{
    ifstream hfmTree("hfmTree");
    hfmTree >> nChCount;
    unsigned int weight[nChCount];
    char ch[nChCount + 1];
	for (int i = 0; i < nChCount; i++)
	{
        hfmTree.get(ch[i]);
	}
	for (int i = 0; i < nChCount; i++)
	{
        hfmTree >> weight[i];
	}
    hfmTree.close();
    BuildHfmTree(HT, weight, ch, nChCount);
}

void Encoding(const HuffmanTree HT, int nLeafCount)
{
    char **HC = new char *[nLeafCount + 1]; // Store every Leaf's encode
    // The Length of encode string is nLeafCount - 1 at most
    int nEncodeLen = nLeafCount; 
     // Store current leaf node's encode temporary
    char *encodeTmp = new char[nEncodeLen];
    encodeTmp[nEncodeLen - 1] = '\0';

    // Encode every leaf(character) and save to HC
    for (int nCLeafOrder = 1; // Current Leaf node order
            nCLeafOrder <= nLeafCount;
            ++nCLeafOrder
            ) 
    {
        int start = nEncodeLen - 1;
        int nCNodeOrder = nCLeafOrder; // Current node order in path to root
                                       // while encoding
        int nCParentOrder = HT[nCNodeOrder].parent;

        //Encode current leaf from leaf node to root
        for (; -1 != nCParentOrder; // Current node is not root of HfmTree
                nCNodeOrder = nCParentOrder, nCParentOrder = 
                HT[nCParentOrder].parent
                )
		{
            if (nCNodeOrder == HT[nCParentOrder].lchild) {
                encodeTmp[--start] = '0';
			}
			else {
                encodeTmp[--start] = '1';
			}
		}
        HC[nCLeafOrder] = new char(nEncodeLen - start);
        strcpy(HC[nCLeafOrder], &encodeTmp[start]);
	}
    delete encodeTmp;

    // Print Encoding Table
    for (int k = 1; k <= nLeafCount; k++)
	{
        cout << HT[k].character << " ";
        cout << HC[k] << endl;
	}
	
    //  Encoding string in file "ToBeTran" to binary code and save in "CodeFile"
    //  using the HC table
    ifstream ToBeTran("ToBeTran"); // read
    ofstream CodeFile("CodeFile"); // write
    char ch;
    while (ToBeTran.get(ch))
    {
        for (int i = 1; i <= nLeafCount; ++i) {
            if (ch == HT[i].character) {
                CodeFile << HC[i];
                cout << HC[i];
                break;
            }
        }
    }
    ToBeTran.close();
    CodeFile.close();
} //Encoding()

// Decode binary code in file "CodeFile" to string saving in file "TextFile"
// using Huffman Tree
void Decoding(HuffmanTree HT)
{
    string strCode;
    ifstream CodeFile("CodeFile");
    ofstream TextFile("TextFile");
    CodeFile >> strCode;
    int nCNodeOrder = 0;  // Order of root in HT
    for (int i = 0;'\0' != strCode[i]; ++i)
    {
        if ('0' == strCode[i]) {
            nCNodeOrder = HT[nCNodeOrder].lchild;
        }
        else if ('1' == strCode[i]) {
            nCNodeOrder = HT[nCNodeOrder].rchild;
        }

        // Current node is leaf
        if (-1 == HT[nCNodeOrder].lchild) {
            cout << HT[nCNodeOrder].character;
            TextFile << HT[nCNodeOrder].character;
            nCNodeOrder = 0;  // return to root
        }
    }
    TextFile.close();
    CodeFile.close();
}
	
void Print()
{
	char code[51];
    ifstream CodeFile("CodeFile");
    ofstream CodePrin("CodePrin");

    while (CodeFile.get(code, 51)) {
        cout << code;
        cout << endl;
        CodePrin << code;
        CodePrin << endl;
    }
    CodeFile.close();
    CodePrin.close();
}

// ao ru shu print
void AoRuBiao(HuffmanTree HT, int nCNodeOrder, int t, ofstream &TreePrint)
{
    int i;
    if (-1 != nCNodeOrder)
    {
        AoRuBiao(HT, HT[nCNodeOrder].rchild, t + 5, TreePrint);
        for (i = 0; i < t; i++)
        {
            cout << " ";
            TreePrint << " ";
        }
        cout << setw(5) << HT[nCNodeOrder].weight << endl;
        TreePrint << HT[nCNodeOrder].weight << endl;
        AoRuBiao(HT, HT[nCNodeOrder].lchild, t + 5, TreePrint);
    }
}
void TreePrint(HuffmanTree HT)
{
    ofstream TreePrint("TreePrint");
    AoRuBiao(HT, 0, 0, TreePrint);
    TreePrint.close();
}


void printMenu()
{
	cout << "\n I: Initialization." << endl;
	cout << " E: Encoding." << endl;
	cout << " D: Decoding." << endl;
	cout << " P: Print." << endl;
    cout << " T: TreePrint." << endl;
	cout << " Q: Quit." << endl;
	cout << "\n Input: ";
}

int main(int argc, const char *argv[])
{
	char input;
	HuffmanTree HT = NULL;
    int nLeaf = 0;
	char code[100] = { 0 };
	do {
		printMenu();
		cin >> input;
		cout << endl;
		switch (input) {
            case 'I': InitHfmTree(HT, nLeaf); break;
			case 'E': 
					  if (NULL == HT) {
                        readHfmFile(HT, nLeaf);
					  }
                      Encoding(HT, nLeaf);
					  break;
            case 'D': Decoding(HT); break;
			case 'P': Print(); break;
            case 'T': TreePrint(HT); break;
            case 'Q': break;
			default: cout << "Error Input." << endl; break;
		}
	} while ('Q' != input);
	return 0;
}
