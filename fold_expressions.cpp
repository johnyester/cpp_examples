
// http://cpptruths.blogspot.com/2016/12/understanding-fold-expressions.html
// check out: http://cpptruths.blogspot.com/2014/03/fun-with-lambdas-c14-style-part-1.html
/* C17 fold examples:
defined over a 32 operators: + - * / % ^ & | = < > << >> += -= *= /= %= ^= &= |= <<= >>= == != <= >= && || , .* ->*.

// unary left fold
template <typename... Args>
auto addall(Args... args)
{
  return (... + args);
}

// equivalent to: ((((1+2)+3)+4)+5).
addall(1,2,3,4,5); // returns 15.


//binary left fold
template <typename... Args>
auto addall(Args... args)
{
  return (0 + ... + args);
}

// equivalent to (((((0+1)+2)+3)+4)+5)
addall(1,2,3,4,5); // returns 15
*/

#include <iostream>
#include <iomanip>

namespace jly_tutorials
{
#define UNARY_LEFT_FOLD(NAME, OP)   \
template<typename... Args>          \
auto NAME(Args&&... args) {         \
  return (... OP args);             \
}

	UNARY_LEFT_FOLD(add, +);
	UNARY_LEFT_FOLD(sub, -);
	UNARY_LEFT_FOLD(mul, *);
	UNARY_LEFT_FOLD(divide, / );
	UNARY_LEFT_FOLD(mod, %);
	UNARY_LEFT_FOLD(bxor, ^);
	UNARY_LEFT_FOLD(band, &);
	UNARY_LEFT_FOLD(bor, | );
	UNARY_LEFT_FOLD(assign, =);
	UNARY_LEFT_FOLD(lt, < );
#ifndef __clang__ 
	UNARY_LEFT_FOLD(gt, > );
	UNARY_LEFT_FOLD(rshift, >> );
#endif
	UNARY_LEFT_FOLD(lshift, << );
	UNARY_LEFT_FOLD(addassign, +=);
	UNARY_LEFT_FOLD(subassign, -=);
	UNARY_LEFT_FOLD(mulassign, *=);
	UNARY_LEFT_FOLD(divassign, /=);
	UNARY_LEFT_FOLD(modassign, %=);
	UNARY_LEFT_FOLD(bxorassign, ^=);
	UNARY_LEFT_FOLD(bandassign, &=);
	UNARY_LEFT_FOLD(borassign, |=);
	UNARY_LEFT_FOLD(lshiftassign, <<=);
	UNARY_LEFT_FOLD(rshiftassign, >>=);
	UNARY_LEFT_FOLD(equals, == );
	UNARY_LEFT_FOLD(nequals, != );
	UNARY_LEFT_FOLD(lte, <= );
	UNARY_LEFT_FOLD(gte, >= );
	UNARY_LEFT_FOLD(land, &&);
	UNARY_LEFT_FOLD(lor, || );
	UNARY_LEFT_FOLD(objptrmem, .*);
	UNARY_LEFT_FOLD(ptrptrmem, ->*);

	template<typename... Args>
	auto comma(Args&&... args) {
		return (..., args);
	}

	struct Phone { int ext; };
	struct Person { Phone phone; };

