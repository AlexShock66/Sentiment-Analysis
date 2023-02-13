//
// Created by Alex Shockley on 9/2/2020.
//

#include <cstring>
#include <iostream>
#include "SString.h"

SString::SString() { // default constructor that assigns base values
    size = 0;
    maxSize = 10;
    data = new char[0];
    data[0] = '\0';
}

SString::SString(char newWord[]) { // overloaded constructor that copies the contents of the passed in char[] into it's data and sets the size to the size of the passed in data

    this->size = strlen(newWord);
    this->data = new char[size + 1];
    for(int i = 0; i < size; i ++) {
        this->data[i] = newWord[i];
    }
    if(maxSize < size){
        this->maxSize = size;
    }
    data[size] = '\0'; // ensure that the null character is present in each Sstring because we are searching for it later on

}



SString::~SString() { // destructor
    delete[] this->data;

}

char *SString::getData() const { // getter
    return this->data;
}

void SString::setString(char *string) { // set string method that deletes the current data and reassigns it based on what is passed in by the user, Updates the size aswell
    if(this->data != nullptr) {
        delete[] this->data;
    }
    data = nullptr;

    this->size = strlen(string);
    this->data = new char[this->size + 1];
    for(int i = 0; i < this->size; i ++) {
        this->data[i] = string[i];
    }
    if(maxSize < size){
        this->maxSize = size;
    }
    data[size] = '\0';

}

int SString::getSize() const {
    return size;
}


SString &SString::operator=(const SString & copy) { // overloaded = operator that assigns the new value a deep copy
    if (this != &copy) {
            delete[] this->data;

        this->size = copy.size;
        this->data = new char[copy.size +1];

        for (int i = 0; i < size + 1; i++) {
            data[i] = copy.data[i];
        }
        data[size] = '\0';
    }

    return *this;
}



bool SString::contains(char *check) { // function that checks if a string is contained within another string, returns true if it is, returns false if it is not

    return strstr(this->data, check);
}

bool SString::contains(char *check, int startPos) { // more indepth function to check if a string is contained within another string, but it also accepts a starting index so it doesnt have to search the entire string
    int checkSize = 0;
    char test = ' ';
    bool value = false;
    while(test != '\0') {
        test = check[checkSize];
        checkSize++;
    }
    checkSize--;
    for(int i = startPos; i < this->size; i ++) { // iterate through the size of the this->data
        for(int j = 0; j < checkSize; j++) { // iterate through the size of the string passed in
            if(check[j] != this->data[i]) { // check character for character to see if the set of characters is the same, if it gets through the entire word that is passed in, then it returns true
                value = false;
                break;
            } else {
                value = true;
                i++;
            }
        }
        if(value == true) {
            break;
        }
    }
    return value;
}





SString::SString(const SString &copy) { // copy constructor to create a deep copy for use in vectors

    this->maxSize = copy.maxSize;
    this->size = copy.size;
    this->data = new char[size + 1];
    for(int i = 0; i < size; i ++) {
        data[i] = copy.data[i];
    }
    data[size] = '\0';

}

SString SString::wordAt(int counter) { // takes the string and returns a new SString at the index that is passed in
    int z = 0;
    SString realWord = SString();
    if(counter > this->size) return realWord; // if the index is out of bounds, return a blank SString
    for(int i = 0; i <= counter; i++) { // for loop running index amount of times
        int j = 0;
        if(z > strlen(this->data) ) break;
        char word[20];
        char currChar = 'b';
        while (currChar != ' ') { // as long as the character doesnt = ' ', continue "building" the word

            if(currChar == '\0') {
                break;
            }

            currChar = this->data[z]; // assign the character to the word
            word[j] = this->data[z];

            j++;
            z++;
        }

        realWord.setString(word); // set the SString to whatever word is present at index counter
        memset(word,0,strlen(word)); // clear the contents of word variable

    }
    return realWord; // return the Sstring that was created using the word at index counter
}

int SString::getNumWords() { // function that counts the number of spaces in an SString and returns that value
    char currChar = ' ';
    int i = 0;
    int wordCount = 0;
    for(int j; j < strlen(this->data); j++) {
        currChar = this->data[i];
        i++;
        if(currChar == ' '){
            wordCount++;
        }
    }
    return wordCount;
}
bool SString::operator <(const SString &var) const { // overloaded < operator
    if(strcmp(data,var.data) < 0) {
        return true;
    } else {
        return false;
    }
}

bool SString::operator>(const SString &var) const{ // overloaded > operator
    if(strcmp(data,var.data) > 0) {
        return true;
    } else {
        return false;
    }
}

bool SString::operator==(const SString &var) const { //overloaded == operator
    if(strcmp(this->data,var.data) == 0) {
        return true;
    } else {
        return false;
    }
}
bool SString::operator !=(const SString &var) const{ //overloaded != operator
    return strcmp(data, var.data) == 0;
}
