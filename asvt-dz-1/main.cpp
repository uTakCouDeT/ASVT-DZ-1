#include <iostream>
#include <vector>
#include <string>
#include <set>
#include <map>
#include <stdlib.h>
#include <string>
#include <cmath>

using namespace std;

void vector_print(vector<vector<int>> vec) {
    cout << "   ";
    for (int i = 0; i < vec[0].size(); i++) {
        if (i < 10) {
            cout << "0" << i << " ";
        } else {
            cout << i << " ";
        }
    }
    cout << endl;
    for (int i = 0; i < vec.size(); i++) {
        if (i < 10) {
            cout << "0" << i << " ";
        } else {
            cout << i << " ";
        }
        for (int j : vec[i]) {
            if(j){
                cout << " x ";
            } else {
                cout << " . ";
            }
        }
        cout << endl;
    }
}

vector<int> dec_to_bin(int n, int len) {
    vector<int> number;
    vector<int> otvet;
    int count = 0;
    number.resize(len);
    while (count != len) {
        number[count] = n % 2;
        n = n / 2;
        count += 1;
    }
    otvet.resize(len);
    for (int i = len - 1; i >= 0; i--) {
        otvet[i] = number[len - 1 - i];
    }
    return otvet;
}

vector<vector<int>> input(vector<int> func) {
    vector<vector<int>> miniterms;
    vector<int> wrong_term;
    int count = 0;
    int len_of_miniterm = log(func.size()) / log(2);
    miniterms.resize(func.size());
    for (int i = 0; i < len_of_miniterm; i++) {
        wrong_term.push_back(8);
    }
    for (int i = 0; i < func.size(); i++) {
        if (func[i] == 1) {
            miniterms[i] = dec_to_bin(count, len_of_miniterm);
        } else {
            miniterms[i] = wrong_term;
        }
        count += 1;
    }
    return miniterms;
}

int weight(vector<int> implicant) {
    int weightt = 0;
    for (int i = 0; i < implicant.size(); i++) {
        if (implicant[i] == 1) {
            weightt++;
        } else {
            continue;
        }
    }
    return weightt;
}

vector<vector<int>> MakeMiniTerms(vector<int> input_func) {
    vector<vector<int>> Mini;
    vector<vector<int>> Minis;
    vector<int> wrong_term;
    Mini = input(input_func);
    int len_of_miniterm = log(input_func.size()) / log(2);
    for (int i = 0; i < len_of_miniterm; i++) {
        wrong_term.push_back(8);
    }
    for (int i = 0; i < Mini.size(); i++) {
        if (Mini[i] != wrong_term) {
            Minis.push_back(Mini[i]);
        }
    }
    return Minis;
}

int compare(vector<int> A, vector<int> B) {
    int count_of_difference = 0;
    int place_of_difference = 0;
    for (int i = 0; i < A.size(); i++) {
        if (A[i] == B[i]) {
            continue;
        } else {
            count_of_difference += 1;
            place_of_difference = i;
        }
    }
    if (count_of_difference == 1) {
        return place_of_difference;
    } else {
        return -1;
    }
}

