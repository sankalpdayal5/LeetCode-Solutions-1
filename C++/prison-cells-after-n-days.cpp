// Time:  O(1)
// Space: O(1)

class Solution {
public:
    vector<int> prisonAfterNDays(vector<int>& cells, int N) {
        for (N = (N - 1) % 14 + 1; N > 0; --N) {
            vector<int> cells2(8, 0);
            for (int i = 1; i < 7; ++i) {
                cells2[i] = static_cast<int>(cells[i - 1] == cells[i + 1]);
            }
            cells = move(cells2);
        }
        return cells;
    }
};

// Time:  O(1)
// Space: O(1)
class Solution2 {
public:
    vector<int> prisonAfterNDays(vector<int>& cells, int N) {
        unordered_map<vector<int>, int, VectorHash<int>> lookup;
        lookup[cells] = N;
        bool is_loop = false;
        while (N) {
            lookup[cells] = N--;
            vector<int> cells2(8, 0);
            for (int i = 1; i < 7; ++i) {
                cells2[i] = static_cast<int>(cells[i - 1] == cells[i + 1]);
            }
            cells = move(cells2);
            if (lookup.count(cells) && is_loop == false) {
                N %= lookup[cells] - N;
                is_loop = true;
            }
        }
        return cells;
    }

private:
    template<typename T>
    struct VectorHash {
        size_t operator()(const std::vector<T>& v) const {
            size_t seed = 0;
            for (const auto& i : v) {
                seed ^= std::hash<T>{}(i)  + 0x9e3779b9 + (seed<<6) + (seed>>2);
            }
            return seed;
        }
    };
};