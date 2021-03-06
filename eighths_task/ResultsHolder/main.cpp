#include <string>
#include <set>
#include<iostream>
#include<map>
#include<vector>
#include<algorithm>
#include <unordered_set>
using namespace std;

class ResultsHolder {
public:
    /**
     * Добавить в общую таблицу результат экзамена студента.
     * Параметры:
     * - full_name - строка с полным именем студента
     * - mark - оценка (от 1 до 10)
     * (Гарантируется, что совпадений полных имён у разных студентов не бывает.)
     *
     * Если студента с данным именем нет в результатах - добавить его.
     * Если студент с таким именем есть - обновить его результат
     * (потому что апелляции вполне возможны).
     */
    void update(const std::string& full_name, unsigned mark) {
        auto i = std::find(s.begin(), s.end(), full_name);
        if (i != s.end()) {
            for (auto j = students1.begin(); j != students1.end(); j++) {
                if (j->second == full_name) {
                    j = students1.erase(j);
                }
            }
        }
        s.push_back(full_name);
        students.insert(make_pair(full_name, mark));
        students1.insert((make_pair(mark, full_name)));
        marks.push_back(mark);
        std::sort(marks.begin(), marks.end());
    }

    /**
     * Вывести студентов, отсортировав по именам по алфавиту.
     *
     * Вывод в std::cout.
     *
     * Формат вывода:
     * Alex 7
     * Anastasia 9
     * Anny 5
     * Ivan 10
     * Nikita 8
     */
    void print_students() const{
        for(const auto & student : students){
            cout << student.first << " " << student.second << endl;
        }
    }

    /**
     * Вывести студентов, отсортировав сперва по оценкам по убыванию,
     * а при равных оценках - по именам по алфавиту.
     *
     * Вывод в std::cout.
     *
     * Формат вывода:
     * Ivan 10
     * Anastasia 9
     * Nikita 8
     * Alex 7
     * Anny 5
     */
    void print_standings() const{
        std::vector<std::pair<int, std::string>> v;
        for(auto const & it : students1) {
            v.push_back({it.first, it.second});
        }
        std::reverse(v.begin(), v.end());
        for (const auto& i: v) {
            std:: cout << i.second << ' ' << i.first << '\n';
        }
    }

    /**
     * Обработать запрос военкомата.
     *
     * Военкомат передаёт список имён и хочет призвать этих людей в армию.
     * Если у этих людей неуд-ы (оценка ниже 3), то:
     * - вернуть эти имена в ответе военкомату;
     * - удалить этих людей из общей таблицы (потому что теперь они не студенты).
     *
     * Входной параметр: сет строк с именами, кого хочет призвать военкомат.
     * Возвращаемое значение: сет строк с именами, кого действительно можно призвать
     * (или пустой сет, если призвать никого нельзя).
     * Гарантируется, что военкомат не будет пытаться призвать несуществующих студентов.
     */
    std::set<std::string> process_military_request(const std::set<std::string>& names){
        for(const auto & it : names){
            if(students[it] < 3){
                s1.insert(it);
            }
        }
        return s1;
    }
private:
    map<string, unsigned> students;
    map<unsigned, string> students1;
    vector<unsigned>marks;
    set<string> s1;
    vector<string> s;
};
int main(){
    // Создали таблицу
    ResultsHolder rh;

    // Загрузили результаты
    rh.update("Alex", 6);
    rh.update("Anny", 5);
    rh.update("Ivan", 10);
    rh.update("Anastasia", 9);
    rh.update("Johnny", 1);
    rh.update("Alex", 7); // Апелляция у Alex, оценка обновляется
    rh.update("Nikita", 8);

    // Вывели в порядке убывания результата
    std::cout << "Exam results:" << std::endl;
    rh.print_standings();

    // Определили, кто идёт в армию
    auto to_military_service = rh.process_military_request({"Johnny", "Ivan"});

    // Вывели их на экран
    std::cout << "Are in army now:" << std::endl;
    for(const auto& s : to_military_service) {
        std::cout << s << std::endl;
    }

    // Вывели по алфавиту (но уже без Johnny, но Ivan остался с нами)
    std::cout << "Exam results:" << std::endl;
    rh.print_students();
    return 0;
}