vector<vector<vector<int>>> find_first_impl(vector<vector<vector<int>>> group) {
    vector<vector<vector<vector<int>>>> first_implicants(10);
    set<vector<int>> used_implicants;
    int count_of_new_implicants;
    int difference;
    int already_pushed;
    for (int i = 0; i < 10; i++) {
        first_implicants[i].resize(6);
    }
    first_implicants[0] = group;
    for (int level = 0; level < 10; level++) {
        count_of_new_implicants = 0;
        for (int i = 0; i < first_implicants[level].size() - 1; i++) {
            if ((first_implicants[level][i].size() != 0) && (first_implicants[level][i + 1].size() != 0)) {
                for (int count = 0; count < first_implicants[level][i + 1].size(); count++) {
                    for (int j = 0; j < first_implicants[level][i].size(); j++) {
                        difference = compare(first_implicants[level][i][j], first_implicants[level][i + 1][count]);
                        if (difference != -1) {
                            already_pushed = 0;
                            vector<int> placed_vec = first_implicants[level][i][j];
                            placed_vec[difference] = 9;
                            for (auto it: first_implicants[level + 1][i]) {
                                if (it == placed_vec) {
                                    already_pushed = 1;
                                }
                            }
                            used_implicants.insert(first_implicants[level][i][j]);
                            used_implicants.insert(first_implicants[level][i + 1][count]);
                            if (already_pushed == 0) {
                                first_implicants[level + 1][i].push_back(placed_vec);
                                count_of_new_implicants++;
                            }
                        }
                    }
                }
            }
        }
        if (count_of_new_implicants == 0) {
            break;
        }
    }
    vector<vector<int>> result_first_implicants;
    vector<vector<int>> result_used_implicants;
    for (int i = 0; i < first_implicants.size(); i++) {
        for (int j = 0; j < first_implicants[i].size(); j++) {
            if (first_implicants[i][j].size() == 0) {
                continue;
            }
            for (int k = 0; k < first_implicants[i][j].size(); k++) {
                if (used_implicants.find(first_implicants[i][j][k]) == used_implicants.end())
                    result_first_implicants.push_back(first_implicants[i][j][k]);
            }
        }
    }
    for (auto it: first_implicants[0]) {
        for (auto vec: it) {
            result_used_implicants.push_back(vec);
        }
    }
    return {result_first_implicants, result_used_implicants};
}

int child_and_parent(vector<int> child, vector<int> parent) {
    for (int i = 0; i < child.size(); i++) {
        if (child[i] != parent[i]) {
            if (child[i] != 9) return 0;
        }
    }
    return 1;
}

vector<int> min_coverage(vector<vector<int>> success_sets, map<int, vector<int>> number_implicant) {
    int min_count_numbers = 10000000;
    vector<int> min_set;
    for (auto it: success_sets) {
        int count_numbers = 0;
        for (auto i: it) {
            for (auto variable: number_implicant[i]) {
                if (variable == 9) {
                    continue;
                }
                count_numbers++;
            }
        }
        if (count_numbers < min_count_numbers) {
            min_count_numbers = count_numbers;
            min_set = it;
        }
    }
    return min_set;
}

vector<int> find_coverage(vector<int> non_essential, vector<int> non_made, vector<vector<int>> table_of_points,
                          map<int, vector<int>> number_implicant) {
    vector<vector<int>> sets;
    for (int i = 0; i < pow(2, non_essential.size()); i++) {
        sets.push_back(dec_to_bin(i, non_essential.size()));
    }
    vector<vector<int>> success_sets;
    for (auto it: sets) {
        set<int> local_non_made;
        set<int> local_made;
        vector<int> local_set;
        for (auto column: non_made) {
            local_non_made.insert(column);
        }
        for (int i = 0; i < it.size(); i++) {
            for (auto j: non_made) {
                if (it[i] == 1) {
                    if (table_of_points[non_essential[i]][j] == 1) {
                        local_set.push_back(non_essential[i]);
                        local_made.insert(j);
                        if (local_non_made == local_made) {
                            success_sets.push_back(local_set);
                            break;
                        }
                    }
                }
            }
        }
    }
    return min_coverage(success_sets, number_implicant);
}

vector<vector<int>> make_table_of_points(vector<vector<int>> first_implicants, vector<vector<int>> usual_implicants,
                                         map<int, vector<int>> number_implicant) {
    vector<vector<int>> table_of_points;
    vector<int> nul_vec(usual_implicants.size());
    for (int i = 0; i < nul_vec.size(); i++) {
        nul_vec[i] = 0;
    }
    for (int i = 0; i < first_implicants.size(); i++) {
        table_of_points.push_back(nul_vec);
    }
    for (int first_implicant = 0; first_implicant < first_implicants.size(); first_implicant++) {
        for (int usual_implicant = 0; usual_implicant < usual_implicants.size(); usual_implicant++) {
            table_of_points[first_implicant][usual_implicant] = child_and_parent(number_implicant[first_implicant],
                                                                                 number_implicant[usual_implicant +
                                                                                                  first_implicants.size()]);
        }
    }
    return table_of_points;
}


