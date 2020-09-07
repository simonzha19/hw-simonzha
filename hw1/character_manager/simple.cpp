#include "simple.h"
#include <algorithm>

using namespace std;


char* SimpleCharacterManager::alloc_chars(size_t size) {
	// TODO: your implementation here
	if((first_available_address + size) > &(buffer[BUFFER_SIZE-1])){
		return nullptr;
	}
	else{
		char* start_address = first_available_address;
		first_available_address = first_available_address + size;
		return start_address;
	}
}

void SimpleCharacterManager::free_chars(char* address) {
	// TODO: your implementation here
	if(address == nullptr || address < &(buffer[0]) || address > &(buffer[BUFFER_SIZE-1])){
		return;
	}
	first_available_address = address;
	std::fill(address, &(buffer[BUFFER_SIZE - 1]),'\0');
	
}
