#ifndef PARALLEL_TRACKS_H
#define PARALLEL_TRACKS_H

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <iomanip>
#include <stdexcept>
#include <limits>
#include <cctype>		// Contains isdigit, isalpha, isupper, etc.

const unsigned int SIZE = 9; // lines in the data

//-------------------------------------------------------
// Name: is_valid_number
// PreCondition:  a string that needs to be checked as a valid competition 
// number (non-negative int)
// PostCondition: returns TRUE if string is only made up of numeric chars 0-9
//---------------------------------------------------------
bool is_valid_number(const std::string& str);

//-------------------------------------------------------
// Name: is_valid_time
// PreCondition:  a string that needs to be checked as a valid time 
// (non-negative float)
// PostCondition: returns TRUE if string is only made up of numeric chars 
// 0-9 or '.'
//---------------------------------------------------------
bool is_valid_time(const std::string& str);

//-------------------------------------------------------
// Name: is_valid_country
// PreCondition:  a string that needs to be checked as a valid country (std::string)
// PostCondition: returns TRUE if string is made of exactly 3 capital chars A-Z
//---------------------------------------------------------
bool is_valid_country(const std::string& str);

//-------------------------------------------------------
// Name: is_valid_name
// PreCondition:  a string that needs to be checked as a valid name (std::string)
// PostCondition: returns TRUE if string is made of letters A-Z, a-z, and ' '
//---------------------------------------------------------
bool is_valid_name(const std::string& str);

//-------------------------------------------------------
// Name: get_runner_data
// PreCondition:  the prepped parallel arrays , and a legit filename is pass
// PostCondition: all arrays contain data from the csv file given
//---------------------------------------------------------
void get_runner_data( const std::string& file, float *timeArray, std::string* countryArray, 
		unsigned int* numberArray, std::string *lastnameArray);

//-------------------------------------------------------
// Name: prep_float_array
// PreCondition:  a float arrays is pass in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_float_array(float *ary);

//-------------------------------------------------------
// Name: prep_float_array
// PreCondition:  a float arrays is pass in
// PostCondition: data in the array is 'zeroed' out
//---------------------------------------------------------
void prep_unsigned_int_array(unsigned int *ary);

//-------------------------------------------------------
// Name: prep_string_array
// PreCondition:  a string arrays is pass in
// PostCondition: data in the array is "N/A" out to determine if
// a value has changed
//---------------------------------------------------------
void prep_string_array(std::string *ary);

//-------------------------------------------------------
// Name: get_ranking
// PreCondition:  just the time array is passed in, and has valid data
// PostCondition: after a very ineffiect nested loop to determine the placements 
// and places the ranks in a new array. That new array is returned
//---------------------------------------------------------
void get_ranking(const float *timeArray, unsigned int *rankArray);

//-------------------------------------------------------
// Name: print_results
// PreCondition:  almost all parallel arrays are passed in and have valid data
// PostCondition: after a very ineffiect nested loop to determine the ranks
// it then displays then along with a delta in time from the start
//---------------------------------------------------------
void print_results(const float *timeArray, const std::string* countryArray,
		const std::string *lastnameArray, const unsigned int* rankArray);

#endif