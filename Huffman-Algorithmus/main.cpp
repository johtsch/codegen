#include <iostream>
#include "huffman.hpp"

int main(){
    HuffmanCoder hc;

    hc.addElement('c', 0.1638);
    hc.addElement('v', 0.0454);
    hc.addElement('w', 0.0871);
    hc.addElement('u', 0.1957);
    hc.addElement('r', 0.4209);
    hc.addElement('z', 0.0871);

    hc.fireup();

    std::cout << "c: "<< hc.gcocStr('c') << std::endl;
    std::cout << "v: "<< hc.gcocStr('v') << std::endl;
    std::cout << "w: "<< hc.gcocStr('w') << std::endl;
    std::cout << "u: "<< hc.gcocStr('u') << std::endl;
    std::cout << "r: "<< hc.gcocStr('r') << std::endl;
    std::cout << "z: "<< hc.gcocStr('z') << std::endl;
    
}