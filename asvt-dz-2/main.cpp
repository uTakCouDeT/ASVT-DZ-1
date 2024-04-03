#include <iostream>
#include <utility>
#include <vector>
#include <cmath>
#include <set>

void print_implicant(std::vector<int> implicant) {
    for (int i = 0; i < implicant.size(); i++) {
        if (implicant[i] == 1) std::cout << "X" << implicant.size() - 1 - i;
        if (implicant[i] == 0)std::cout << "!X" << implicant.size() - 1 - i;
        if (implicant[i] == 9)continue;
    }
}

void print_Koef(std::vector<int> implicant) {
    std::reverse(implicant.begin(), implicant.end());
    std::cout << "K";
    for (int i = 0; i < implicant.size(); i++) {
        if (implicant[i] == 9) continue;
        std::cout << i + 1;
    }
    std::cout << ",";
    for (int i: implicant) {
        if (i == 9) continue;
        std::cout << i;
    }
}

std::set<std::vector<int>> set_cross(const std::set<std::vector<int>> &s1, const std::set<std::vector<int>> &s2) {
    std::set<std::vector<int>> rezult;
    std::set<std::vector<int>> base;
    std::set<std::vector<int>> finde;
    if (s1.size() > s2.size()) {
        base = s1;
        finde = s2;
    } else {
        base = s2;
        finde = s1;
    }

    for (const auto &it: finde) {
        if (base.find(it) != base.end()) rezult.insert(it);
    }
    return rezult;
}

bool bolshe(std::vector<int> B_positions, std::vector<int> A_positions, std::vector<int> B_varibles,
            std::vector<int> A_varibles) {
    if (B_positions.size() <= A_positions.size()) return false;
    int state = 0;

    std::vector<int> find;
    std::vector<int> base;
    base.reserve(B_positions.size());
    for (int i = 0; i < B_positions.size(); i++) {
        base.push_back(B_positions[i] * 10 + B_varibles[i]);
    }

    find.reserve(A_positions.size());
    for (int i = 0; i < A_positions.size(); i++) {
        find.push_back(A_positions[i] * 10 + A_varibles[i]);
    }
    for (int i: base) {
        if (state == find.size()) return true;
        if (i == find[state]) {
            state++;
        }
    }

    if (state == find.size()) return true;
    else return false;
}

std::vector<int> dec_to_bin(int n, int len) {
    std::vector<int> number;
    number.resize(len);
    int count = 0;
    while (count != len) {
        number[count] = n % 2;
        n = n / 2;
        count += 1;
    }
    std::vector<int> otvet;
    otvet.resize(len);
    for (int i = len - 1; i >= 0; i--) {
        otvet[i] = number[len - 1 - i];
    }
    return otvet;
}

class Koef {
    std::set<std::vector<int>> realized_set;
    std::vector<int> high_index;
    std::vector<int> low_index;
    int value = 9;
    std::vector<int> id_vec;
    int id{};
public:
    Koef() {
        std::set<std::vector<int>> null_set;
        realized_set = null_set;
        high_index = {};
        low_index = {};
        value = 9;
        id_vec = {};
        id = 0;
    }

    Koef(std::vector<int> variables, const std::vector<int> &positions) {
        for (auto it: variables) id_vec.push_back(9);
        low_index = positions;
        for (auto it: positions) {
            id_vec[it] = variables[it];
            high_index.push_back(variables[it]);
        }
        int count = 1;
        for (int i: id_vec) {
            id += i * count;
            count *= 10;
        }

    }

    int get_id() {
        return id;
    }

    std::vector<int> get_vec_id() {
        return id_vec;
    }

    int get_number_nine() {
        int nine_positions = 0;
        for (int i: id_vec) {
            if (i == 9) {
                nine_positions++;
            }
        }
        return nine_positions;
    }

    void print_K(int flag = 0) {
        if (flag == 1) {
            print_implicant(id_vec);
        } else if (flag == 2) {
            print_Koef(id_vec);
        } else {
            for (auto i: id_vec)
                std::cout << i;
            std::cout << std::endl;
        }
    }

