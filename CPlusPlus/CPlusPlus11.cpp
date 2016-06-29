// Little test program to play with the new features in C++11
// Instead of creating a couple of file I just put defines around 
// the different tests. Only one file to maintain.
#include <iostream>
#include <algorithm>
#include <functional>
#include <thread>
#include <vector>
#include <mutex>
#include <atomic>
#include <chrono>

using namespace std;

#define __TEST6__

#ifdef __TEST1__
int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!
	return 0;
}
#endif


#ifdef __TEST2__
int main()
{
   char s[]="Hello World!";
   int Uppercase = 0; //modified by the lambda
   for_each(s, s+sizeof(s), [&Uppercase] (char c) {
    if (isupper(c))
     Uppercase++;
    });
 cout<< Uppercase<<" uppercase letters in: "<< s<<endl;
}
#endif


#ifdef __TEST3__

void f(int& n1, int& n2, const int& n3)
{
    std::cout << "In function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
    ++n1; // increments the copy of n1 stored in the function object
    ++n2; // increments the main()'s n2
    // ++n3; // compile error
}

int main()
{
    int n1 = 1, n2 = 2, n3 = 3;
    std::function<void()> bound_f = std::bind(f, n1, std::ref(n2), std::cref(n3));
    n1 = 10;
    n2 = 11;
    n3 = 12;
    std::cout << "Before function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
    bound_f();
    std::cout << "After function: " << n1 << ' ' << n2 << ' ' << n3 << '\n';
}
#endif


#ifdef __TEST4__
// http://en.cppreference.com/w/cpp/language/constexpr
#include <stdexcept>

// C++11 constexpr functions use recursion rather than iteration
// (C++14 constexpr functions may use local variables and loops)
constexpr int factorial(int n)
{
    return n <= 1? 1 : (n * factorial(n - 1));
}

// literal class
class conststr {
    const char* p;
    std::size_t sz;
public:
    template<std::size_t N>
    constexpr conststr(const char(&a)[N]): p(a), sz(N - 1) {}

    // constexpr functions signal errors by throwing exceptions
    // in C++11, they must do so from the conditional operator ?:
    constexpr char operator[](std::size_t n) const
    {
        return n < sz? p[n] : throw std::out_of_range("");
    }
    constexpr std::size_t size() const { return sz; }
};

// C++11 constexpr functions had to put everything in a single return statement
// (C++14 doesn't have that requirement)
constexpr std::size_t countlower(conststr s, std::size_t n = 0,
                                             std::size_t c = 0)
{
    return n == s.size()? c :
           s[n] >= 'a' && s[n] <= 'z'? countlower(s, n + 1, c + 1) :
                                       countlower(s, n + 1, c);
}

// output function that requires a compile-time constant, for testing
template<int n>
struct constN
{
    constN() { std::cout << n << '\n'; }
};

int main()
{
    std::cout << "4! = " ;
    constN<factorial(4)> out1; // computed at compile time

    volatile int k = 8; // disallow optimization using volatile
    std::cout << k << "! = " << factorial(k) << '\n'; // computed at run time

    std::cout << "the number of lowercase letters in \"Hello, world!\" is ";
    constN<countlower("Hello, world!")> out2; // implicitly converted to conststr
}

#endif


#ifdef __TEST5__
#include <future>
#include <thread>

int main()
{
    // future from a packaged_task
    std::packaged_task<int()> task([](){ return 7; }); // wrap the function
    std::future<int> f1 = task.get_future();  // get a future
    std::thread(std::move(task)).detach(); // launch on a thread

    // future from an async()
    std::future<int> f2 = std::async(std::launch::async, [](){ return 8; });

    // future from a promise
    std::promise<int> p;
    std::future<int> f3 = p.get_future();
    std::thread( [&p]{ p.set_value_at_thread_exit(9); }).detach();

    std::cout << "Waiting..." << std::flush;
    f1.wait();
    f2.wait();
    f3.wait();
    std::cout << "Done!\nResults are: "
              << f1.get() << ' ' << f2.get() << ' ' << f3.get() << '\n';
}
#endif

#ifdef __TEST6__
//Split "mem" into "parts", e.g. if mem = 10 and parts = 4 you will have: 0,2,4,6,10
//if possible the function will split mem into equal chuncks, if not
//the last chunck will be slightly larger

// http://en.cppreference.com/w/cpp/chrono

std::vector<int> bounds(int parts, int mem) {
    std::vector<int>bnd;
    int delta = mem / parts;
    int reminder = mem % parts;
    int N1 = 0, N2 = 0;
    bnd.push_back(N1);
    for (int i = 0; i < parts; ++i) {
        N2 = N1 + delta;
        if (i == parts - 1)
            N2 += reminder;
        bnd.push_back(N2);
        N1 = N2;
    }
    return bnd;
}

void dot_product(const std::vector<int> &v1, const std::vector<int> &v2, std::atomic<int> &result, int L, int R){
	int partial_sum = 0;
	for(int i = L; i < R; ++i){
		partial_sum += v1[i] * v2[i];
	}
	result += partial_sum;
}

int main(){
	int nr_elements = 1e5;
	int nr_threads = 2;
	atomic<int> result(0);
	vector<thread> threads;

    chrono::time_point<chrono::system_clock> start, end;
    start = chrono::system_clock::now();

	//Fill two vectors with some values
	vector<int> v1(nr_elements,3), v2(nr_elements,2);

	//Split nr_elements into nr_threads parts
	vector<int> limits = bounds(nr_threads, nr_elements);

	//Launch nr_threads threads:
    for (int i = 0; i < nr_threads; ++i) {
        threads.push_back(thread(dot_product, ref(v1), ref(v2), ref(result), limits[i], limits[i+1]));
    }

    //Join the threads with the main thread
    for(auto &t : threads){
        t.join();
    }

    end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = end-start;
    cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

    //Print the result
    cout<<result<<endl;

	return 0;
}
#endif
