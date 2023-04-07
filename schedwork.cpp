#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool makeSched(size_t hor, size_t ver, size_t count, size_t need, vector<size_t> move, 
	const AvailabilityMatrix& avail, DailySchedule& sched);
// Add your implementation of schedule() and other helper functions here
bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
		//Add code below
		//make the vector 
vector<size_t> move(avail[0].size()); std::fill(move.begin(), move.end(), 0);
    // make sched
std::vector<Worker_T> vec(dailyNeed);
	DailySchedule curr(avail.size(), vec);
bool result = makeSched(size_t{}, size_t{}, maxShifts, dailyNeed, move, avail, curr);
	sched = curr;
	return result;
}
bool makeSched(size_t hor, size_t ver, size_t count, size_t need, vector<size_t> move, 
	const AvailabilityMatrix& avail, DailySchedule& sched){
	switch (hor == avail.size()) {
    case true:
        return true;
    default:
    bool found = false;
        for (size_t j = 0; avail[0].size() > j ; j++) {
    if (avail[hor][j] == 1 && count != move[j]) {
        sched[hor][ver] = j;
        move[j] = move[j] + 1;
        //finish sched
        const size_t vertical_count = sched[0].size();
        size_t clength = (ver + 1) % vertical_count;
        size_t hlength = hor + (ver + 1) / vertical_count;
        found = makeSched(hlength, clength, count, need, move, avail, sched);
        if (found) {
            return true;
        } else {
            //delete
            move[j]--;
            sched[hor][ver] = 0;
        }
    }
}
return found;
}
}