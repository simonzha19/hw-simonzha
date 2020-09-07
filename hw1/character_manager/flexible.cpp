#include "flexible.h"

using namespace std;


// The constructor creates a unique_ptr to a dynamically allocated array of two
// CharacterBlocks using the initialization list syntax. No need to change this
// unless you add fields to the FlexibleCharacterManager.
FlexibleCharacterManager::FlexibleCharacterManager() : blocks(new CharacterBlock[2] {}) {}

char* FlexibleCharacterManager::alloc_chars(size_t n) {
	// TODO: your implementation here

	//Initialize Characterblock and it's size
	CharacterBlock char_block;
	char_block.size = n;
	int position = 0;
	//If we don't have any blocks in use, we can just start from buffer[0]
	if(blocks_in_use == 0){
		char_block.address = &(buffer[0]);
	}

	//If we have 1 block, we must check if there's space from buffer[0] to first address,
	//Then from end of address to buffer[SIZE]
	if(blocks_in_use == 1){
		if(blocks[0].address - &(buffer[0]) >= n){
			char_block.address = &(buffer[0]);
			position = 0;
		}
		else if(&(buffer[BUFFER_SIZE]) - (blocks[0].address + blocks[0].size) >= n){
			char_block.address = blocks[0].address + blocks[0].size;
			position = 1;
		}
		else{
			return nullptr;
		}
	}
	//If we have any blocks in use, we're going to loop through all available blocks
	//And try to find a space in between the block addresses to see if our alloc will fit
	if(blocks_in_use > 1){
		
		bool position_found = false;
		bool at_position_zero = false;

		//Check to see if there's enough space between buffer[0] and our first address
		if(blocks[0].address - &(buffer[0]) > n){
			char_block.address = &(buffer[0]);
			at_position_zero = true;
			position_found = true;
			position = 0;
		}
		//Iterates through all blocks in use, checking to see if the difference between their last address
		//And the next first is enough to fit our allocation
		
			for(int i=0; i < blocks_in_use; i++){
				if(position_found){
					break;
				}
				if(blocks[i + 1].address - (blocks[i].address + blocks[i].size) >= n){
					position = i;
					position_found = true;
					break;
				}
			}
		if(position_found && !at_position_zero){
			char_block.address = blocks[position].address + blocks[position].size;
			position++;
		}
		if(!position_found){
			//Check to see if there's enough space between buffer[BUFFER_SIZE] and our last address
			if(&(buffer[BUFFER_SIZE]) - (blocks[blocks_in_use].address + blocks[blocks_in_use].size) >= n){
				char_block.address = blocks[blocks_in_use].address + blocks[blocks_in_use].size;
				position = blocks_in_use + 1;
			}
			else{
				return nullptr;
			}
		}
	}
	
	
	//DoubleList adapted from GroceryList example
	if(blocks_in_use + 1 >= blocks_size){
		doubleList();
	}
	blocks_in_use++;
	insertInBlocks(char_block, position);

	

	return char_block.address;

}

void FlexibleCharacterManager::free_chars(char* p) {
	// TODO: your implementation here
	if(p < &(buffer[0]) || p > &(buffer[BUFFER_SIZE-1])){
		return;
	}

	bool found = false;
	int position = 0;
	for(int i=0; i <= blocks_in_use; i++){
		if(p == blocks[i].address){
			found = true;
			position = i;
			break;
		}
	}
	if(!found){
		return;
	}
	
	std::fill(blocks[position].address, blocks[position].address + blocks[position].size,'\0');
	deleteInBlocks(position);
	blocks_in_use--;

}


void FlexibleCharacterManager::doubleList(){
    unique_ptr<CharacterBlock[]> old_blocks(blocks.release());
    blocks = make_unique<CharacterBlock[]>(blocks_size*2);
    for (size_t i = 0; i < blocks_in_use; i++){
        blocks[i] = old_blocks[i];
    }
    blocks_size *= 2;
}
void FlexibleCharacterManager::insertInBlocks(CharacterBlock cb, int position){
	unique_ptr<CharacterBlock[]> old_blocks(blocks.release());
	blocks = make_unique<CharacterBlock[]>(blocks_size);
	
	for(int i=0; i < position; i++){
		blocks[i] = old_blocks[i];
	}
	blocks[position] = cb;
	for(int i=position+1; i < blocks_size; i++){
		blocks[i] = old_blocks[i-1];
	}

}
void FlexibleCharacterManager::deleteInBlocks(int position){
	unique_ptr<CharacterBlock[]> old_blocks(blocks.release());
	blocks = make_unique<CharacterBlock[]>(blocks_size);
	
	for(int i=0; i < position; i++){
		blocks[i] = old_blocks[i];
	}
	for(int i=position+1; i < blocks_size; i++){
		blocks[i-1] = old_blocks[i];
	}
}