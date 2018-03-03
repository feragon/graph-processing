#pragma once

#include <string>

/**
 * @brief Compare deux caractères sans tenir compte des majuscules
 * @param a Caractère 1
 * @param b Caractère 2
 * @return Vrai s'ils sont égaux
 */
bool compareCharInsensitive(unsigned char a, unsigned char b);

/**
 * @brief Compare deux chaînes de caractère sans tenir compte des majuscules
 * @param s1 Chaîne 1
 * @param s2 Chaîne 2
 * @return Vrai s'ils sont égaux
 */
bool compareCaseInsensitive(const std::string& s1, const std::string& s2);