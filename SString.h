//
// Created by Alex Shockley on 9/2/2020.
//

#ifndef S20_PA01_SENTIMENTANALYSIS_SSTRING_H
#define S20_PA01_SENTIMENTANALYSIS_SSTRING_H


class SString {
private:
    char* data;
    int size;
    int maxSize;
public:
    SString();
    SString(char newWord[]);
    ~SString();
    char *getData() const;
    void setString(char *string);
    int getSize() const;
    SString& operator=(const SString &);
    bool contains(char check[]);
    bool contains(char check[],int startPos);
    SString(const SString &copy);
    SString wordAt(int counter);
    int getNumWords();
    bool operator <(const SString &var) const;
    bool operator >(const SString &var) const;
    bool operator ==(const SString& var) const;
    bool operator !=(const SString& var) const;

};


#endif //S20_PA01_SENTIMENTANALYSIS_SSTRING_H
