#include "dice.h"
//This feels a little pointless, but sticking to convention for future-proofness
using namespace dice;

int die::roll(){
    return distribution(mt);
}