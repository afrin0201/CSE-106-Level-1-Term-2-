#include <iostream>
#include <fstream>
#include <string>
#include "listBST.hpp"
using namespace std;

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        cerr << "Usage: filename" << "\n";
        return 1;
    }
    ifstream in_file(argv[1]);
    if (!in_file)
    {
        cerr << "Unable to open file\n";
        return 1;
    }

    BST<string, int> *bst1 = new ListBST<string, int>();
    if (!bst1)
    {
        cerr << "Memory allocation failed\n";
        return 2;
    }
    BST<string, int> *bst2 = new ListBST<string, int>();
    if (!bst2)
    {
        cerr << "Memory allocation failed\n";
        delete bst1; // Clean up previously allocated memory
        return 3;
    }

    int n;
    in_file >> n;
    string str;
    for (int i = 0; i < n; ++i)
    {
        in_file >> str;
        if (bst1->find(str))
        {
            int count = bst1->get(str);
            bst1->update(str, count + 1);
        }
        else
        {
            bst1->insert(str, 1);
        }
        // TODO: Implement the logic to read Phil's words
        // Start your code here

        // End your code here
    }
    for (int i = 0; i < n; ++i)
    {
        // TODO: Implement the logic to read Claire's words
        // Start your code here
        in_file >> str;
        if (bst2->find(str))
        {
            int count = bst2->get(str);
            bst2->update(str, count + 1);
        }
        else
        {
            bst2->insert(str, 1);
        }
        // End your code here
    }

    // TODO: Implement the logic to print the initial state of both hands
    // Start your code here
    cout << "Phil's words:" << endl;
    bst1->print('I');
    cout << endl;
    cout << "Claire's words:" << endl;
    bst2->print('I');
    // End your code here
    cout << "\nGame starts!\n\n";
    cout << "==============================\n";

    while (true)
    {
        string word;
        in_file >> word;
        if (bst1->find(word))
        {
            cout << "Phil has " << word << "!" << endl;
            int count = bst1->get(word);

            if (count == 1)
            {
                bst1->remove(word);
            }
            else
            {
                bst1->update(word, count - 1);
            }
        }
        if (bst2->find(word))
        {
            cout << "Claire has " << word << "!" << endl;
            int count = bst2->get(word);
            if (count == 1)
            {
                bst2->remove(word);
            }
            else
            {
                bst2->update(word, count - 1);
            }
        }
        if (bst1->size() == 0 && bst2->size() != 0)
        {
            cout << "Phil wins!" << endl;
            break;
        }
        else if (bst2->size() == 0 && bst1->size() != 0)
        {
            cout << "Claire wins!" << endl;
            break;
        }
        else if (bst1->size() == 0 && bst2->size() == 0)
        {
            cout << "Game tied!" << endl;
            break;
        }
        cout << endl;
        cout << "Phil's remaining words:" << endl;
        bst1->print('I');
        cout << endl;
        cout << "Claire's remaining words:" << endl;
        bst2->print('I');
        cout << endl;
        // TODO: Implement the logic to process the game turn and print both hands after each turn
        // Start your code here

        // End your code here
        cout << "==============================\n";
    }

    in_file.close();
    delete bst1;
    delete bst2;
    return 0;
}