	/*
	Hello World!
add 1 6
sub 1 -4
mul 1 6
divide 1 3
mod 1 0
bxor 1 7
band 1 1
assign 1 4
assign-a 99 4 4
gt 1 true
rshift 1 2
lt 1 false
lshift 1 32
addassign 1 7
subassign 1 5
mulassign 1 12
divassign 1 3
modassign 1 0
bxorassign 1 5
bandassign 1 6
borassign 1 15
lshiftassign 1 32
rshiftassign 1 2
equals 1 false
nequals 1 true
lte 1 true
gte 1 true
land true true
lor false true
comma 1 2
objptrmem 999
p.*phoneptr.*extptr 999
ptrptrmem(&p,phoneptr).ext 999
&(pptr->*phoneptr)->*extptr 999
*/
	void main_unary_fold(void)
	{
		std::cout << std::boolalpha;
		std::cout << "add " << add(1) << " " << add(1, 2, 3) << "\n";// 1
		std::cout << "sub " << sub(1) << " " << sub(1, 2, 3) << "\n";
		std::cout << "mul " << mul(1) << " " << mul(1, 2, 3) << "\n";
		std::cout << "divide " << divide(1) << " " << divide(18, 2, 3) << "\n";
		std::cout << "mod " << mod(1) << " " << mod(23, 3, 2) << "\n";
		std::cout << "bxor " << bxor(1) << " " << bxor(1, 2, 4) << "\n";
		std::cout << "band " << band(1) << " " << band(1, 3, 7) << "\n";
		std::cout << "assign " << assign(1) << " " << assign(1, 2, 4) << "\n";

		auto a = 99;
		std::cout << "assign-a " << assign(a);
		std::cout << " " << assign(a, 2, 4);
		std::cout << " " << a << "\n";

#ifndef __clang__ 
		std::cout << "gt " << gt(1) << " " << gt(3, 2, 0) << "\n";
		std::cout << "rshift " << rshift(1) << " " << rshift(32, 2, 2) << "\n";
#endif

		std::cout << "lt " << lt(1) << " " << lt(1, 2, -1) << "\n";
		std::cout << "lshift " << lshift(1) << " " << lshift(1, 2, 3) << "\n";
		std::cout << "addassign " << addassign(1) << " " << addassign(2, 3, 2) << "\n";
		std::cout << "subassign " << subassign(1) << " " << subassign(7, 2) << "\n";
		std::cout << "mulassign " << mulassign(1) << " " << mulassign(2, 3, 2) << "\n";
		std::cout << "divassign " << divassign(1) << " " << divassign(7, 2) << "\n";
		std::cout << "modassign " << modassign(1) << " " << modassign(23, 3, 2) << "\n";
		std::cout << "bxorassign " << bxorassign(1) << " " << bxorassign(7, 2) << "\n";
		std::cout << "bandassign " << bandassign(1) << " " << bandassign(7, 6) << "\n";
		std::cout << "borassign " << borassign(1) << " " << borassign(1, 2, 4, 8) << "\n";
		std::cout << "lshiftassign " << lshiftassign(1) << " " << lshiftassign(8, 2) << "\n";
		std::cout << "rshiftassign " << rshiftassign(1) << " " << rshiftassign(16, 1, 2) << "\n";
		std::cout << "equals " << equals(1) << " " << equals(8, 3, 2) << "\n";
		std::cout << "nequals " << nequals(1) << " " << nequals(7, 2, 0) << "\n";
		std::cout << "lte " << lte(1) << " " << lte(7, 2, 0) << "\n";
		std::cout << "gte " << gte(1) << " " << gte(7, 3, 1) << "\n";
		std::cout << "land " << land() << " " << land(7, 2) << "\n";
		std::cout << "lor " << lor() << " " << lor(7, 2) << "\n";
		std::cout << "comma " << comma(1) << " " << comma(8, 3, 2) << "\n";

		auto phoneptr = &Person::phone;
		auto extptr = &Phone::ext;
		Person p{ { 999 } };
		Person* pptr = &p;
		std::cout << "objptrmem " << objptrmem(p, phoneptr, extptr) << "\n";
		std::cout << "p.*phoneptr.*extptr " << p.*phoneptr.*extptr << "\n";
		std::cout << "ptrptrmem(&p,phoneptr).ext " << ptrptrmem(&p, phoneptr).ext << "\n";
		std::cout << "&(pptr->*phoneptr)->*extptr " << (&(pptr->*phoneptr))->*extptr << "\n";

	}

	///////////////////////////////////////////////////

	struct Int {
		int value;
		explicit Int(int v = 0) : value(v) {}
		explicit operator int() const { return value; }
	};

	std::ostream& operator << (std::ostream& o, const Int& i) {
		o << i.value;
		return o;
	}

	Int operator + (Int const& i, Int const& j) {
		std::cout << "Adding " << i << " " << j << "\n";
		return Int(i.value + j.value);
	};

	Int operator * (Int const& i, Int const& j) {
		std::cout << "Multiplying " << i << " " << j << "\n";
		return Int(i.value * j.value);
	};

	template<typename... Args>
	auto addInts(Args&&... args)
	{
		return (Int{ 0 } + ... + args);
	}

	template<typename... Args>
	auto mulInts(Args&&... args)
	{
		return (Int{ 1 } * ... * args);
	}

	/*
	Adding 0 1
	Adding 1 2
	Adding 3 3
	6
	0
	Multiplying 1 1
	Multiplying 1 2
	Multiplying 2 3
	6
	1
	*/
	void main_binary_fold(void)
	{
		std::cout << addInts(Int{ 1 }, Int{ 2 }, Int{ 3 }) << "\n"; // prints 6
		std::cout << addInts() << "\n"; // prints 0
		std::cout << mulInts(Int{ 1 }, Int{ 2 }, Int{ 3 }) << "\n"; // prints 6
		std::cout << mulInts() << "\n"; // prints 1
	}
}