#include <iostream>
#include "FileSystem.h"

using namespace std;

int main() {
#ifdef _DEBUG
    //checking for memory leaks when the application ends 
    _onexit(_CrtDumpMemoryLeaks);
#endif
    // set random number generator to be used for making random file sizes
    srand(static_cast<unsigned int>(time(0)));
    FileSystem myFileSystem;
    string userInput;


    std::cout << "\\ :> dir\n";
    myFileSystem.listCurrentDirectory();
    

    //take in user input to handle command
    std::cout << "\n Fake File System. Enter commands or 'exit' to quit.\n";
    while (true) {
        std::cout << ":> "; 
        getline(std::cin, userInput); 

        //passes userinput to be handled by filesystem class
        myFileSystem.ProcessUserInput(userInput); // Process the input
    }

    // if user enters exist :
    std::cout << "Exiting Fake File System.\n";
    return 0;
}
