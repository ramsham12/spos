#include <iostream.h>
#include <conio.h>

int max(int memoryBlocks[], int currentIdx, int newIdx) {
	if(memoryBlocks[newIdx] > memoryBlocks[currentIdx]) {
		return newIdx;
	}
	return currentIdx;
}


void printAllocatedBlocks(int allocatedBlocks[], int procArr[], int procSize) {
	cout << "Processor No\tProcessorSize\tBlock No" << endl;
	for(int i = 0; i < procSize; i++) {
		cout << i+1 << "\t\t" << procArr[i] << "\t\t";
		if(allocatedBlocks[i] != -1) {
			cout << allocatedBlocks[i] << endl;
		} else {
			cout << "Not allocated" << endl;
		}
	}
}


void worstFit(int memoryBlocks[], int memSize, int procArr[], int procSize) {
	int allocatedBlocks[20];
	initialize(allocatedBlocks, procSize);

	for(int i = 0; i < procSize; i++) {
		for(int j = 0; j < memSize; j++){
			int wrstIdx = -1;

			if(memoryBlocks[j] >= procArr[i]) {
				if(wrstIdx < 0) {
					wrstIdx = j;
				} else {
					wrstIdx = max(memoryBlocks, wrstIdx, j);
				}
			}

			if(wrstIdx != -1) {
				allocatedBlocks[i] = wrstIdx;
				memoryBlocks[wrstIdx] -= procArr[i];
			}
		}
	}

	printAllocatedBlocks(allocatedBlocks, procArr, procSize);
}


int main() {
	clrscr();

	int memoryBlocks[] = { 200, 100, 225, 300, 210 };
	int memSize = sizeof(memoryBlocks) / sizeof(memoryBlocks[0]);

	int procArr[] = { 100, 200, 90, 290 };
	int procSize = sizeof(procArr) / sizeof(procArr[0]);

	worstFit(memoryBlocks, memSize, procArr, procSize);

	getch();
	return 0;
}