    void relization_set() {
        int nine_positions = 0;
        for (int i: id_vec) {
            if (i == 9) {
                nine_positions++;
            }
        }
        std::vector<std::vector<int>> details_for_new_sets;
        int len = pow(2, nine_positions);
        std::vector<std::vector<int>> local_sets;

        for (int i = 0; i < len; i++) {
            std::vector<int> nul_vec;
            nul_vec.reserve(id_vec.size());
            for (int l = 0; l < id_vec.size(); l++) nul_vec.push_back(0);
            local_sets.push_back(nul_vec);
            std::vector<int> v = dec_to_bin(i, nine_positions);
            details_for_new_sets.push_back(v);
        }

        int number_of_detail = 0;
        for (int i = 0; i < id_vec.size(); i++) {
            if (id_vec[i] != 9) {
                for (int j = 0; j < len; j++) local_sets[j][i] = id_vec[i];
            } else {

                for (int number_of_pack = 0; number_of_pack < details_for_new_sets.size(); number_of_pack++) {
                    local_sets[number_of_pack][i] = details_for_new_sets[number_of_pack][number_of_detail];

                }
                number_of_detail++;
            }

        }
        for (const auto &it: local_sets) realized_set.insert(it);
    }

    std::set<std::vector<int>> get_set() {
        return realized_set;
    }

    void print_s() {
        for (auto i: id_vec) std::cout << i;
        std::cout << std::endl << std::endl;
        for (const auto &vec: realized_set) {
            for (auto el: vec) {
                std::cout << el;
            }
            std::cout << std::endl;
        }
        std::cout << std::endl;
    }

    void set_value(int value) {
        this->value = value;
    }

    int get_value() {
        return value;
    }

    std::vector<std::vector<int>> get_indexes() {
        return {high_index, low_index};
    }

    void print() {
        std::cout << "K";
        for (auto i: low_index) std::cout << i + 1;
        std::cout << ",";
        for (auto i: high_index) std::cout << i;
    }

    bool operator==(Koef &K) {
        std::vector<std::vector<int>> indexes;
        indexes.push_back(high_index);
        indexes.push_back(low_index);
        int count = 0;
        for (int i = 0; i < 2; i++) {
            if (indexes[i] != K.get_indexes()[i]) count++;
        }
        if (count != 0) return false;
        else {
            return true;
        }
    }

    bool bolshe_K(Koef K) {
        std::vector<int> other_high_index = K.get_indexes()[0];
        std::vector<int> other_low_index = K.get_indexes()[1];
        if (bolshe(low_index, other_low_index, high_index, other_high_index)) return true;
        else return false;
    }


    void operator=(Koef K1) {
        std::vector<std::vector<int>> indexs;
        indexs = K1.get_indexes();
        high_index = indexs[0];
        low_index = indexs[1];
        id = K1.get_id();
        id_vec = K1.get_vec_id();
        realized_set = K1.get_set();
    }

    friend bool operator<(const Koef &K1, const Koef &K2);

};

bool operator<(const Koef &K1, const Koef &K2) {
    return K1.id < K2.id;
}


class equation {
    std::vector<Koef> uravnenie;
    int value;
public:
    equation() {
        value = 1;
        uravnenie = {};
    }

    equation(int n, int len, int value) {
        this->value = value;
        std::vector<int> variables;
        std::vector<int> all_pos_vec;
        variables = dec_to_bin(n, len);
        for (int j = 1; j < pow(2, len); j++) {
            all_pos_vec = dec_to_bin(j, len);
            std::vector<int> position_vec;
            for (int pos = 0; pos < all_pos_vec.size(); pos++) {
                if (all_pos_vec[pos] == 1) position_vec.push_back(pos);
            }
            Koef K(variables, position_vec);
            if (value == 0) K.set_value(0);
            uravnenie.push_back(K);
        }

    }

    void set_koefs(std::vector<Koef> uravnenie) {
        this->uravnenie = std::move(uravnenie);
    }

