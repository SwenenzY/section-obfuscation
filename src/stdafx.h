#pragma once
#include <Windows.h>
#include <iostream>
#include <fstream>
#include <filesystem>
#include <stdio.h>
#include <random>
#include <string>
#include <thread>

using namespace std;

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
