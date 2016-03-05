#pragma once
#include <vector>
#include <type_traits>
#include "Solution.hpp"
#include "Problem.hpp"

using namespace std;

// template<typename Pro, typename Sol>
// using IsSubtypesProblemAndSolution = typename std::enable_if<std::is_base_of<Solution, Sol>::value && std::is_base_of<Problem, Pro>::value>::type;

// template<class Sol, class Pro, class Enable = void>
// class DivAndConquerq {}; // primary template


// template <class Sol, class Pro>
// class DivAndConquerq<Pro, Sol, IsSubtypesProblemAndSolution<Pro, Sol>> {
//  public:
//   DivAndConquerq() {};

//   Sol solve(Pro p) {
//     vector<Pro> pp;
//     if (isSimple(p)) {
//       return simplySolve(p);
//     }
//     else  {
//       pp = decompose(p);
//     }
//     vector<Sol> ss = vector<Sol>(pp.size());
//     for (unsigned i = 0; pp.size() > i; i++) {
//       ss[i] = solve(pp[i]);
//     }
//     return combine(p, ss);
//   }

//  protected:
//   bool isSimple(Problem p);

//   Solution simplySolve(Problem p);

//   vector<Problem> decompose(Problem p);

//   Solution combine(Problem p, vector<Solution> ss);
// };

class DivAndConquer {
public:
  Solution solve(Problem p) {
    vector<Problem> pp;

    if (isSimple(p)) {
      return simplySolve(p);
    }
    else  {
      pp = decompose(p);
    }

    vector<Solution> ss = vector<Solution>(pp.size());
    for (unsigned i = 0; pp.size() > i; i++) {
      ss[i] = solve(pp[i]);
    }
    return combine(p, ss);
  }

protected:
  bool isSimple(Problem p);

  Solution simplySolve(Problem p);

  vector<Problem> decompose(Problem p);

  Solution combine(Problem p, vector<Solution> ss);
};

// #include <type_traits>
// #include <iostream>
// #include <string>

// class Solution {};
// class Problem {};

// template<typename T>
// using IsSolution = typename std::is_base_of<Solution, T>::value;

// template<typename T>
// using IsProblem = typename std::is_base_of<Problem, T>::value;

// template <bool value, typename T = void>
// using EnableIf = typename std::enable_if<value, T>::type;

// template<typename Sol,typename Pro>
// using IsSolutionAndProblem = typename std::enable_if
//     <std::is_base_of<Solution, Sol>::value
//   && std::is_base_of<Problem, Pro>::value>::type;

// // the partial specialization of A is enabled via a template parameter
// template<class Sol, class Pro, class Enable = void>
// class DivAndConquer {}; // primary template

// //typename std::enable_if<std::is_base_of<Solution, Sol>::value
// //                     && std::is_base_of<Problem, Pro>::value>> {

// template <class Sol, class Pro>
// class DivAndConquer<Sol, Pro, //EnableIf<IsProblem<Pro>::value && IsSolution<Sol>::value >> 
// IsSolutionAndProblem<Sol, Pro>> 
// {
// //typename std::enable_if<std::is_base_of<Solution, Sol>::value
// //                     && std::is_base_of<Problem, Pro>::value>::type> {
// protected:
//     Sol sol;
//     Pro pro;
// public:
//     DivAndConquer() {};
    
//     DivAndConquer(const DivAndConquer<Sol, Pro>& a) {
//         this = a;
//     }
//     //DivAndConquer(Sol s, Pro p) {
//     //    sol = s;
//     //    pro = p;
//     //    std::cout << "conquer" << std::endl;
//     //}

// };

// class SolM : public Solution {};

// class ProM : public Problem {};


// class Merge : public DivAndConquer<SolM, ProM> {
// public:


//     Merge(Solution s, Problem p){
//         //sol = s;
//         //pro = p;
//         std::cout << "merge" << std::endl;
//     }

// };

// int main()
// {
 
//     Problem p;
//     Solution s;
//     //DivAndConquer<int, int>aa (5,5);
//     //DivAndConquer<Solution, Problem> aa(s, p);
    
//     ProM pp;
//     SolM c;
//     Merge ass (c, pp);//(c,pp);
//     //A<int> a1; // OK, matches the primary template
//     ///A<double> a2(1.55); // OK, matches the partial specialization
// }
