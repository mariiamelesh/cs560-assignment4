#include "textEditor.h"
#include <iostream>
#include <cstdlib>

void clearConsole() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}
int input() {
    int val;
    while (!(std::cin >> val)) {
        std::cin.clear();
        std::cin.ignore(1000, '\n'); 
        std::cout << "wrong, try again XD ";
    }
    return val;
}

int main() {
    TextEditor editor;

    int running = 1;
    while (running) {
		system("pause");
        clearConsole(); 
        editor.display();
        std::cout << "1. Up\n2. Down\n3. Left\n4. Right\n5. Add Text\n6. Add Checklist\n7. Toggle Check\n8. Add Contact\n9. Undo\n10.Redo\n11.Copy\12. Cut\n13. Paste\n14. Write(append)\n15. Insert\n16. Delete\n17. Search\n18. Encrypt and save\n19. Load and decrypt\n20. New tab\n21. Switch tab\n0. Exit\nChoice: ";
        int choice = input();

        if (choice == 0) {
			running = 0;
			break;
		}

        std::string path;
		std::string text;
		std::string mail;
        int key, len;

        switch (choice) {
            case 1: 
				editor.moveUp(); 
				break;
            case 2: 
				editor.moveDown(); 
				break;
            case 3: 
				editor.moveLeft(); 
				break;
            case 4: 
				editor.moveRight(); 
				break;

            case 5:
                std::cout << "enter text: "; 
                std::cin.ignore(); 
                std::getline(std::cin, text);
                editor.addText(text); 
                break;
            case 6:
                std::cout << "enter task: "; 
                std::cin.ignore(); 
                std::getline(std::cin, text);
                editor.addChecklist(text); 
                break;
			case 7: {
				editor.toggleChecklist(); 
				break;
			}
            case 8:
                std::cout << "enter name: "; 
                std::cin.ignore(); 
                std::getline(std::cin, text);
                std::cout << "enter email: "; 
                std::getline(std::cin, mail);
                editor.addContact(text, mail); 
                break;
            
            case 9: 
				editor.undo();
				break;
            case 10: 
				editor.redo(); 
				break;
            case 11:
                std::cout << "length: "; 
                len = input(); 
                editor.copyText(len); 
                break;
            case 12:
                std::cout << "length: "; 
                len = input(); 
                editor.cutText(len);
                break;
            case 13:
                editor.pasteText();
                break;
            case 14:
                std::cout << "enter text: "; 
                std::cin.ignore(); 
                std::getline(std::cin, text);
                editor.writeText(text); 
                break;
            case 15:
                std::cout << "enter text: "; 
                std::cin.ignore(); 
                std::getline(std::cin, text);
                editor.insertText(text); 
                break;
            case 16:
                std::cout << "length: "; 
                len = input(); 
                editor.deleteText(len); 
                break;
            case 17:
                std::cout << "text to search: "; 
                std::cin.ignore(); 
                std::getline(std::cin, text);
                editor.searchText(text); 
				break;
                
            case 18:
                std::cout << "path: ";
                std::cin >> path;
                std::cout << "key: "; 
                key = input();
                editor.encryptAndSave(path, key);
                break;
            case 19:
                std::cout << "path: "; 
                std::cin >> path;
                std::cout << "key: "; 
                key = input();
                editor.loadAndDecrypt(path, key);
				break;
            case 20:
                editor.newTab();
                break;
            case 21:{
                std::cout << "tab number: ";
                int tabId = input();
                editor.switchTab(tabId);
                break;
			}
        }
    }
    return 0;
}