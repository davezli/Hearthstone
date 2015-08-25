#include <vector>
#include <cstdlib>
#include <iostream>

using namespace std;

// Set up constants: 
	int DEBUG = 0;

	// disenchanting 
    int deC = 5;
    int deGC = 50;
    int deR = 20;
    int deGR = 100;
    int deE = 100;
    int deGE = 400;
    int deL = 400;
    int deGL = 1600;

	// enchanting
    int eC = 40;
    int eR = 100;
    int eE = 400;
    int eL = 1600;

	// rates are 10000 * %
	int rateC = 6997;
	int rateGC = 147;
	int rateR = 2140;
	int rateGR = 138;
	int rateE = 429;
	int rateGE = 31;
	int rateL = 108;
	int rateGL = 11;

	// tgt nums
	int numC = 39;
	int numR = 37;
	int numE = 26;
	int numL = 21;
// done constants

// Open packs until enough dust to craft all missing cards
int open_to_completion() {
	
	int pack = 0;

	vector<int> arrC(numC,0);
	vector<int> arrR(numR,0);
	vector<int> arrE(numE,0);
	vector<int> arrL(numL,0);

    int currdust = 0;
    int goaldust = numC*eC+numR*eR+numE*eE+numL*eL;

    int rates[8] = {rateC,rateGC,rateR,rateGR,rateE,rateGE,rateL,rateGL};
    for(int i = 1; i < 8; i++) {
        rates[i] += rates[i-1];
    }

	while(currdust < goaldust) {
		pack++;
		// open 5 cards
		for(int card = 0; card < 5; card++) {
			int type = rand() % 10001;
			// determine the type of card 
			if(type < rates[0]) {
				int id = rand() % numC;
				if(arrC[id] > 2) {
					currdust += deC;
				}
				else {
					arrC[id]++;
					goaldust -= eC;
				}
			}
			else if (type < rates[1]) {
				currdust += deGC;
			}
            else if(type < rates[2]) {
                int id = rand() % numR;
                if(arrR[id] > 2) {
                    currdust += deR;
                }
                else {
                    arrR[id]++;
                    goaldust -= eR;
                }
            }   
            else if (type < rates[3]) {
                currdust += deGR;
            }
            else if(type < rates[4]) {
                int id = rand() % numE;
                if(arrE[id] > 2) {
                    currdust += deE;
                }
                else {
                    arrE[id]++;
                    goaldust -= eE;
                }
            }
            else if (type < rates[5]) {
                currdust += deGE;
            }
            else if(type < rates[6]) {
                int id = rand() % numL;
                if(arrL[id] > 2) {
                    currdust += deL;
                }
                else {
                    arrL[id]++;
                    goaldust -= eL;
                }
            }
            else if (type < rates[7]) {
				if(DEBUG) 
					cout << "Opened a GOLDEN LEGENDARY in pack " << pack << endl;
                currdust += deGL;
            }
		}
	}
	return pack;		 
}

int main() {
//	DEBUG = 1;
	srand(time(0));
	int trials = 10000;
	int total_packs = 0;
	for(int i = 0; i < trials; i++) {
		total_packs += open_to_completion();
	}
	cout << "It will take " << (total_packs/trials) << " packs to complete TGT." << endl;
}
