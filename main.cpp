#include <iostream>

using namespace std;

template<class _Arg1, class _Arg2, class _Arg3, class _Arg4>
class trinary_function: public binary_function<_Arg1, _Arg2, _Arg4> {
public:
	typedef _Arg3 third_argument_type;
};

template<class _Tp1, class _Tp2, class _Tp3>
class AllGreaterNull: public trinary_function<_Tp1, _Tp2, _Tp3, bool> {
public:
	bool operator() (const _Tp1& v1, const _Tp2& v2, const _Tp3& v3) const {
		return (v1 > 0 && v2 > 0 && v3 > 0);
	}
};



template<class __Operation>
class binder3rd {
public:
	typedef typename __Operation::first_argument_type 	first_argument_type;
	typedef typename __Operation::second_argument_type 	second_argument_type;
	typedef typename __Operation::third_argument_type 	third_argument_type;
	
	typedef typename __Operation::result_type 			result_type;
	
private:
	const third_argument_type _third_arg_value;
	const __Operation _op;
public:
	binder3rd(const __Operation& op, const third_argument_type& third_arg_value): _third_arg_value(third_arg_value), _op(op) { }
	
	result_type operator() (const first_argument_type& f, const second_argument_type& s) const {
		return (_op(f, s, _third_arg_value));
	}
};

template<class __Operation>
binder3rd<__Operation> bind3rd (const __Operation& op, const typename __Operation::third_argument_type& value) {
	return binder3rd<__Operation>(op, value);
}


int main() {

	auto op = bind3rd(AllGreaterNull<int, char, short>(), 1);
	auto op1 = bind2nd(op, 2);
	
	if(op1(1)) {
		return 1;
	}
	
	return 0;
}
