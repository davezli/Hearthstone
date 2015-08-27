#include <vector>
#include <cstdlib>
#include <algorithm>
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

// DEBUG STUFF
int openedC = 0;
int openedGC = 0;
int openedR = 0;
int openedGR = 0;
int openedE = 0;
int openedGE = 0;
int openedL = 0;
int openedGL = 0;
int openedDust = 0;
int neededDust = 0;

// Open packs until enough dust to craft all missing cards
int open_to_completion() {

    int pack = 0;

    vector<int> arrC(numC,0);
    vector<int> arrR(numR,0);
    vector<int> arrE(numE,0);
    vector<int> arrL(numL,0);

    int currdust = 0;
    int goaldust = 2*numC*eC+2*numR*eR+2*numE*eE+numL*eL;

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
				openedC++;
                if(arrC[id] >= 2) {
                    currdust += deC;
                }
                else {
                    arrC[id]++;
                    goaldust -= eC;
                }
            }
            else if (type < rates[1]) {
                currdust += deGC;
				openedGC++;
            }
            else if(type < rates[2]) {
                int id = rand() % numR;
				openedR++;
                if(arrR[id] >= 2) {
                    currdust += deR;
                }
                else {
                    arrR[id]++;
                    goaldust -= eR;
                }
            }
            else if (type < rates[3]) {
                currdust += deGR;
				openedGR++;
            }
            else if(type < rates[4]) {
                int id = rand() % numE;
				openedE++;
                if(arrE[id] >= 2) {
                    currdust += deE;
                }
                else {
                    arrE[id]++;
                    goaldust -= eE;
                }
            }
            else if (type < rates[5]) {
                currdust += deGE;
				openedGE++;
            }
            else if(type < rates[6]) {
                int id = rand() % numL;
				openedL++;
                if(arrL[id] >= 2) {
                    currdust += deL;
                }
                else {
                    arrL[id]++;
                    goaldust -= eL;
                }
            }
            else if (type < rates[7]) {
				openedGL++;
                currdust += deGL;
            }
        }
    }
	openedDust += currdust;
	neededDust += goaldust;
    return pack;
}

int main() {
//	DEBUG = 1;
    srand(time(0));
    int trials = 10000;
    int total_packs = 0;
	int worst = 0;
	int best = 1000;
    for(int i = 0; i < trials; i++) {
        int buffer = open_to_completion();
		total_packs += buffer;
		worst = max(worst,buffer);
		best = min(best,buffer);
    }
	cout << "it will take from " << best << " to " << worst << " packs to complete TGT, ";
	cout << "with an average of " << (total_packs/trials) << " packs." << endl;
	if(DEBUG) {
		cout << "I opened " << (openedC/trials) << " commons." << endl;
		cout << "I opened " << (openedGC/trials) << " golden commons." << endl;
		cout << "I opened " << (openedR/trials) << " rares." << endl;
		cout << "I opened " << (openedGR/trials) << " golden rares." << endl;
		cout << "I opened " << (openedE/trials) << " epics." << endl;
		cout << "I opened " << (openedGE/trials) << " golden epics." << endl;
		cout << "I opened " << (openedL/trials) << " legendaries." << endl;
		cout << "I opened " << (openedGL/trials) << " golden legendaries." << endl;
		cout << "I opened " << (openedDust/trials) << " dust." << endl;
		cout << "I needed " << (neededDust/trials) << " dust." << endl;
	}		
}

