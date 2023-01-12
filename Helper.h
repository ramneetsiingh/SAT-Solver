namespace Helper{
    bool isAlphaNum(const char& c){
        return (c >='a' and c <='z') or (c >='A' and c <='Z') or (c >='0' and c <='9');
    }
    bool isNum(const char& c){
        return (c >='0' and c <='9');
    }
}