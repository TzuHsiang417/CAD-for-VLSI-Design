#ifndef _LOGICOPT_H
#define _LOGICOPT_H

#include <string>
#include <string.h>
#include <vector>
#define MERGED 1
#define NO_MERGED 0

using namespace std;

inline vector<string> minterm; 
inline vector<string> input;
inline string output;
inline vector<string> prime_implicant;
inline vector<string> on_set;
inline vector<vector<bool> > table;
inline vector<string> minimum_cover;

template<typename T>
void FreeVector(vector<T> &vt)
{
    vector<T> vt_tmp;
    vt_tmp.swap(vt);
}

//readfile
void get_file(char *);
void create_file(char *);

//Quine McCluskey
void Quine_McCluskey_ALGO();
bool compare_num_of_1(string, string);
void sort_minterm();
bool can_merge(string, string);
string merge(string, string);

//Column Covering
void Column_Covering_ALGO();
bool can_marked_table(string, string);
void create_table();
void set_covered(int x, int *);
void column_has_single_1(int *);
void minimum_set_of_row(int *);

#endif