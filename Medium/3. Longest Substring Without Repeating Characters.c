int lengthOfLongestSubstring(char* s) {
    int length = strlen(s);
    if(length == 0) return 0;    
    int count = 0;    
    int ans = 0;
    int* check = calloc(95 , sizeof(int));
    for(int i = 0  ; i < length ; i++){
        memset(check , 0 ,  95 * sizeof(int));
        count = 0;
        *(check + (s[i] - ' ')) = 1;
        for(int j = i + 1 ; j < length ; j++){
            if(*(check + (s[j] - ' ')) == 1) break;
            else {
                *(check + (s[j] - ' ')) = 1;
                count++;
            }
            if(count > ans) ans = count;
        }
    }
    return ans + 1;
}
