#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <iterator>
#include <functional>
using namespace std;
class FishRecord {
public:
    FishRecord(const string& species, float length, float weight, const string& date, const std::string& fisherman)
        : species(species), length(length), weight(weight), date(date), fisherman(fisherman) {}

    const string& getSpecies() const { return species; }
    float getLength() const { return length; }
    float getWeight() const { return weight; }
    const string& getDate() const { return date; }
    const string& getFisherman() const { return fisherman; }
    string toString() const {
        return "Species: " + species + ", Length: " + to_string(length) + ", Weight: " + to_string(weight) + ", Date: " + date + ", Fisherman: " + fisherman;
    }
private:
    string species;
    float length;
    float weight;
    string date;
    string fisherman;
};

class FishRecords {
public:
    class iterator;

    void addRecord(const FishRecord& record) {
        records.push_back(record);
    }

    iterator begin() { return iterator(records.begin()); }
    iterator end() { return iterator(records.end()); }

private:
    vector<FishRecord> records;

    class iterator {
    public:
        using iterator_category = std::bidirectional_iterator_tag;
        using value_type = FishRecord;
        using difference_type = std::ptrdiff_t;
        using pointer = FishRecord*;
        using reference = FishRecord&;

        iterator(typename vector<FishRecord>::iterator iter) : iter(iter) {}
        iterator operator+(int n) const { return iterator(iter + n); }
        int operator-(const iterator& other) const { return iter - other.iter; }
        FishRecord& operator*() const { return *iter; }
        iterator& operator++() { ++iter; return *this; }
        iterator operator++(int) { iterator tmp = *this; ++(*this); return tmp; }
        iterator& operator--() { --iter; return *this; }
        iterator operator--(int) { iterator tmp = *this; --(*this); return tmp; }
        bool operator==(const iterator& other) const { return iter == other.iter; }
        bool operator!=(const iterator& other) const { return !(*this == other); }


    private:
        typename vector<FishRecord>::iterator iter;
    };

};
template<class Iter>
void merge_sort(Iter first, Iter last, int option)
{
    if (last - first > 1)
    {
        Iter middle = first + (last - first) / 2;
        merge_sort(first, middle, option);
        merge_sort(middle, last, option);
        switch (option) {
        case 1:
            inplace_merge(first, middle, last, [](const FishRecord& a, const FishRecord& b) {
                return a.getSpecies() < b.getSpecies();
                });
            break;
        case 2:
            inplace_merge(first, middle, last, [](const FishRecord& a, const FishRecord& b) {
                return a.getLength() < b.getLength();
                });
            break;
        case 3:
            inplace_merge(first, middle, last, [](const FishRecord& a, const FishRecord& b) {
                return a.getWeight() < b.getWeight();
                });
            break;
        case 4:
            inplace_merge(first, middle, last, [](const FishRecord& a, const FishRecord& b) {
                return a.getDate() < b.getDate();
                });
            break;
        case 5:
            inplace_merge(first, middle, last, [](const FishRecord& a, const FishRecord& b) {
                return a.getFisherman() < b.getFisherman();
                });
            break;
        }
        
    }
}
int main() {
    FishRecords records;

    records.addRecord(FishRecord("Trout", 30.5f, 2.5f, "2024-04-25", "Smith"));
    records.addRecord(FishRecord("Salmon", 45.0f, 4.2f, "2024-04-27", "Johnson"));
    records.addRecord(FishRecord("Bass", 28.0f, 3.0f, "2024-04-28", "Williams"));

    while (true) {
        cout << "Sort by: 1 - species, 2 - length, 3 - weight, 4 - date, 5 - fisherman" << endl;
        int option;
        cin >> option;
        merge_sort(records.begin(), records.end(), option);

        cout << "Sorted by " + to_string(option) << endl;
        for (const auto& record : records) {
            cout << record.toString() << endl;
        }
    }   

    return 0;
}
