#ifndef AiAS_Utils
#define AiAS_Utils

template<class T>
void Swap(T& a, T& b) {
	T t = a;
	a = b;
	b = t;
}

template<class T = void>
struct Less {
	bool operator()(const T& a, const T& b) {
		return a < b;
	}
};

template<>
struct Less<void> {
	template<class A, class B>
	bool operator()(const A& a, const B& b) {
		return a < b;
	}
};

#endif // !AiAS_Utils
