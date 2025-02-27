#include <stdio.h>

unsigned char p(unsigned char x) {
    unsigned char
        s[] = {1,221,146,79,147,153,11,68,214,215,78,220,152,10,69},
        k[] = {0,32,50,6,20,4,22,34,48,16,2,54,36,52,38,18,0};    
    
    if(x) {
        unsigned char l = 1, a = 2;
        while(a != x) {
            a = (a << 1) ^ ((a >> 7) * 29);
            l++;
        }
        return (l % 17) 
            ? (252 ^ k[l % 17] ^ s[l / 17]) 
            : (252 ^ k[l / 17]);
    }
    return 252;
}

unsigned char p_alt(unsigned char x) {
    char* k = "@`rFTDVbpPBvdtfR@\xacp?\xe2>4\xa6\xe9{z\xe3q5\xa7\xe8";
    int l = 256, b = 17;
    while(--l * x ^ l)
        x = (x << 1) ^ (x >> 7) * 285;
    return l % b ? k[l % b] ^ k[b + l/b] ^ b : k[l/b] ^ 188;
}

int main() {
    int differences = 0;
    
    printf("Original vs Alternative S-box comparison:\n");
    printf("%4s | %3s | %3s | %s\n", "Byte", "p()", "alt", "Status");
    printf("-----|-----|-----|--------\n");
    
    for(int i = 0; i < 256; i++) {
        unsigned char res1 = p(i);
        unsigned char res2 = p_alt(i);
        
        if(i % 16 == 0) printf("\n");  // New line every 16 values
        
        printf("%3d: %3d vs %3d | %s\n", 
               i, 
               res1, 
               res2,
               (res1 == res2) ? "OK" : "DIFF");
        
        if(res1 != res2) differences++;
    }
    
    printf("\nTotal differences: %d\n", differences);
    return 0;
}