    std::vector<Koef> get_koefs() {
        return uravnenie;
    }

    void print_eq() {
        for (auto koef: uravnenie) {
            koef.print();
            if (&koef != &uravnenie.back()) {
                std::cout << " v ";
            }
        }
        std::cout << " = " << value << std::endl;
    }


};


class all_equations {
    std::vector<equation> the_system_of_equations;
    std::vector<int> values;
    std::set<Koef> nu_koefs;
public:
    explicit all_equations(const std::vector<int> &input_func) {
        nu_koefs = {};
        values = input_func;
        int len_koef = log(input_func.size()) / log(2);
        for (int i = 0; i < input_func.size(); i++) {
            equation eq(i, len_koef, values[i]);
            if (values[i] == 0) {
                for (const auto &it: eq.get_koefs()) nu_koefs.insert(it);
            }

            the_system_of_equations.push_back(eq);

        }
    }

    void print_all_eq() {
        for (auto it: the_system_of_equations) {
            it.print_eq();
        }
    }

    void print_null_koefs() {
        for (auto it: nu_koefs) {
            it.print();
            std::cout << "  ";
        }
    }


    void delete_null_koefs() {
        std::vector<equation> new_system_of_equations;
        for (auto eq: the_system_of_equations) {
            std::vector<Koef> with_null_koefs = eq.get_koefs();
            std::vector<Koef> not_null_koefs;
            for (const auto &koef: with_null_koefs) {
                int flag = 0;
                if (nu_koefs.find(koef) != nu_koefs.end()) {
                    flag++;
                }


                if (flag == 0) {
                    not_null_koefs.push_back(koef);
                }
            }
            equation eq1;
            eq1.set_koefs(not_null_koefs);

            if (!not_null_koefs.empty()) new_system_of_equations.push_back(eq1);
        }

        the_system_of_equations = new_system_of_equations;


    }


    void delete_big_koefs() {
        std::vector<equation> new_system_of_equations;
        for (auto eq: the_system_of_equations) {
            std::vector<Koef> not_extra_koefs;
            for (auto koef: eq.get_koefs()) {
                int flag = 0;
                for (const auto &koef_next: eq.get_koefs()) {
                    if (koef.bolshe_K(koef_next)) {
                        flag = 1;
                    }
                }
                if (flag == 1) continue;
                else {
                    not_extra_koefs.push_back(koef);
                }
            }
            equation eq1;
            eq1.set_koefs(not_extra_koefs);

            if (!not_extra_koefs.empty()) new_system_of_equations.push_back(eq1);
        }
        the_system_of_equations = new_system_of_equations;


    }

    std::set<Koef> MinDnf() {
        std::set<Koef> min_dnf;
        for (auto eq: the_system_of_equations) {
            for (const auto &koef: eq.get_koefs()) {
                min_dnf.insert(koef);
            }
        }

        return min_dnf;
    }
};


void vector_print(std::vector<int> A) {
    for (auto i: A) std::cout << i << " ";
}


std::vector<Koef> Koef_sort(std::vector<Koef> koefs) {
    std::vector<Koef> sorted_koef = std::move(koefs);
    for (int i = 0; i < sorted_koef.size(); i++) {
        for (int j = 0; j < sorted_koef.size() - 1; j++) {
            if (sorted_koef[j].get_set().size() > sorted_koef[j + 1].get_set().size()) {
                Koef temp;
                temp = sorted_koef[j];
                sorted_koef[j] = sorted_koef[j + 1];
                sorted_koef[j + 1] = temp;
            }
        }
    }
    return sorted_koef;
}