set<int> find_essential_variables(vector<vector<int>> table_of_points, vector<vector<int>> first_implicants,
                                  vector<vector<int>> usual_implicants) {
    set<int> essential_variables;
    for (int usual_implicant = 0; usual_implicant < usual_implicants.size(); usual_implicant++) {
        int count_of_points = 0;
        vector<int> essential;
        for (int first_implicant = 0; first_implicant < first_implicants.size(); first_implicant++) {
            if (table_of_points[first_implicant][usual_implicant] == 1) {
                essential.push_back(first_implicant);
                count_of_points += 1;
            }
        }
        if (count_of_points == 1) {
            for (auto it: essential) {
                essential_variables.insert(it);
            }
        }
    }
    return essential_variables;
}

set<int> find_columns_from_essential_variables(set<int> essential_variables, vector<vector<int>> usual_implicants,
                                               vector<vector<int>> first_implicants,
                                               vector<vector<int>> table_of_points) {
    set<int> columns_from_essential_variables;
    for (auto it: essential_variables) {
        for (int column = 0; column < usual_implicants.size(); column++) {
            if (table_of_points[it][column] == 1)
                columns_from_essential_variables.insert(column + first_implicants.size());
        }
    }
    return columns_from_essential_variables;
}

void print_implicant(vector<int> implicant) {
    for (int i = 0; i < implicant.size(); i++) {
        if (implicant[i] == 1) {
            cout << "X" << implicant.size() - 1 - i;
        }
        if (implicant[i] == 0) {
            cout << "!X" << implicant.size() - 1 - i;
        }
        if (implicant[i] == 9) {
            continue;
        }
    }
}

void
print_min_dnf(set<int> essential_variables, vector<vector<int>> usual_implicants, vector<vector<int>> first_implicants,
              vector<vector<int>> table_of_points, map<int, vector<int>> number_implicant,
              set<int> columns_from_essential_variables) {
    cout << "\nMinimal DNF: ";
    if (columns_from_essential_variables.size() == usual_implicants.size()) {
        int count_of_borders = essential_variables.size() - 1;
        for (auto i: essential_variables) {
            print_implicant(number_implicant[i]);
            if (count_of_borders != 0) {
                cout << " V ";
                count_of_borders--;
            }
        }
    } else {
        vector<int> non_essential_variables;
        for (int i = 0; i < first_implicants.size(); i++) {
            if (essential_variables.find(i) == essential_variables.end()) {
                non_essential_variables.push_back(i);
            }
        }
        vector<int> non_made_columns;
        for (int i = first_implicants.size(); i < usual_implicants.size() + first_implicants.size(); i++) {
            if (columns_from_essential_variables.find(i) == columns_from_essential_variables.end()) {
                non_made_columns.push_back(i - first_implicants.size());
            }
        }
        for (auto it: find_coverage(non_essential_variables, non_made_columns, table_of_points, number_implicant)) {
            essential_variables.insert(it);
        }
        int count_of_borders = essential_variables.size() - 1;
        for (auto i: essential_variables) {
            print_implicant(number_implicant[i]);
            if (count_of_borders != 0) {
                cout << " V ";
                count_of_borders--;
            }
        }
    }
}

void table_implicants(vector<vector<int>> implicants) {
    for (int i = 0; i < implicants.size(); i++) {
        cout << i << " : ";
        print_implicant(implicants[i]);
        cout << "(";
        for (int j = 0; j < implicants[i].size(); j++) {
            if (implicants[i][j] == 9) {
                cout << "~";
            } else {
                cout << implicants[i][j];
            }
        }
        cout << ")";
        cout << endl;
    }
}

