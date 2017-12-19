/// Important Notes for Hashing

/**
    1. Single Hashing:
    Mod = large prime number(Ex: 1e9+7)
    B = base (the smallest prime greater than total distinct characters)(Ex: 29)
    For string "abcba"
    Hash = (a*(B^0) + b*(B^1) + c*(B^2) + b*(B^3) + a*(B^4))%Mod

    2. Double Hashing:
    Maintain two hash value for each string using above approach.
    For the second hash, use different Mod and B.
    2nd B should be twin prime with first B(Ex: 31)
    2nd Mod should be twin prime with first Mod(Ex: 1e9+9)

    3. Hashing If Position Doesn't Matter (Only the number of occurrence matters):
    Mod and B same as above
    For string "abcba" (Which is same as "aabbc")
    Hash = ((B^a) + (B^b) + (B^c) + (B^b) + (B^a))%Mod


    4. If string s is same as it's rotation (Circular)
    Hash = Sum over the hash of all the adjacent pair of characters
**/

/// Barnestaine String Hashing
/// Another useful technique to get hash of a string

LLU barnestaine(const char* s) {
    LLU hash = 0, c;
    while((c = *s++)){
        hash = ((hash << 5) + hash) ^ c;
    }
    return hash;
}
