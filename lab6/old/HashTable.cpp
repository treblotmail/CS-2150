#include "HashTable.h"
#include <iostream>
#include <bits/stdc++.h>
#include <string>
//Liam Tolbert, lct4am, 3/30/2021,HashTable.cpp
using namespace std;

HashTable::HashTable(int b){
  buckets = b;
  table = new list<string>[buckets];
}

void HashTable::insert(string word){
  table[hashFunction(word)].push_back(word);
}

bool HashTable::contains(string word){
  list<string>::iterator iter;
  int index = hashFunction(word);
  for(iter = table[index].begin(); iter != table[index].end(); iter++){
    if(*iter == word)
      return true;
  }
  return false;
}

int HashTable::hashFunction(string word){
  int val = 0;
  for(int i = 0; i < word.length(); i++){
    val = val * 37 + word[i];
  }
  return val % buckets < 0 ? -1 * (val % buckets) : val % buckets;
}
