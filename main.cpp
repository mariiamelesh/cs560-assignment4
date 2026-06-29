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
int main() {
    TextEditor editor;

    int choice = 0;
	int running = 1;
    while (running) {
        clearConsole(); 
        editor.display();
        
        std::cout
                  << "\n1. Up   2. Down   3. Left   4. Right"
                  << "\n5. Add Text   6. Add Checklist   7. Add Contact"
                  << "\n8. Undo       9. Copy            10. Cut"
                  << "\n11. Paste     12. Write(append)  13. Insert"
                  << "\n14. Delete    15. Search"
                  << "\n16. Encrypt & Save   17. Load & Decrypt"
				  << "\n18. New tab   19. Switch tab"
                  << "\n0. Exit\nChoice: ";
        std::cin >> choice;

        if (choice == 0) break;

        std::string p1, text, mail;
        int key, len;

        switch (choice) {
            case 1: editor.moveUp(); break;
            case 2: editor.moveDown(); break;
            case 3: editor.moveLeft(); break;
            case 4: editor.moveRight(); break;
            
            case 5:
                std::cout << "enter: "; 
				std::cin.ignore(); 
				std::getline(std::cin, text);
                editor.addText(text); 
				break;
            case 6:
                std::cout << "Enter task: "; 
				std::cin.ignore(); 
				std::getline(std::cin, text);
                editor.addChecklist(text, 0); 
				break;
            case 7:
                std::cout << "enter name: "; 
				std::cin.ignore(); 
				std::getline(std::cin, text);
                std::cout << "enter email: "; 
				std::getline(std::cin, mail);
                editor.addContact(text, mail); 
				break;
            
            case 8: 
				editor.undo(); 
				break;
            case 9:
                std::cout << "length: "; 
				std::cin >> len;
                editor.copyText(len); 
				break;
            case 10:
                std::cout << "length: "; 
				std::cin >> len;
                editor.cutText(len);
				break;
            case 11:
                editor.pasteText();
				break;
            case 12:
                std::cout << "enter text: "; 
				std::cin.ignore(); 
				std::getline(std::cin, text);
                editor.writeText(text); 
				break;
            case 13:
                std::cout << "enter text: "; 
				std::cin.ignore(); 
				std::getline(std::cin, text);
                editor.insertText(text); 
				break;
            case 14:
                std::cout << "length: "; 
				std::cin >> len;
                editor.deleteText(len); 
				break;
            case 15:
                std::cout << "text to search: "; 
				std::cin.ignore(); 
				std::getline(std::cin, text);
                editor.searchText(text); 
				break;
                
            case 16:
                std::cout << "path: ";
				std::cin >> p1;
                std::cout << "key: "; 
				std::cin >> key;
                editor.encryptAndSave(p1, "caesar.dll", key);
				break;
            case 17:
                std::cout << "path: "; 
				std::cin >> p1;
                std::cout << "key: "; 
				std::cin >> key;
                editor.loadAndDecrypt(p1, "caesar.dll", key);
				break;
			case 18:
				editor.newTab();
				break;
			case 19:
				int tabId;
				std::cout << "tab number: ";
				std::cin >> tabId;
				editor.switchTab(tabId);
				break;
        }
    }
    return 0;
}