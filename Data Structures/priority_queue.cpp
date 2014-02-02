#include <cstdio>
#include <iostream>
#include <string>
#include <queue>

using namespace std;

class Compare {
  public:

  bool operator() (const string& lhs, const string &rhs) const {
    int size = min(lhs.length(), rhs.length());

    for (int i = 0; i < size; ++i) {
      if(lhs[i] != rhs[i]) {
        return lhs[i] > rhs[i]; 
      }
    }

    return lhs.length() < rhs.length();
  }
};

int main() {

  int money;
  char name[20];
  priority_queue< pair<int, string> > pq;
  pair<int, string> result;

  // suppose we enter these 7 money-name pairs below
  /*
  100 john
  10 billy
  20 andy
  100 steven
  70 felix
  2000 grace
  70 martin
  */
  pq.push(make_pair(100, "john"));          // inserting a pair in O(log n)
  pq.push(make_pair(10, "billy"));
  pq.push(make_pair(20, "andy"));
  pq.push(make_pair(100, "steven"));
  pq.push(make_pair(70, "felix"));
  pq.push(make_pair(2000, "grace"));
  pq.push(make_pair(70, "martin"));

  //                        (2000,grace)
  //           (100,steven)               (70,martin)   
  //     (100,john)   (10,billy)     (20,andy)  (70,felix)

  // let's print out the top 2 person with most money
  result = pq.top();                // O(1) to access the top / max element
  pq.pop();          // O(log n) to delete the top and repair the structure
  printf("%s has %d $\n", ((string)result.second).c_str(), result.first);
  
  result = pq.top(); 
  pq.pop();
  printf("%s has %d $\n", ((string)result.second).c_str(), result.first);

  priority_queue< string, vector<string>, Compare > pq_comparator;
  priority_queue<int, vector<int>, greater<int> > pq_greater;
}