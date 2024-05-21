#include "practiceMap.h"

template <typename keyType, typename valType>
ostream & operator<<(ostream & out, const practiceMap<keyType, valType> & toPrint) {
    for(int i = 0; i < toPrint.TABLE_SIZE; i++) {
        
        
        out << setw(7) << i << ":";
        out << setw(11) << "{ " <<
    }
}