#include <iostream>
#include "engine/board.h"

int main() {
    Board b;
    for(auto y=0; y<8; y+=1){
        for(auto x=0; x<8; x+=1){
            std::cout << b.at(x, y).fen();
        }
        std::cout << "\n";
    }
    return 0;
}
