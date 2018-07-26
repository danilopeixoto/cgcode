#include <iostream>
#include <Global.h>

// Teste
int main(int argc, char ** argv) {
	Vector3 u(-1, 0, 0);
	Vector3 v(0, 0, 1);
	
	std::cout << "Produto vetorial u x v: " << u.cross(v) << std::endl;
	std::cout << "Comprimento de u: " << u.length() << std::endl;
	
	return 0;
}
