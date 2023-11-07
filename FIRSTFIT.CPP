#include <iostream.h>
#include <conio.h>

void initialize(int arr[], int size) {
	for(int i = 0; i < size; i++) {
		arr[i] = -1;
	}
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

int min(int memoryBlocks[], int currentIdx, int newIdx) {
	if(memoryBlocks[newIdx] < memoryBlocks[currentIdx]) {
		return newIdx;
	}
	return currentIdx;
}


int max(int memoryBlocks[], int currentIdx, int newIdx) {
	if(memoryBlocks[newIdx] > memoryBlocks[currentIdx]) {
		return newIdx;
	}
	return currentIdx;
}


void firstFit(int memoryBlocks[], int memSize, int procArr[], int procSize) {
	int allocatedBlocks[20];
	initialize(allocatedBlocks, procSize);

	for(int i = 0; i < procSize; i++) {
		for(int j = 0; j < memSize; j++){
			if(memoryBlocks[j] >= procArr[i]) {
				//allocate
				allocatedBlocks[i] = j+1;
				memoryBlocks[j] -= procArr[i];
				break;
			}
		}
	}

	printAllocatedBlocks(allocatedBlocks, procArr, procSize);
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

void bestFit(int memoryBlocks[], int memSize, int procArr[], int procSize) {

	int allocatedBlocks[20];
	initialize(allocatedBlocks, procSize);

	for(int i = 0; i < procSize; i++) {
		for(int j = 0; j < memSize; j++){
			int bstIdx = -1;

			if(memoryBlocks[j] >= procArr[i]) {
				if(bstIdx < 0) {
					bstIdx = j;
				} else {
					bstIdx = min(memoryBlocks, bstIdx, j);
				}
			}

			if(bstIdx != -1) {
				allocatedBlocks[i] = bstIdx;
				memoryBlocks[bstIdx] -= procArr[i];
			}
		}
	}

	printAllocatedBlocks(allocatedBlocks, procArr, procSize);
}


void nextFit(int memoryBlocks[], int memSize, int procArr[], int procSize) {

	int allocatedBlocks[20];
	initialize(allocatedBlocks, procSize);

	int j = 0, endptr = memSize - 1;
	for(int i = 0; i < procSize; i++) {
		while(j < memSize) {
			if(memoryBlocks[j] >= procArr[i]) {
				allocatedBlocks[i] = j+1;
				memoryBlocks[j] -= procArr[i];

				endptr = (j - 1)%memSize;
				break;
			}

			if(j == endptr) {
				endptr = (j - 1)%memSize;
				break;
			}
			j = (j+1)%memSize;
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

	//4,3,5,not allocated
	//firstFit(memoryBlocks, memSize, procArr, procSize);
	//4:200,3:25,5:120,n
	//worstFit(memoryBlocks, memSize, procArr, procSize);
	//2,1,
	//bestFit(memoryBlocks, memSize, procArr, procSize);
	//1,3,4,n
	nextFit(memoryBlocks, memSize, procArr, procSize);

	getch();
	return 0;
}