int main() {
    vector<int> inp;
    vector<vector<int>> MiniTerms;
    bool input_func = false;
    int phrase_for_farewell;
    while (!input_func) {
        inp = {};
        string input_f;
        //cout << "Enter function vector:" << endl;
        //cin >> input_f;
        input_f = "1000101110001001000110100000101001000101100000011111111011111111";
        input_func = true;
        for (int i = 0; i < input_f.size(); i++) {
            int variable = input_f[i] - '0';
            if (variable != 0 && variable != 1) {
                cout << "Length error" << endl;
                input_func = false;
            }
            inp.push_back(input_f[i] - '0');
        }
        int check_size = inp.size();
        int check_degree = log(check_size) / log(2);
        if (pow(2, check_degree) != check_size) {
            cout << "Length error" << endl;
            input_func = false;
        }
    }
    int check_for_constant = 0;
    for (int i = 0; i < inp.size(); i++) {
        if (inp[i] == 1) {
            check_for_constant++;
        }
    }
    if (check_for_constant == 0) {
        cout << "No minimal DNF";
        cin >> check_for_constant;
        return 0;
    }
    if (check_for_constant == inp.size()) {
        cout << "Minimal DNF: 1";
        cin >> check_for_constant;
        return 0;
    }
    cout << "Function vector: ";
    for (auto it: inp) {
        cout << it;
    }
    cout << endl;
    MiniTerms = MakeMiniTerms(inp);
    vector<vector<vector<int>>> groups(7);
    for (auto & MiniTerm : MiniTerms) {
        groups[weight(MiniTerm)].push_back(MiniTerm);
    }
    vector<vector<vector<int>>> first_implicants_and_usual_implicants = find_first_impl(groups);
    vector<vector<int>> first_implicants = first_implicants_and_usual_implicants[0];
    vector<vector<int>> usual_implicants = first_implicants_and_usual_implicants[1];
    cout << endl << "Primal implicants: " << endl;
    table_implicants(first_implicants);
    cout << endl << "Miniterms: " << endl;
    table_implicants(usual_implicants);
    cout << endl << endl;
    map<int, vector<int>> number_implicant;
    for (int i = 0; i < first_implicants.size(); i++) {
        number_implicant[i] = first_implicants[i];
    }
    for (int i = 0; i < usual_implicants.size(); i++) {
        number_implicant[i + first_implicants.size()] = usual_implicants[i];
    }
    vector<vector<int>> table_of_points = make_table_of_points(first_implicants, usual_implicants, number_implicant);
    vector_print(table_of_points);
    set<int> essential_variables = find_essential_variables(table_of_points, first_implicants, usual_implicants);
    set<int> columns_from_essential_variables = find_columns_from_essential_variables(essential_variables,
                                                                                      usual_implicants,
                                                                                      first_implicants,
                                                                                      table_of_points);
    print_min_dnf(essential_variables, usual_implicants, first_implicants, table_of_points, number_implicant,
                  columns_from_essential_variables);
    cin >> phrase_for_farewell;
    cout << endl << phrase_for_farewell;
    return 0;
}

/*

   00 01 02 03 04 05 06 07 08 09 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25 26 27 28 29 30 31
00  .  .  x  .  .  .  .  x  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .
04  .  .  .  .  .  .  .  .  .  .  x  .  .  .  .  .  .  .  .  .  .  x  .  .  .  .  .  .  .  .  .  .
06  x  x  x  .  x  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .
07  .  x  .  x  .  x  .  .  .  .  .  x  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .
09  .  .  .  .  .  .  x  .  .  .  .  .  .  x  x  .  .  .  .  .  .  .  x  .  .  .  .  .  .  .  .  .
10  .  .  .  .  .  .  .  .  .  x  .  .  .  .  .  .  .  .  x  .  x  .  .  .  .  .  .  x  .  .  .  .
13  .  .  .  .  .  x  .  .  .  .  .  x  x  .  .  .  x  .  .  x  .  .  .  x  .  .  x  .  .  .  x  .
14  .  .  .  .  .  .  .  .  x  .  .  .  .  .  .  x  x  x  .  .  .  .  .  x  .  x  x  .  .  .  x  .
15  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  .  x  .  .  .  .  .  .  x  x  x  .  x  x  x  x

!X4X3!X2!X1!X0 V X4!X3!X2X1X0 V !X5!X4!X1!X0 V !X5!X3X2!X0 V X5!X3!X1X0 V !X4X2X1X0 V X4X2!X0 V X5X4!X0 V X5X4X3

*/