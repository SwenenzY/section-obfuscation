#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdio.h>
#include <random>
#include <string>

using namespace std;

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
    if (from.empty())
        return;
    size_t start_pos = 0;
    while ((start_pos = str.find(from, start_pos)) != std::string::npos) {
        str.replace(start_pos, from.length(), to);
        start_pos += to.length(); // In case 'to' contains 'from', like replacing 'x' with 'yx'
    }
}

std::string random_string_only_char(std::string::size_type length)
{
    string possible_characters = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    random_device rd;
    mt19937 engine(rd());
    uniform_int_distribution<> dist(0, possible_characters.size() - 1);
    string ret = "";
    for (int i = 0; i < length; i++) {
        int random_index = dist(engine); //get index between 0 and possible_characters.size()-1
        ret += possible_characters[random_index];
    }
    return ret;
}


class PeClass {
public:
    const char* OrginalPE = "NULL";
    bool isMatched = false;
    bool operator==(PeClass p) {
        if (p.OrginalPE == this->OrginalPE) return true;
        else return false;
    }
};