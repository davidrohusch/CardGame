//
// Created by david on 20.06.2021.
//
#include"curses.h"
#include <array>
#include <vector>
#include <string>
#include "CCard.h"

#pragma once

using namespace std;

void print_menu(WINDOW *w, int highlight, std::vector<std::string> &choices);

void printBox(WINDOW *w, const string &text, int yoffset = 0, int xoffset = 0);

void drawCardMenu (WINDOW *w, int highlight, vector<shared_ptr<CCard>> &src , int gold, int mana);

void drawCardDesc (WINDOW *w, const string &desc, const SEffect &eff, const string &price);