std::vector<Koef> mdnf(std::vector<Koef> extra_koef) {
    std::vector<Koef> not_extra_koef;
    for (auto &i: extra_koef) i.relization_set();
    extra_koef = Koef_sort(extra_koef);
    std::set<int> index;
    for (int i = 0; i < extra_koef.size(); i++) {


        std::set<std::vector<int>> set_for_check = extra_koef[i].get_set();
        for (int j = 0; j < extra_koef.size(); j++) {
            if (index.find(j) != index.end()) {

                continue;
            }
            if (i == j) continue;

            std::set<std::vector<int>> set_crossing = set_cross(set_for_check, extra_koef[j].get_set());
            for (const auto &s: set_crossing) {
                set_for_check.erase(s);
            }

            if (set_for_check.empty()) {
                index.insert(i);
                break;
            }


        }

    }

    for (int i = 0; i < extra_koef.size(); i++) {
        if (index.find(i) != index.end()) continue;
        not_extra_koef.push_back(extra_koef[i]);
    }

    return not_extra_koef;
}


int main() {

    std::vector<int> inp;
    std::vector<std::vector<int>> MiniTerms;

    bool input_func = false;
    while (!input_func) {
        inp = {};
        std::string input_f;
        //std::cout << "write function vec" << std::endl;
        //std::cin >> input_f;
        input_f = "1000101110001001000110100000101001000101100000011111111011111111";
        input_func = true;

        for (char i: input_f) {
            int variable = i - '0';
            if (variable != 0 && variable != 1) {
                std::cout << "incorrect func vec" << std::endl;
                input_func = false;
            }
            inp.push_back(i - '0');
        }

        int check_size = inp.size();
        int check_degree = log(check_size) / log(2);
        if (pow(2, check_degree) != check_size) {
            std::cout << "incorrect length of func vec" << std::endl;
            input_func = false;
        }

    }

    int check_for_constant = 0;
    for (int i: inp) {
        if (i == 1) check_for_constant++;
    }

    if (check_for_constant == 0) {
        std::cout << "minimal_dnf: doesn't exist";
        std::cin >> check_for_constant;
        return 0;
    }
    if (check_for_constant == inp.size()) {
        std::cout << "minimal_dnf: 1";
        std::cin >> check_for_constant;
        return 0;
    }
    std::cout << "func vec: ";

    //std::vector<int> inp = { 0,1,0,0,1,1,0,1,1,1,1,0,0,1,0,1,1,1,1,1,1,0,0,0,0,1,1,1,0,0,0,0,1,1,0,0,0,0,1,0,1,1,1,0,0,0,1,1,1,1,0,1,0,0,1,0,0,1,0,0,0,0,1,1 };
    for (auto it: inp) std::cout << it;
    std::cout << std::endl;
    all_equations system_of_eq(inp);
//    system_of_eq.print_all_eq();

    system_of_eq.delete_null_koefs();
    std::cout << std::endl << std::endl;

    system_of_eq.print_all_eq();
    std::cout << std::endl << std::endl;

    system_of_eq.delete_big_koefs();
    system_of_eq.print_all_eq();
    std::cout << std::endl << std::endl;

// Подготовка вектора для финального упрощения
    std::vector<Koef> prepare_vec;
    for (const auto &it: system_of_eq.MinDnf()) {
        prepare_vec.push_back(it);
    }

    // Выделение коэффициентов, не покрываемых другими коэффициентами (не являются "большими")
    std::vector<Koef> not_big_koefs;
    for (auto koef: prepare_vec) {
        int flag = 0;
        for (const auto &koef_next: prepare_vec) {
            if (koef.bolshe_K(koef_next)) {
                flag = 1;
            }
        }
        if (flag == 0) { // Если коэффициент не "больше" других, добавляем его в вектор
            not_big_koefs.push_back(koef);
        }
    }

    std::vector<Koef> min_dnf = mdnf(not_big_koefs);

    // Вывод используемых импликант перед финальным выводом
    for (auto koef: min_dnf) {
        koef.print_K(2);
        std::cout << " = 1  => ";
        koef.print_K(1);
        std::cout << std::endl;
    }

    int count_of_borders = min_dnf.size() - 1;
    std::cout << "\n\nminimal_dnf: ";
    for (auto k: min_dnf) {
        k.print_K(1);
        if (count_of_borders != 0) {
            std::cout << " V ";
            count_of_borders--;
        }
    }
    int data;
    std::cin >> data;
    return 0;
}

