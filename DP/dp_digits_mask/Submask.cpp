// time -> O(3^n)
// Enumerates all submasks of a given bitmask in decreasing order.
for(int mask = 0 ; mask < (1<<n) ; ++mask)
    for(int sub = mask ; sub ; sub = (sub - 1) & mask) { // loop submask

        // process

    }
}

